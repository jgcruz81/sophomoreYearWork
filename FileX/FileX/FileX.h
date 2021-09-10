//
//  FileX.h
//  FileX
//
//  Created by Juan Cruz on 3/30/19.
//  Copyright © 2019 Juan Cruz. All rights reserved.
//

#ifndef FileX_h
#define FileX_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

void begin(char filename[]);
void decompress(char filename[], char huffman[]);
void compress(char filename[], char huffman[]);
void match (char string[], int *output);
struct MinTree* search (struct MinTree * node, char letter[]);
void dictionary (int *huff);
void start(char str[], int j);
struct MinTree* find(struct MinTree *node, char letter[]);
void populateRoot(void);
void buildhuff(void);
void insert(struct MinTree **k);
struct MinTree delete(void);
void finalhuff(void);
void inorder(struct MinTree* node, char *byte, int level, int path, int* fd);
struct MinTree* mindelete(struct MinTree* head, char str[]);
struct MinTree* minValueNode(struct MinTree *node);
struct MinTree* dictInsert(struct MinTree* node, struct MinTree* new);
int bigger(char string1[], char string2[]);
int getBalance(struct MinTree *N);
struct MinTree *leftRotate(struct MinTree *x);
struct MinTree *rightRotate(struct MinTree *y);
int max(int a, int b);
int height(struct MinTree *N);



#endif /* FileX_h */
