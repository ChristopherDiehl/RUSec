#ifndef CURLHELPER_H
#define CURLHELPER_H

#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


struct string {
  char *ptr;
  size_t len;
};


char ** curl(char * url);
char ** parseJson(char * string, int len);
char * charcpy(char * string, int start, int end);
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);
void init_string(struct string *s);

#endif