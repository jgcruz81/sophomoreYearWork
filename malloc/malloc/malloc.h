//
//  malloc.h
//  malloc
//
//  Created by Juan Cruz on 3/5/19.
//  Copyright © 2019 Juan Cruz. All rights reserved.
//

#ifndef malloc_h
#define malloc_h
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define malloc( x ) mall( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

//MetaNode Struct
struct Node{
    unsigned short block_size:15; //Size of block
    unsigned short is_allocated:1; //Not allocated = 0; Allocated = 1
}Node;

//main memory
static char mainmem[4096];

void* mall(size_t size, char* string, size_t line);
void fee(void* memaddy, char* string, size_t line);
void clean(void);
char* sea(char* starting_block, size_t size);
void printB(int size, void const * const ptr, char *array);


#endif /* malloc_h */
