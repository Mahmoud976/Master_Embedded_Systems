#define _CRT_SECURE_NO_WARNINGS


#include"String.h"
/*
*
*
*
*
*/
sint32_t my_memcmp(const void* str1, const void* str2, int lenght)
{
	sint32_t retval = 0;
	uint8_t* temp1 = str1;  uint8_t* temp2 = str2;
	if ((NULL == temp1) || (NULL == temp2)) { printf("faild\n"); }
	else if (temp1 == temp2) { retval = 0; }
	else {
		while (lenght) {
			if (*temp1 != *temp2) {
				retval = (*temp1 > *temp2) ? 1 : -1;
				break;
			}
			else { temp1++;temp2++; lenght--; }
		}
	}
	return retval;
}
/*
*
*
*
*
*/
void* my_memcpy(void* dest, const void* src, int lenght)
{
	uint8_t* tempdest = dest;
	uint8_t* tempsrc = src;
	if ((NULL == tempdest) || (NULL == tempsrc)) {}
	else if (tempdest == tempsrc) {}
	else
	{
		while (lenght--)
		{
			*tempdest++ = *tempsrc++;
		}
	}

	return dest;
}
/*
*
*
*
*
*/
void* my_memset(void* str, int value, int lenght)
{
	uint8_t* temp = str;
	if (NULL == temp) {}
	//else if(lenght > sizeof(temp)){}
	else
	{
		while (lenght--)
		{
			*temp = value;
			temp++;

		}
	}
	return str;
}
/*
*
*
*
*
*/
uint32_t my_strlen(const char* str)
{
	uint32_t count = 0;
	uint8_t* temp = str;
	if (NULL == temp) {}
	else
	{
		while (*temp++ != '\0')count++;

	}
	return count;
}
/*
*
*
*
*
*/
char* my_strcat(char* dest, const char* src)
{
	uint8_t* tempdest = dest;
	uint8_t* tempsrc = src;
	if ((NULL == tempdest) || (NULL == tempsrc)) { printf("failed pointer is NULL!!"); }
	//else if (  (printf("first= %i",sizeof(tempdest) - my_strlen(tempdest))) < (printf("   soc%i",(my_strlen(tempsrc))))) { printf("Error dest is small!!"); }
	else
	{
		my_memcpy((tempdest + my_strlen(tempdest)), tempsrc, my_strlen(tempsrc));
	}

	return dest;
}
/*
*
*
*
*
*/
char* my_strncat(char* dest, const char* src, int lenght)
{
	uint8_t* tempdest = dest;
	uint8_t* tempsrc = src;
	if ((NULL == tempdest) || (NULL == tempsrc)) { printf("failed pointer is NULL!!"); }
	else
	{
		my_memcpy((tempdest + my_strlen(tempdest)), tempsrc, lenght);
	}

	return dest;
}
/*
*
*
*
*
*/
uint32_t my_chinstr(const char* str, char value)
{
	uint8_t* temp = str;
	if (NULL == temp) { printf(""); }
	else
	{
		for (int i = 0; i <= my_strlen(temp);i++)
		{
			if (temp[i] == value)	return i;

		}
	}
	return -1;
}
/*
*
*
*
*
*/
char* my_strchr(const char* str, int value)
{
	uint8_t* temp = str;
	if (NULL == temp) { printf(""); }
	else
	{
		for (int i = 1; i <= my_strlen(temp);i++)
		{
			if (temp[i - 1] == value)
			{
				temp = temp + i;
				break;
			}
		}
	}
	return temp;
}
/*
*
*
*
*
*This function returns the number of characters in the initial segment of string str1 which are not in the string str2.
*/
int my_strcspn(const char* str1, const char* str2)
{
	uint8_t* temp1 = str1;uint8_t* temp2 = str2;
	if ((NULL == temp1) || (NULL == temp2)) {}
	else
	{
		for (int i = 0; i < my_strlen(temp1); i++)
		{
			for (int j = 0; j < my_strlen(temp2); j++)
				if (temp1[i] == temp2[j]) return i;
		}
	}
}
/*
*
*
*
*This function returns a pointer to the character in str1 that matches one of the characters in str2, or NULL if no such character is found.
*/
char* my_strpbrk(const char* str1, const char* str2)
{
	uint8_t* temp1 = str1;uint8_t* temp2 = str2;
	if ((NULL == temp1) || (NULL == temp2)) {}
	else
	{
		for (int i = 0; i < my_strlen(temp1); i++)
		{
			for (int j = 0; j < my_strlen(temp2); j++)
				if (temp1[i] == temp2[j]) return temp1[i];

		}
	}
	return NULL;
}
/*
*
*
*
*
*/

