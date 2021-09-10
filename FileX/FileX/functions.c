//
//  functions.c
//  FileX
//
//  Created by Juan Cruz on 3/30/19.
//  Copyright © 2019 Juan Cruz. All rights reserved.
//
#include "FileX.h"
#include <stdio.h>

struct MinTree{
    struct MinTree *west;
    struct MinTree *east;
    struct MinTree *next;
    int occ;
    int data;
    int height;
    char *letter;
    char *byte;
};

int arraysize = 0;
struct MinTree *forbuild = NULL;
struct MinTree *head = NULL;
struct MinTree *dict = NULL;


int height(struct MinTree *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b)? a : b;
}


struct MinTree *rightRotate(struct MinTree *y) {
    struct MinTree *x = y->west;
    struct MinTree *T2 = x->east;
    x->east = y;
    y->west = T2;
    y->height = max(height(y->west), height(y->east))+1;
    x->height = max(height(x->west), height(x->east))+1;
    return x;
}

struct MinTree *leftRotate(struct MinTree *x) {
    struct MinTree *y = x->east;
    struct MinTree *T2 = y->west;
    y->west = x;
    x->east = T2;
    x->height = max(height(x->west), height(x->east))+1;
    y->height = max(height(y->west), height(y->east))+1;
    return y;
}

int getBalance(struct MinTree *N) {
    if (N == NULL)
        return 0;
    return height(N->west) - height(N->east);
}
/*////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////////////////*/

int bigger(char string1[], char string2[]){
    long size1 = strlen(string1);
    long size2 = strlen(string2);
    int i = 0;
    /*begin traversing trying to find "bigger" string*/
    while (size1 != 0 && size2 != 0) {
        
        if (string1[i] > string2[i]) {
            return 0;
        }
        if (string1[i] < string2[i]){
            return 1;
        }
        size1--;
        size2--;
        i++;
    }
    /*larger string is returned*/
    if (size1 > size2) {
        return 0;
    }
    if (size1 < size2) {
        return 1;
    }
    return 2;
}

struct MinTree* dictInsert(struct MinTree* node, struct MinTree* new) {
    if (node == NULL)
        return new;
    if (bigger(new->letter, node->letter) == 1)
        node->west = dictInsert(node->west, new);
    else if (bigger(node->letter, new->letter) == 1)
        node->east = dictInsert(node->east, new);
    else{
        return node;
    }
    
    node->height = 1 + max(height(node->west), height(node->east));
    int balance = getBalance(node);
    
    /* If unbalance occurs there are 4 cases*/
    
    /* Left Left Case*/
    if (balance > 1 && (bigger(new->letter, node->west->letter) == 1)) {
        return rightRotate(node);
    }
    /* Right Right Case*/
    if (balance < -1 && (bigger(node->east->letter, new->letter) == 1))
        return leftRotate(node);
    
    /* Left Right Case*/
    if (balance > 1 && (bigger(node->west->letter, new->letter) == 1))
    {
        node->west =  leftRotate(node->west);
        return rightRotate(node);
    }
    
    /* Right Left Case*/
    if (balance < -1 && (bigger(new->letter, node->east->letter) == 1))
    {
        node->east = rightRotate(node->east);
        return leftRotate(node);
    }
    return node;
}

struct MinTree* minValueNode(struct MinTree *node) {
    struct MinTree* current = node;
    while (current->west != NULL)
        current = current->west;
    
    return current;
}

struct MinTree* mindelete(struct MinTree* head, char str[]) {
    if (head == NULL)
        return head;
    if (bigger(str, head->letter) == 1)
        head->west= mindelete(head->west, str);
    else if (bigger(head->letter, str) == 1)
        head->east = mindelete(head->east, str);
    
    else{
        if ((head->west == NULL) || (head->east == NULL)){
            struct MinTree* temp = NULL;
            if (temp == head->west)
                temp = head->east;
            else
                temp = head->west;
            
            if (temp == NULL) {
                temp = head;
                head = NULL;
            }
            else
                head = temp;
        }else {
            struct MinTree* temp = minValueNode(head->east);
            head->letter = temp->letter;
            head->occ = temp->occ;
            head->east = mindelete(head->east, temp->letter);
        }
    }
    
    if (head== NULL)
        return head;
    
