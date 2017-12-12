#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "harness.h"

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void check_for_multiple_processes();
void check_malloc();
void handle_invalid_address();
void test_multiple_pages();
void check_free();
void handling_multiple_pages();

//run one at a time
int main(int argc, char ** argv) {
	init_petmem();
 	//check_malloc();
    	//test_multiple_pages();
   	//check_free();
	//handling_multiple_pages();

	//check_for_multiple_processes();
  	handle_invalid_address();
    return 0;
}
void handling_multiple_pages()
{

	printf("Creating 2 pages\n");

	char * buf ;
        buf= pet_malloc(8096);
	
    buf[50] = 'H';
    buf[51] = 'e';
    buf[52] = 'l';
    buf[53] = 'l';
    buf[54] = 'o';
    buf[55] = ' ';
    buf[56] = 'W';
    buf[57] = 'o';
    buf[58] = 'r';
    buf[59] = 'l';
    buf[60] = 'd';
    buf[61] = '!';
    buf[62] = 0;
    
    buf[8000] = 't';

    printf("%s\n", (char *)(buf + 50));
	printf("\t%c\n",buf[8000]);    
    pet_free(buf);
	printf("--------------------------------------------\n");

     

}

void check_for_multiple_processes()
{
    printf("Multiple processes test\n");
    init_petmem();
    if (fork()==0){
        printf("Process 1: Child\n");
        char * buf ;
        buf= pet_malloc(8096);
        printf("Allocated 1 page at %p\n", buf);
        pet_dump();
        buf[50] = 'O';
        buf[51] = 'S';
        printf("%s\n", (char *)(buf + 50));
        pet_free(buf);

    }
    else{
        printf("Process 2: Parent\n");
        char * buf2 ;
        buf2= pet_malloc(8096);
        printf("Allocated 1 page at %p\n", buf2);
        pet_dump();
        buf2[3] = 'S';
        buf2[4] = 'E';
        printf("%s\n", (char *)(buf2 + 3));
        pet_free(buf2);
    }

    printf("--------------------------------------------\n");

}
void check_malloc()
{
    printf("Simple Malloc test\n");
    //small block
    init_petmem();
    double * a = pet_malloc(10*sizeof(double));
    printf("Malloced %p \n",a);
    if(a==NULL)
    {
        printf("Malloc does not wor");
    }
    else{
        a[0] = 56.6;
        a[9] = 100.1;
        printf("%f %f\n",a[0],a[9]);
        printf("Malloc works\n");
        pet_free(a);
    }
    printf("--------------------------------------------\n");
    printf("Malloc NULL test\n");
    char *b;
    if ((b = pet_malloc(0))!=NULL)
    {
        printf("Malloc returns non NULL pointer: FAIL\n");
    }
    else
    {
        printf("Malloc returns NULL pointer:PASS\n");
    }
    printf("--------------------------------------------\n");

}
void test_multiple_pages()
{
    printf("Testing multiple pages\n");
    init_petmem();
	int i=0,j;
	char * b[5000];
	for(i=0;i<5000;i++)
	{
		
		b[i] = pet_malloc(32*1024);
		printf("Address %p\n",b[i]);
		
	}
	for(i=0;i<5000;i++)
	{
		
			b[i]='a';
			printf("%c\t %d \t %d\n",b[i],i);
			pet_free(b[i]);
		
	}
    
	
    printf("--------------------------------------------\n");
}
void handle_invalid_address()
{
    printf("Handle invalid address\n");
    init_petmem();
    char * buf;
    buf = 0x1000000123;
    buf[0] = 'c';
    //pet_free(buf);
    //printf("%s\n", (char *)buf[0]);
    printf("--------------------------------------------\n");
}

void check_free()
{
    printf("Freeing NULL\n");
    pet_free(NULL);
    printf("Unaffected: no operation\n");
    printf("--------------------------------------------\n");
}