char* my_strrchr(const char* str, int value)
{
	uint16_t count;
	uint8_t* temp = str;
	if (NULL == temp) { printf(""); }
	else
	{
		for (int i = 1; i <= my_strlen(temp);i++)
		{
			if (temp[i - 1] == value)
			{
				count = i;
			}
		}
		temp = temp + count;
	}
	return temp;
}
/*
*
*
*
*This function returns the number of characters in the initial segment of str1 which consist only of characters from str2.
*/
int my_strspn(const char* str1, const char* str2)
{
	uint16_t count = 0;
	uint8_t* temp1 = str1;uint8_t* temp2 = str2;
	if ((NULL == temp1) || (NULL == temp2)) {}
	else
	{
		for (int i = 0; i < my_strlen(temp1); i++)
		{
			for (int j = 0; j < my_strlen(temp2); j++)
				if (temp1[i] == temp2[j])
				{
					count++;
					break;
				}
		}
	}
	return count;
}
/*
*
*
*
*This function returns a pointer to the first occurrence in haystack of any of the entire sequence of characters specified in needle, or a null pointer if the sequence is not present in haystack.
*/
/*
char* my_strstr(const char* haystack, const char* needle)
{
	uint8_t* temp1 = haystack; uint8_t* temp2 = needle;
	if ((NULL == temp1) || (NULL == temp2)) {}
	else if (my_strlen(temp1) < my_strlen(temp2)) { printf("temp2>"); return NULL; }
	else
	{
		if (temp1 == temp2)return temp1;

		for (int i = 0; i < my_strlen(temp1); i++)
		{
			if (temp1[i] == temp2[0])
			{
				for (int k = 0; k < my_strlen(temp2); k++)
				{
					if (temp1[i] == temp2[k])
					{
						if (k == my_strlen(temp2) - 1)  return temp2;
						i++;
						continue;
					}
					else break;
				}
			}
		}
	}
	return NULL;
}*/


/**
 * @brief  Splits a string into tokens based on delimiters.
 *
 * @details
 * - Each call returns the next token in the string.
 * - Uses a static pointer to keep track of the current position.
 * - Modifies the original string in-place.
 *
 * @param  str   The string to tokenize (first call) or NULL (subsequent calls)
 * @param  delim String containing delimiter characters
 * @return Pointer to the next token, or NULL if no more tokens
 */
char* my_strtok(char* str, const char* delim)
{
	static char* next = NULL; // keeps track of current position
	char* start;

	// If new string provided, reset static pointer
	if (str != NULL)
		next = str;

	if (next == NULL)
		return NULL;

	// Skip leading delimiters
	while (*next != '\0')
	{
		const char* d = delim;
		int is_delim = 0;
		while (*d != '\0')
		{
			if (*next == *d)
			{
				is_delim = 1;
				break;
			}
			d++;
		}
		if (!is_delim)
			break;
		next++;
	}

	if (*next == '\0') // end of string
		return NULL;

	// Start of token
	start = next;

	// Move to the end of the token
	while (*next != '\0')
	{
		const char* d = delim;
		int is_delim = 0;
		while (*d != '\0')
		{
			if (*next == *d)
			{
				is_delim = 1;
				break;
			}
			d++;
		}
		if (is_delim)
		{
			*next = '\0'; // terminate token
			next++;       // prepare for next call
			return start;
		}
		next++;
	}

	// Last token without delimiter after it
	next = NULL;
	return start;
}

/*
*
*
*
*
*/
int my_strxfrm(char* dest, const char* src, int len)
{
	uint8_t* tempdest = dest;
	uint8_t* tempsrc = src;
	uint8_t lenght = my_strlen(tempsrc);
	uint8_t lenght1 = my_strlen(tempsrc);
	if ((NULL == tempdest) || (NULL == tempsrc)) {}
	else if (tempdest == tempsrc) {}
	else
	{
		while (lenght--)
		{
			*tempdest++ = *tempsrc++;
		}
	}
	return lenght1;
}


/* Copies source string to destination (null-terminated) */
char* my_strcpy(char* dest, const char* src)
{
	char* ptr = dest;

	/* Copy each character until null-terminator */
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	/* Add null-terminator at the end */
	*ptr = '\0';

	return dest;
}

/* Copies up to n characters from source to destination */
char* my_strncpy(char* dest, const char* src, size_t n)
{
	char* ptr = dest;
	size_t i = 0;

	/* Copy at most n characters or until null-terminator */
	while (i < n && src[i] != '\0')
	{
		ptr[i] = src[i];
		i++;
	}

	/* If we copied less than n, pad rest with nulls */
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}

	return dest;
}