    head->height = max(height(head->west), height(head->east)) + 1;
    int balance = getBalance(head);
    
    /* Left Left Case*/
    if (balance > 1 && getBalance(head->west) >= 0)
        return rightRotate(head);
    
    /* Left Right Case*/
    if (balance > 1 && getBalance(head->west) < 0)
    {
        head->west = leftRotate(head->west);
        return rightRotate(head);
    }
    
    /* Right Right Case*/
    if (balance < -1 && getBalance(head->east) <= 0)
        return leftRotate(head);
    
    /* Right Left Case*/
    if (balance < -1 && getBalance(head->east) > 0)
    {
        head->east = rightRotate(head->east);
        return leftRotate(head);
    }
    
    return head;
}

/*^deletes/////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////////////////*/
/*///////////////////////////////////////////////////////////////////////*/
void inorder(struct MinTree* node, char *byte, int level, int path, int* fd) {
    if (node == NULL) {
        return;
    }
    char *place;
    place = malloc(level);
    if (level != 0) {
        place = memcpy(place, byte, level);
        if(path == 0){
            place[level-1] = '0';
        }else{
            place[level-1] = '1';
        }
        place[level] = '\0';
    }
    
    level++;
    inorder(node->west, place, level, 0, fd);
    
    if (node->data == 1) {
        
        printf("%s\t", place);
        printf("%s\n", node->letter);
        write(*fd, place, level-1);
        char tab = '\t';
        write(*fd, &tab, 1);
        
        int x = (int)strlen(node->letter);
        write(*fd, node->letter, x);
        char newline = '\n';
        write(*fd,&newline, 1);
    }
    inorder(node->east, place, level, 1, fd);
    level--;
    free(place);
    return;
}

