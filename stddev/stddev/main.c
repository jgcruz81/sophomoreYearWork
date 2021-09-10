//
//  main.c
//  stddev
//
//  Created by Juan Cruz on 9/30/18.
//  Copyright © 2018 Juan Cruz. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


struct Node {
    double data;
    struct Node *next;
};
void push(struct Node** head, double data) {
    struct Node* new = (struct Node*) malloc(sizeof(struct Node));
    new->data  = data;
    new->next = (*head);
    (*head) = new;
}
int numbers_only(const char *s) {
    while (*s) {
        if (isdigit(*s++)) return 0;
    }
    return 1;
}
void printList(struct Node *node) {
    while (node != NULL) {
        printf(" %lf ", node->data);
        node = node->next;
    }
}
double mean(struct Node *node) {
    double sum = 0;
    int count = 0;
    if(node->next == NULL){
        return node->data;
    }
    while (node != NULL) {
        sum = sum + node->data;
        count ++;
        node = node->next;
    }
    if (sum != 0) {
        sum = sum/count;
        return sum;
    }
    return 0;
}
double std(struct Node *node, double mean) {
    double sum = 0;
    double x = 0;
    int count = 0;
    while (node != NULL) {
        x = pow((node->data - mean), 2);
        sum = sum + x;
        count ++;
        node = node->next;
    }
    if (sum != 0) {
        sum = sum/count;
        sum = sqrt(sum);
        return sum;
    }
    return 0;
}
int main(int argc, const char * argv[]) {
    
    struct Node* head = NULL;
    double data;
    char line[256];
    while(scanf("%[^\n]%*c", line) == 1) {
        if (numbers_only(line) == 0) {
            sscanf(line, "%lf", &data);
            push(&head, data);
        }
        if(line[0] == '#'){
            break;
        }
    }
    
    if(head == NULL){
        printf("no data");
        return 0;
    }
    double me = mean(head);
    double sd = std(head, me);
    printf("mean: %.0lf\n",me);
    printf("stddev: %.0lf",sd);
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    
    return 0;
}
