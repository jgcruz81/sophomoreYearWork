//
//  main.c
//  life
//
//  Created by Juan Cruz on 10/2/18.
//  Copyright © 2018 Juan Cruz. All rights reserved.
//

#include<stdio.h>
    #include<stdlib.h>
    #include <ctype.h>

int directional(int rows, int columns, char arr[rows][columns], int up, int down, int left, int right){
    int count = 0;
    int x = up/columns;
    int y = up%columns;
    if (arr[x][y] == '*') {
        count++;
    }
    x = down/columns;
    y = down%columns;
    if (arr[x][y] == '*') {
        count++;
    }
    x = left/columns;
    y = left%columns;
    if (arr[x][y] == '*') {
        count++;
    }
    x = right/columns;
    y = right%columns;
    if (arr[x][y] == '*') {
        count++;
    }
    return count;
}
int diagonal (int rows, int columns, char arr[rows][columns], int topleft, int topright, int botleft, int botright){
    int count = 0;
    int x = topleft/columns;
    int y = topleft%columns;
    if (arr[x][y] == '*') {
        count++;
    }
    x = topright/columns;
    y = topright%columns;
    if (arr[x][y] == '*') {
        count++;
    }
    x = botleft/columns;
    y = botleft%columns;
    if (arr[x][y] == '*') {
        count++;
    }
    x = botright/columns;
    y = botright%columns;
    if (arr[x][y] == '*') {
        count++;
    }
    return count;
}
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

void check(int rows, int columns, char arr[rows][columns], int x, int y, char poop[rows][columns] ){
    int right = mod((rows*x + y + 1), columns)+ columns*x;
    int left  = mod((rows*x + y - 1), columns) + columns*x;
    int n = rows * columns;
    int up = mod((rows*x + y - columns + n), n);
    int down = mod((rows*x + y + columns), n);
    int topleft = left + up - (rows*x + y);
    int topright = right + up - (rows*x + y);
    int botleft = left + down - (rows*x + y);
    int botright = right + down - (rows*x + y);
    int count = directional(rows, columns, arr, up, down, left, right);
    count = count + diagonal(rows, columns, arr, topleft, topright, botleft, botright);
    
    if (arr[x][y] == '.') {
        if (count == 3) {
            poop[x][y] = '*';
        }
    }
    else if(arr[x][y] == '*') {
        if (count < 2 || count > 3) {
            poop[x][y] = '.';
        }
    }
}

int main(int argc,char *argv[])
{
    FILE *fp1;
    char ch[100];
    if(argc != 3) {
        printf("\n insufficient arguments.\n");
        exit(0);
    }
    fp1=fopen(argv[2],"r");
    
    if(fp1==NULL) {
        printf("\n File not created.\n");
        exit(0);
    }
    int i = 0, j = 0;
    while(!feof(fp1)) {
        ch[i]=fgetc(fp1);
        if (ch[i] == '\n') {
            break;
        }
        i++;
    }
    char *ptr;
    long x;
    long y;
    
    x = strtol(ch, &ptr, 10);
    ptr++;
    y = strtol(ch, &ptr, 10);
    
    char life[x][y];
    char poop[x][y];
    char pee;
    
    for(i=0; i<x; i++) {
        for(j=0;j<y;j++) {
            pee = fgetc(fp1);
            life[i][j] = pee;
            poop[i][j] = life[i][j];
        }
        pee = fgetc(fp1);
    }
    char *p;
    long iter = strtol(argv[1], &p, 10);
    int k = 0;
    for (k = 0; k < iter; k ++) {
        for(i=0; i<x; i++) {
            for(j=0;j<y;j++) {
                check(x, y, life, i, j, poop);
            }
        }
        for(i=0; i<x; i++) {
            for(j=0;j<y;j++) {
                life[i][j] = poop[i][j];
            }
        }
    }
    fclose(fp1);
    for(i=0; i<x; i++) {
        for(j=0;j<y;j++) {
            printf("%c",life[i][j]);
        }
        printf("\n");
    }
    return 0;
}
