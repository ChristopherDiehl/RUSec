#include "curlHelper.h"

void init_string(struct string *s) 
{
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

char * charcpy(char * string, int start, int end)
{
	char * return_val = malloc(sizeof(char) *(end-start));
	int i = 0;

	for (i = start; i < end; i ++)
	{
		return_val[i-start] = string[i];
	}

	return return_val;

}

//returns id, key, iv
char ** parseJson(char * string, int len) 
{
	printf("%s\n\n",string);
	int i = 0, counted =0;
	char ** return_val = malloc(sizeof(char*)*3);

	for(i = 4; i < len; i ++)
	{

		if(string[i] == ':')
		{
			i = i + 2;
			int j = i;
			while(string[j] != '"') {
				j++;
			}
			return_val[counted] = charcpy(string,i,j);
			counted ++;

			if(counted == 3)
				break;
		}
	}

	return return_val;

}

char ** curl(char * url)
{

	CURL *curl;
	CURLcode res;
	struct string s;
	char ** parsedJson;
	init_string(&s);

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

		res = curl_easy_perform(curl);

		if(res != CURLE_OK)
		   curl_easy_strerror(res);


		parsedJson = parseJson(s.ptr,s.len);
		free(s.ptr);

		curl_easy_cleanup(curl);

		return parsedJson;
	}

}