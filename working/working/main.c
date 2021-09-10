#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
void push(struct Node** head, int data)
{
    struct Node* new = (struct Node*) malloc(sizeof(struct Node));
    new->data = data;
    new->next = *head;
    *head = new;
}
void deleteNode(struct Node **head, int data) {
    struct Node* temp = *head, *prev;
    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    
}
void append(struct Node** head, int data) {
    
    struct Node* new = (struct Node*) malloc(sizeof(struct Node));
    struct Node *last = *head;
    new->data  = data;
    new->next = NULL;
    
    while (last->next != NULL){
        if (last->data == data) {
            return;
        }else if(last->data < data && last->next != NULL && last->next->data > data){
            new->next = last->next;
            last->next = new;
            return;
        } else{
            last = last->next;
        }
    }
    if(last->data < data){
        last->next = new;
        return ;
    }
    return;
}

void printList(struct Node *node) {
    struct Node* head = node;
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    printf("%d :", count);
    while (node != NULL) {
        printf(" %d", node->data);
        node = node->next;
    }
}
int main() {
    struct Node* head = NULL;
    int data;
    char c;
    while(scanf(" %c", &c) == 1){
        if(c == 'd'){
            scanf(" %d", &data);
            if (head != NULL && head->data == data) {
                head = head->next;
            }else{
                deleteNode(&head, data);
            }
            printList(head);
            printf("\n");
        }else if(c == 'i'){
            scanf(" %d", &data);
            if (head == NULL|| head->data > data ){
                push(&head, data);
            } else{
                append(&head, data);
            }
            printList(head);
            printf("\n");
        }else{
            break;
        }
    }
    struct Node* tmp;
    
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return 0;
}