void finalhuff(){
    //if root = 0;
    char *byte = malloc(1);
    int fd = open("HuffmanCodebook", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    char start = '\\';
    char newline = '\n';
    write(fd,&start,1);
    write(fd,&newline,1);
    inorder(head, byte, 0, 0, &fd);
    close(fd);
}

struct MinTree delete() {
    struct MinTree a = *head;
    arraysize--;
    head = a.next;
    return a;
}

void insert(struct MinTree **k) {
    // First insert the new key at the end*/
    struct MinTree *last = *k;
    if (arraysize == 0) {
        arraysize++;
        last->next = NULL;
        head = last;
        return;
    }
    arraysize++;
    if (head->occ < last->occ) {
        struct MinTree *ptr = head;
        while (ptr->next != NULL && (ptr->next->occ < last->occ)) {
            ptr = ptr->next;
        }
        if (ptr->next == NULL && (ptr->occ < last->occ)) {
            ptr->next = last;
            last->next = NULL;
            return;
        }
        last->next = ptr->next;
        ptr->next = last;
        
    }else{
        last->next = head;
        head = last;
        return;
    }
    return;
    
}

void buildhuff(){
    if (arraysize == 0) {
        finalhuff();
    }
    struct MinTree a = delete();
    struct MinTree b = delete();
    struct MinTree *z = (struct MinTree*) malloc(sizeof(struct MinTree));
    
    
    z->data = 0;
    z->occ = a.occ + b.occ;
    z->west = &a;
    z->east = &b;
    insert(&z);
    if (arraysize == 1) {
        finalhuff();
        return;
    }
    buildhuff();
    return;
}

void populateRoot(){
    while (forbuild!=NULL){
        struct MinTree* a = (struct MinTree*) malloc(sizeof(struct MinTree));
        a->data = 1;
        a->height = 1;
        a->occ = forbuild->occ;
        a->east = NULL;
        a->west = NULL;
        a->next = NULL;
        int j = (int)strlen(forbuild->letter);
        a->letter = malloc(j+1);
        memcpy(a->letter, forbuild->letter, j);
        a->letter[j] = '\0';
        forbuild = mindelete(forbuild, forbuild->letter);
        insert(&a);
    }
}


struct MinTree* find(struct MinTree *node, char letter[]){
    if (node == NULL)
        return NULL;
    if (bigger(letter, node->letter) == 1)
        return find(node->west, letter);
    else if (bigger(node->letter, letter) == 1)
        return find(node->east, letter);
    else{
        node->occ++;
        return node;
    }
}

void start(char str[], int j){
    
    struct MinTree *found = find(forbuild,str);
    if (found != NULL) {
        return;
    }
    struct MinTree *new = (struct MinTree*) malloc(sizeof(struct MinTree));
    new->data = 1;
    new->occ = 1;
    new->height = 1;
    new->letter = malloc(j+1);
    memcpy(new->letter, str, j+1);
    new->east = NULL;
    new->west = NULL;
    new->next = NULL;
    forbuild = dictInsert(forbuild, new);
}

void begin(char filename[]){
    char str[255];
    memset(&str,'\0',255);
    int file = open(filename, O_RDONLY);
    int j = 0;
    char x;
    
    while (read(file, &x, 1) > 0) {
        if (x == ' ' || x == '\t') {
            while (x == ' ' ||  x == '\t') {
                str[j] = x;
                j++;
                read(file, &x, 1);
            }
            start(str, j);
            j = 0;
            memset(&str,'\0',255);
        }
        while (x != ' ' && x != '\n') {
            if (x == '\\') {
                str[j] = x;
                j++;
            }
            str[j] = x;
            j++;
            read(file, &x, 1);
        }
        start(str, j);
        j = 0;
        memset(&str,'\0',255);
    }
    populateRoot();
    buildhuff();
}

/*////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////////////////*/
void dictionary (int *huff){
    char x;
    char str [255];
    char byte [255];
    memset(&str,'\0',255);
    memset(&byte,'\0',255);
    int j = 0;
    read(*huff, &x, 1);
    read(*huff, &x, 1);
    
    while (read(*huff, &x, 1) > 0) {
        while (x != '\t') {
            byte[j] = x;
            j++;
            read(*huff, &x, 1);
        }
        struct MinTree *z = (struct MinTree*) malloc(sizeof(struct MinTree));
        z->height = 1;
        z->occ = j-1;
        z->byte = malloc(j);
        memcpy(z->byte, byte, j);
        z->east = NULL;
        z->west = NULL;
        
        j = 0;
        read(*huff, &x, 1);
        while (x != '\n') {
            str[j] = x;
            j++;
            read(*huff, &x, 1);
        }
        z->letter = malloc(j+1);
        memcpy(z->letter, str, j+1);
        
        dict = dictInsert(dict, z);
        memset(&str,'\0',255);
        memset(&byte,'\0',255);
        j = 0;
    }
}

struct MinTree* search (struct MinTree * node, char letter[]){
    if (node == NULL){
        printf("search error");
        return NULL;
    }
    if (bigger(letter, node->letter) == 1)
        return search(node->west, letter);
    else if (bigger(node->letter, letter) == 1)
        return search(node->east, letter);
    else{
        return node;
    }
}

void match (char string[], int *output){
    struct MinTree *found = search(dict, string);
    write(*output,found->byte, found->occ);
    //printf("%s: %s %d\n", found->letter, found->byte, found->occ);
}

void compress(char filename[], char huffman[]){
    
    int file = open(filename, O_RDONLY);
    if (file <= 0) {
        printf("compress: file open error");
        return;
    }
    int huff = open(huffman, O_RDONLY);
    if (file <= 0) {
        printf("compress: huffman open error");
        return;
    }
    
    dictionary(&huff);
    close(huff);
    
    int length = (int)strlen(filename);
    char *tocompress = malloc((int)strlen(filename)+5);
    memcpy(tocompress, filename, length);
    char end[5] = ".hcz";
    end[4] = '\0';
    memcpy(tocompress+length, end, 5);
    int output = open(tocompress, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    
    char str[255];
    memset(&str,'\0',255);
    int j = 0;
    char x;
    while (read(file, &x, 1) > 0) {
        if (x == '\n') {
            char newline = '\n';
            write(output,&newline, 1);
        }
        
        while (x != ' ' && x != '\n' ) {
            str[j] = x;
            j++;
            read(file, &x, 1);
        }
        match(str, &output);
        j = 0;
        memset(&str,'\0',255);
        if (x == '\n') {
            char newline = '\n';
            write(output,&newline, 1);
        }
    }
    close(output);
    close(file);
}
void decompress(char filename[], char huffman[]){
    char *p = filename;
    p[strlen(p)-4] = 0;
}
