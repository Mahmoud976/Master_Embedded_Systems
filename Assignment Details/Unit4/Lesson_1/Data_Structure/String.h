#ifndef string_h
#define string_h

#include<stdio.h>
#include<stdlib.h>
#include"Typedef_t.h"

/* Maximum allowed bytes to copy (adjust to your system) */
#define my_memcpy_MAX_LEN   (1024U)


int my_memcmp(const void* str1, const void* str2, int lenght);

void* my_memcpy(void* dest, const void* src, uint32_t length);

void* my_memset(void* str, int value, int lenght);

int my_strlen(const char* str);

uint32_t my_chinstr(const char* str, char value);

//void* my_memmove(void* dest, const void* src, int lenght);//as my_memcpy

char* my_strcat(char* dest, const char* src);

char* my_strncat(char* dest, const char* src, int lenght);

char* my_strchr(const char* str, int value);

//int my_strcmp(const char* str1, const char* str2); // as memcmp

//int my_strncmp(const char* str1, const char* str2, int lenght);//as memcmp

//int my_strcoll(const char* str1, const char* str2); my_memcpy

//char* my_strcpy(char* dest, const char* src); my_memcpy

//char* my_strncpy(char* dest, const char* src, int lenght); my_memcpy

int my_strcspn(const char* str1, const char* str2);

//char* my_strerror(int errnum);


char* my_strpbrk(const char* str1, const char* str2);

char* my_strrchr(const char* str, int value);

int my_strspn(const char* str1, const char* str2);


char* my_strstr(const char* haystack, const char* needle);


int* my_strtok(char* str, const char* delim);


int my_strxfrm(char* dest, const char* src, int lenght);



#endif // !string_h