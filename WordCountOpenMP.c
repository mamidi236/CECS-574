//              
//note: How to run and test: Enter all the txt files' name you want to test into one txt file named "filename_list.txt". 
//                           Put this .c document and the filename_list.txt file together under the same folder and then run and compile.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <omp.h>

#define FILENAME_LEN 50
#define FILENAME_NUM 100
#define MAX_LINE_SIZE 100000

char text[FILENAME_NUM][MAX_LINE_SIZE * 50];



void skipPuntDigsToLower(char *p)
{
	char *src = p, *dst = p;
	while (*src) 
	{
		if (ispunct((unsigned char)*src) || isdigit((unsigned char)*src)) 
		{
			src++;
		}
		else if (isupper((unsigned char)*src)) 
		{
			*dst++ = tolower((unsigned char)*src);
			src++;
		}
		else if (src == dst) 
		{
			src++;
			dst++;
		}
		else 
		{
			*dst++ = *src++;
		}
	}
	*dst = 0;
}


void readFunc(const char* filename, int index) 
{
	FILE *fp = fopen(filename, "r");
	char word[1000];
	if (fp == NULL)
	{
		printf("input file is invalid !");
		return;
	}
                                                                                                                                                                                        
	while (fscanf(fp, " %s", word) == 1)
	{
		skipPuntDigsToLower(word);
		strcat(text[index], word);
		strcat(text[index], " ");
	}
	fclose(fp);
}







// Main Function
int main()
{
	int file_num = 0;
	FILE *read_filename = fopen("filename_list.txt", "r");
	char **filename_list_array = (char **)malloc(sizeof(char*)* FILENAME_NUM);
	int i,j;

#pragma omp parallel for
	for (i = 0; i < FILENAME_NUM; i++)
	{
		filename_list_array[i] = (char *)malloc(sizeof(char)* FILENAME_LEN);
	}

	if (read_filename == NULL)
	{
		printf("Cannont open the file !");
		return 0;
	}
	while (!feof(read_filename))
	{
		fscanf(read_filename, "%s\n", filename_list_array[file_num]);
		file_num++;
	}
	

	omp_set_num_threads(8);
	
#pragma omp parallel private (i)
	{

		{
			for (i = 0; i < file_num; i++) 
			{
#pragma omp task
				{
					readFunc(filename_list_array[i], i);
				}
			}
		}
	}


//implement mapper function
// implement writter function




	return 0;
}
