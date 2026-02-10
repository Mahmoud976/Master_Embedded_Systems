#ifndef _String_H_
#define _String_H_
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include"My_Typedef.h"
#include <stddef.h>  // For NULL

int my_memcmp(const void* str1, const void* str2, int lenght);

void* my_memcpy(void* dest, const void* src, int lenght);

void* my_memset(void* str, int value, int lenght);

int my_strlen(const char* str);

uint32_t my_chinstr(const char* str, char value);

//void* my_memmove(void* dest, const void* src, int lenght);//as memcpy

char* my_strcat(char* dest, const char* src);

char* my_strncat(char* dest, const char* src, int lenght);

char* my_strchr(const char* str, int value);

//int my_strcmp(const char* str1, const char* str2); // as memcmp

//int my_strncmp(const char* str1, const char* str2, int lenght);//as memcmp

//int my_strcoll(const char* str1, const char* str2); memcpy

char* my_strcpy(char* dest, const char* src); 

char* my_strncpy(char* dest, const char* src, int lenght); 

int my_strcspn(const char* str1, const char* str2);

//char* my_strerror(int errnum);


char* my_strpbrk(const char* str1, const char* str2);

char* my_strrchr(const char* str, int value);

int my_strspn(const char* str1, const char* str2);


char* my_strstr(const char* haystack, const char* needle);


char* my_strtok(char* str, const char* delim);

int my_strxfrm(char* dest, const char* src, int lenght);



#endif // !_String_H_