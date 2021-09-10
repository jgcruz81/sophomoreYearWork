#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};
struct Node *newNode(int data) {
    struct Node *temp =  (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d \n", root->data);
        inorder(root->right);
    }
}
void inorderdel(struct Node *node) {
    if (node != NULL){
        inorderdel(node->left);
        inorderdel(node->right);
        free(node);
    }
    return;
    
}

void printInorder(struct Node *node) {
    if (node == NULL){
        return;
    }
    printf("(");
    printInorder(node->left);
    printf("%d", node->data);
    printInorder(node->right);
    printf(")");
}

struct Node* insert(struct Node* node, int data) {
    if (node == NULL) return newNode(data);
    
    if (node->data > data){
        node->left  = insert(node->left, data);
    }
    else if (node->data < data){
        node->right = insert(node->right, data);
    }
    return node;
}
int search(struct Node* root, int data) {
    if(root == NULL){
        return 1;
    }
    if (root->data == data){
        return 0;
    }
    if (root->data < data)
        return search(root->right, data);
    
    return search(root->left, data);
}
struct Node *poop(struct Node *node) {
    struct Node *current = node;
    
    while (current->right != NULL)
        current = current->right;
    
    return current;
}
struct Node *deleteNode(struct Node *root, int data) {
    if (root == NULL) return root;
    
    if (root->data > data){
        root->left = deleteNode(root->left, data);
    }
    else if (root->data < data){
        root->right = deleteNode(root->right, data);
    }
    
    else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        struct Node *temp = poop(root->left);
        
        root->data = temp->data;
        
        root->left = deleteNode(root->left, temp->data);
    }
    return root;
}

int main() {
    struct Node *head = NULL;
    int data;
    char line[1];
    while(scanf(" %c", line) == 1){
        if(*line == 'd'){
            scanf(" %d", &data);
            if(search(head, data) == 0){
                head = deleteNode(head, data);
                printf("deleted");
                printf("\n");
            } else{
                printf("absent");
                printf("\n");
            }
        }else if(*line == 'i'){
            scanf(" %d", &data);
            if (head == NULL) {
                head = insert(head, data);
                printf("inserted");
                printf("\n");
            }else {
                if(search(head, data) == 0){
                    printf("duplicate");
                    printf("\n");
                    
                } else{
                    insert(head, data);
                    printf("inserted");
                    printf("\n");
                }
            }
        }else if(*line == 's'){
            scanf(" %d", &data);
            if(search(head, data) == 0){
                printf("present");
                printf("\n");
                
            } else{
                printf("absent");
                printf("\n");
            }
        }else if(*line == 'p'){
            printInorder(head);
            printf("\n");
        }
        else{
            break;
        }
    }
    inorderdel(head);
    return 0;
}
