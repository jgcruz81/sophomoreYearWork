#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct Node
{
    struct Node *next;
    char *letter;
};
/*
 linked list struct
 next points to next node
 char pointer holds token
 */

int bigger(char string1[], char string2[]){
    long size1 = strlen(string1);
    long size2 = strlen(string2);
    int i = 0;
    /*begin traversing trying to find "bigger" string*/
    while (size1 != 0 && size2 != 0) {
        /*
         if either string contains a capital letter
         and the other doesn't, return "bigger" string
         */
        if (string1[i] <= 90 && string2[i] >= 97) {
            return 0;
        }
        if (string1[i] >= 97 && string2[i] <= 90) {
            return 1;
        }
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
    return 1;
}
void append(struct Node** head, char string[], int n) {
    struct Node *new = (struct Node*) malloc(sizeof(struct Node));
    new->letter = NULL;
    struct Node *last = *head;
    /*first node to be added*/
    if (*head == NULL) {
        new->letter = (char*)malloc(sizeof(char) * n);
        memset(new->letter, '\0', n+1);
        new->next = NULL;
        memcpy(new->letter, string, n);
        *head = new;
        return;
    }
    /*3 places to add a node
     1. before head*/
    if (bigger(last->letter, string)) {
        new->next = *head;
        new->letter = (char*)malloc(sizeof(char) * n);
        memset(new->letter, '\0', n+1);
        memcpy(new->letter, string, n);
        *head = new;
        return;
    }
    else{
        while (last->next != NULL) {
            /*2. between 2 nodes*/
            if (bigger(string, last->letter) && bigger(last->next->letter, string)) {
                new->next = last->next;
                last->next = new;
                new->letter = (char*)malloc(sizeof(char) * n);
                memset(new->letter, '\0', n+1);
                memcpy(last->next->letter, string, n);
                return;
            }
            last = last->next;
        }
    }
    /*3. after head*/
    last->next = new;
    new->letter = (char*)malloc(sizeof(char) * n);
    memset(new->letter, '\0', n+1);
    memcpy(last->next->letter, string, n);
    last->next->next = NULL;
    return;
}

int main(int argc, const char * argv[]) {
    /*only allow 2 arguments*/
    
    int j = 0, i = 0;
    char t[] = "what'\r'is'\0'up";
    char c = t[0];
    
    struct Node *head = NULL;
    
    while (j < strlen(t)) {
        if ((c >= 65 && c <= 90)||(c >= 97 && c <= 122)){
            i = j;
            while ((c >= 65 && c <= 90)||(c >= 97 && c <= 122)) {
                j++;
                c = *(t+j);
            }
            char z[j-i];
            memset(z, '\0', j-i+1);
            strncpy(z, t + i, j-i);
            /*add node to list of nodes*/
            append(&head, z, j -i);
            memset(z, '\0', j-i+1);
        }
        j++;
        c = *(t+j);
    }
    /*begin printing in order and freeing*/
    while (head != NULL) {
        struct Node *current = head;
        head = head->next;
        printf("%s\n",current->letter);
        free(current->letter);
        free(current);
    }
    return 0;
}
