#include "FileX.h"
//#include "functions.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char *argv[]) {
    
    if (argc > 5){
        printf("driver error: less arguements");
        return -1;
    }
    if (strncmp(argv[1], "-R", 2) == 0) {
        //DIR *dir = opendir(".");
        printf("Recursive Case\n");
        if (strncmp(argv[2], "-b", 2) == 0) {
            printf("poop");
        }
        else if (strncmp(argv[2], "-c", 2) == 0) {
            printf("poop");
        }
        else if (strncmp(argv[2], "-d", 2) == 0){
            
        }
    }else{
        if (strncmp(argv[1], "-b", 2) == 0) {
            printf("here\n");
            char *filename = argv[2];
            begin(filename);
        }
        else if (strncmp(argv[1], "-c", 2) == 0) {
            char *filename = argv[2];
            char *huffcb = argv[3];
            compress(filename, huffcb);
        }
        else if (strncmp(argv[1], "-d", 2) == 0){
            char *filename = argv[2];
            char *huffcb = argv[3];
            decompress(filename, huffcb);
            
        }
        return 0;
    }
    
    
}

