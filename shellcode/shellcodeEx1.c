#include <stdio.h>
#include <stdlib.h>


void return_input(int width, int height){
	
	char array[5];
	gets(array);
	printf("%s\n",array);

}
int main() {
	return_input(1,2);
	return 0;
}

