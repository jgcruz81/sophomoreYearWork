#include "malloc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
/*
 * First: If 'size' is larger than meta & main mem size
 * or if 'size' is equal to or below 0, return NULL
 * Second: If created char pointer finds space in main mem
 * return as void pointer
 * else return NULL
 */
void* mall(size_t size, char* string, size_t line){
    //check to make sure the heap isn't full
    if((4094 < size) || size <= 0){
        return NULL;
    }
    //search for a spot, returns NULL if there's no space
    char* ptr = sea(&mainmem[0], size);
    if(ptr == NULL){
        return NULL;
    }
    //void ptr to new memory location
    return (void*)(ptr);
}

void fee(void* memaddy, char* string, size_t line){
    //ptr that will traverse through main mem
    //char* ptr = &mainmem[0];
    int i;
    //this for loop needs to changed
    
    for(i=0; i<4096; i++){
        
    }
}

void printB(int size, void const * const ptr, char *array)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i = 0, j;
    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
}

//Need to find a pointer with enough size and allocated == 0
//i've illusted what needs to be done at the bottom of the header, so you can ignore this sloppy
//code for now
char* sea(char* start, size_t size){
    char begin[0];
    begin[0] = mainmem[0];
    begin[1] = mainmem[1];
    struct Node a;
    a.block_size = 8;
    a.is_allocated = 1;
    memcpy(mainmem, &a, 2);
    
    char array[15];
    char *point = array;
    int i = 0;
    for (i = 2; i > 0; i--) {
        printB(sizeof(begin[0]), &begin[0], point);
    }
    return NULL;
}
//Sets all of the main char array to be empty
void clean(){
    //set everything in the array to 0
    int i;
    for(i=0; i< 4096; i++){
        mainmem[i]= '0';
    }
    //so far idk how else to make metadata without a pointer(size of 8)
    struct Node data;
    data.is_allocated = 0;
    data.block_size = 4094;
}

