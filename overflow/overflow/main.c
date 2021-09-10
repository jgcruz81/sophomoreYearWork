//
//  main.c
//  overflow
//
//  Created by Juan Cruz on 2/19/19.
//  Copyright © 2019 Juan Cruz. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
//BEING USED
struct real{
    unsigned short block_size: 15;
    unsigned short is_allocated: 1;
} real;

struct switchh{
    unsigned short is_allocated: 1;
    unsigned short block_size: 15;
} switchh;

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main()
{
    //char buffer[10];
    char array[10];
    char second[10];
    
    struct real a;
    a.block_size = 4000;
    a.is_allocated = 1;
    
    struct switchh s;
    s.is_allocated = 1;
    s.block_size = 16;
    
    
    //unsigned short x = a.block_size;
    //byte = &buffer[0];
    memcpy(second, &s, 2);
    memcpy(array, &a, 2);
    printf("real: \n");
    printBits(sizeof(array[0]), &array[0]);
    //printf("\n");
    printBits(sizeof(array[1]), &array[1]);
    //printf("\n");
    printf("switch: \n");
    printBits(sizeof(second[0]), &second[0]);
    //printf("\n");
    printBits(sizeof(second[1]), &second[1]);
    //printf("\n");
    
    char input[15] = "000111110100000";
    int result= 0;
    int count = 0;
    int z = 1;
    
    for(count = 14; count > 0; count--)
    {
        if(input[count] == '1')
        {
            result += z;
        }
        z <<= 1;
    }
    printf("%d", result);
    
    int *p = malloc(1);
    int x = sizeof(p);
    //printf("%d", sizeof(p));
    return 0;
    //key_t;
    
    
}
void review (){
    int * ptr = (int*)malloc(sizeof(int)*2);
    char *repoint  = (char*) ptr;
    
    //ptr == repoint
    //ptr++ > ++ repoint
    //++ptr >/< ++repoint
    //what would happen if yuou did not incrememnt the address of the buffer you issue a
    //non blocking write from as you loop
    //a non blocking io call will return in two cases: when its finished, when you told it to return
    //error?
    //p node doesnt have meta data point to other p nodes
}
