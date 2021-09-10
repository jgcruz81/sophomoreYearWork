#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef enum {AND, OR, NOT, NAND, NOR, XOR, MULTIPLEXER, DECODER, PASS} OpType;

typedef struct instruction {
    OpType op;
    int gate;
    struct Node *in;
    struct Node *out;
    struct instruction *next;
    
} instruction;


struct Node
{
    struct Node *next;
    char letter[16];
    int *data;
    int safe;
    int flip;
};

void append(struct Node** head, char string[], int n) {
    struct Node *new = (struct Node*) malloc(sizeof(struct Node));
    struct Node *last = *head;
    if (*head == NULL) {
        strcpy(new->letter, string);
        new->safe = 0;
        new->data = (int*)malloc(sizeof(int) * pow(2, n));
        *head = new;
        return;
    }
    
    while (last->next != NULL){
        last = last->next;
    }
    last->next = (struct Node*) malloc(sizeof(struct Node));
    strcpy(last->next->letter, string);
    last->next->safe = 0;
    last->next->data = (int*)malloc(sizeof(int) * pow(2, n));
    last->next->next = NULL;
    
    return;
}

struct instruction *directive;
struct Node* all;
int icount;
int instructs;
int outnumber;

void add(struct instruction **t){
    struct instruction *last = directive;
    if (directive == NULL) {
        directive = *t;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = *t;
    return;
}

int swap(int a){
    if (a == 0) {
        return 1;
    } else{
        return 0;
    }
}
void flip(struct Node **t, int n){
    struct Node *last = *t;
    int i = 0;
    for (i = 0; i < n; i++) {
        if (last->data[i] == 1) {
            last->data[i] = 0;
        }else{
            last->data[i] = 1;
        }
    }
}
int check(struct Node **t, int n, int k){
    int i = 0;
    int count = 0;
    struct Node *last = *t;
    for (i = 0; i < n; i++) {
        if (last->data[k] == 1) {
            count++;
        }
        last = last->next;
    }
    if (count == n) {
        return 1;
    }
    return 0;
}
void addtobin(char *bin, int n){
    int carry = 1;
    char hold[n];
    int i = 0;
    for (i = n-1; i >= 0 ; i--)
    {
        if (bin[i] == '0' && carry == 0) {
            hold[i] = '0';
            carry = 0;
        }
        else if(bin[i] == '0' && carry == 1){
            hold[i] = '1';
            carry = 0;
        }else if(bin [i] == '1' && carry == 0){
            hold[i] = '1';
            carry = 0;
        } else{
            hold[i] = '0';
            carry = 1;
            
        }
    }
    for (i = 0; i < n; i++) {
        bin[i] = hold[i];
    }
}

int bcombo(struct Node **t, int gate, int it){
    int i = 0;
    char combo[gate];
    struct Node *ptr = *t;
    for (i = 0; i < pow(2, gate); i++) {
        ptr = ptr->next;
    }
    for (i = 0; i < gate; i++) {
         if ((ptr->letter[0] == '0' || ptr->letter[0] == '1') && ptr->letter[1] == '\0') {
             combo[i] = ptr->letter[0];
        }
        else{
            combo[i] = ptr->data[it] + 48;
        }
        
        ptr = ptr->next;
    }
    int val = 0;
    for (i = 0; i < gate; i++) {
        val = 2 * val + (combo[i] - '0');
    }
    return val;
}

void evalInstruction(struct instruction **d,int n) {
    int i = 0;
    struct instruction *t = *d;
    
    if (t->op == MULTIPLEXER) {
        int x = pow(2, t->gate);
        char a[32][16];
        int i = 0;
        struct Node *ptr = t->in;
        struct Node *outvar = all;
        
        while (outvar != NULL) {
            if (strcmp(outvar->letter, t->out->letter) == 0) {
                break;
            }
            outvar = outvar->next;
        }
        
        for (i = 0; i < x; i++) {
            strcpy(a[i], ptr->letter);
            ptr = ptr->next;
        }
        outvar->data = (int*)malloc(sizeof(int) * pow(2, n));
        int combo = 0;
        for (i = 0; i < pow(2, n); i++) {
            ptr = all;
            combo = bcombo(&t->in, t->gate, i);
            if (a[combo][0] == '0') {
                outvar->data[i] = 0;
            }else if (a[combo][0] == '1'){
                outvar->data[i] = 1;
            } else{
                while (ptr != NULL) {
                    if (strcmp(a[combo], ptr->letter) == 0) {
                        outvar->data[i] = ptr->data[i];
                        break;
                    } else{
                        ptr = ptr->next;
                    }
                }
            }
        }
        outvar->safe = 1;
        t->out->safe = 1;
    }
    if (t->op == DECODER) {
        struct Node *ptr = t->in;
        struct Node *outs = t->out;
        char bin[t->gate];
        int i = 0;
        for (i = 0; i<t->gate; i++) {
            bin[i] = '0';
        }
        for(i = 0; i < pow(2, t->gate); i++){
            outs->data = (int*)malloc(sizeof(int) * pow(2, n));
            int j = 0;
            ptr = t->in;
            for (j = 0; j < t->gate; j++) {
                if (bin[j] == '0' && ptr->flip == 0 ) {
                    flip(&ptr, pow(2, n));
                    ptr->flip = 1;
                    ptr->safe = 1;
                }
                else if (bin[j] == '1' && ptr->flip == 1) {
                    flip(&ptr, pow(2, n));
                    ptr->flip = 0;
                }
                ptr = ptr->next;
            }
            int k = 0;
            for ( k = 0; k < pow(2, n); k++) {
                if (check(&t->in,t->gate,k) == 1) {
                    outs->data[k] = 1;
                }else{
                    outs->data[k] = 0;
                }
            }
            
            addtobin(bin,t->gate);
            outs = outs->next;
        }
        outs = t->out;
        while (outs != NULL) {
            ptr = all;
            while (ptr != NULL) {
                if (strcmp(ptr->letter, outs->letter) == 0) {
                    if (ptr->safe == 0) {
                        ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
                        for (i = 0; i < pow(2, n); i ++) {
                            ptr->data[i] = outs->data[i];
                        }
                        ptr->safe = 1;
                    }else{
                        break;
                    }
                }
                else{
                    ptr = ptr->next;
                }
            }
            outs = outs->next;
        }
        t->out->safe = 1;
    }
    if (t->op == AND){
        t->out->data = (int*)malloc(sizeof(int) * pow(2, n));
        for (i = 0; i < pow(2, n); i ++) {
            if (t->in->data[i] == t->in->next->data[i] && t->in->data[i] == 1) {
                t->out->data[i] = 1;
            }else{
                t->out->data[i] = 0;
            }
        }
        t->out->safe = 1;
        struct Node *ptr = all;
        while (ptr != NULL) {
            if (strcmp(ptr->letter, t->out->letter) == 0) {
                if (ptr->safe == 0) {
                    ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
                    for (i = 0; i < pow(2, n); i ++) {
                        ptr->data[i] = t->out->data[i];
                    }
                    ptr->safe = 1;
                }else{
                    break;
                }
            }else{
                ptr = ptr->next;
            }
        }
    }
    if(t->op == OR){
        t->out->data = (int*)malloc(sizeof(int) * pow(2, n));
        for (i = 0; i < pow(2, n); i ++) {
            if (t->in->data[i] == 1 || t->in->next->data[i] == 1) {
                t->out->data[i] = 1;
            }else{
                t->out->data[i] = 0;
            }
        }
        t->out->safe = 1;
        struct Node *ptr = all;
        while (ptr != NULL) {
            if (strcmp(ptr->letter, t->out->letter) == 0) {
                if (ptr->safe == 0) {
                    ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
                    for (i = 0; i < pow(2, n); i ++) {
                        ptr->data[i] = t->out->data[i];
                    }
                    ptr->safe = 1;
                }else{
                    break;
                }
            }else{
                ptr = ptr->next;
            }
        }
    }
    if(t->op == NOT) {
        flip(&t->in, pow(2, n));
        int i = 0;
        t->out->data = (int*)malloc(sizeof(int) * pow(2, n));
        for (i = 0; i < pow(2, n); i++) {
            t->out->data[i] = t->in->data[i];
        }
        t->in->safe = 1;
        t->out->safe = 1;
        
        struct Node *ptr = all;
        while (ptr != NULL) {
            if (strcmp(ptr->letter, t->out->letter) == 0) {
                if (ptr->safe == 0) {
                    ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
                    for (i = 0; i < pow(2, n); i ++) {
                        ptr->data[i] = t->out->data[i];
                    }
                    ptr->safe = 1;
                    break;
                }else{
                    break;
                }
            }else{
                ptr = ptr->next;
            }
        }
    }
    if (t->op == NAND) {
        t->out->data = (int*)malloc(sizeof(int) * pow(2, n));
        for (i = 0; i < pow(2, n); i ++) {
            if (t->in->data[i] == t->in->next->data[i] && t->in->data[i] == 1) {
                t->out->data[i] = 1;
            }else{
                t->out->data[i] = 0;
            }
        }
        t->out->safe = 1;
        flip(&t->out,pow(2, n));
        struct Node *ptr = all;
        while (ptr != NULL) {
            if (strcmp(ptr->letter, t->out->letter) == 0) {
                if (ptr->safe == 0) {
                    ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
                    for (i = 0; i < pow(2, n); i ++) {
                        ptr->data[i] = t->out->data[i];
                    }
                    ptr->safe = 1;
                }else{
                    break;
                }
            }else{
                ptr = ptr->next;
            }
        }
    }
    if (t->op == NOR) {
        t->out->data = (int*)malloc(sizeof(int) * pow(2, n));
        for (i = 0; i < pow(2, n); i ++) {
            if (t->in->data[i] == 1 || t->in->next->data[i] == 1) {
                t->out->data[i] = 1;
            }else{
                t->out->data[i] = 0;
            }
        }
        t->out->safe = 1;
        flip(&t->out,pow(2, n));
        struct Node *ptr = all;
        while (ptr != NULL) {
            if (strcmp(ptr->letter, t->out->letter) == 0) {
                if (ptr->safe == 0) {
                    ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
                    for (i = 0; i < pow(2, n); i ++) {
                        ptr->data[i] = t->out->data[i];
                    }
                    ptr->safe = 1;
                }else{
                    break;
                }
            }else{
                ptr = ptr->next;
            }
        }
    }
    if (t->op == XOR) {
        t->out->data = (int*)malloc(sizeof(int) * pow(2, n));
        for (i = 0; i < pow(2, n); i ++) {
            if (t->in->data[i] == 1 && t->in->next->data[i] == 0) {
                t->out->data[i] = 1;
            }else if(t->in->data[i] == 0 && t->in->next->data[i] == 1){
                t->out->data[i] = 1;
            }else{
                t->out->data[i] = 0;
            }
        }
        t->out->safe = 1;
        struct Node *ptr = all;
        while (ptr != NULL) {
            if (strcmp(ptr->letter, t->out->letter) == 0) {
                if (ptr->safe == 0) {
                    ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
                    for (i = 0; i < pow(2, n); i ++) {
                        ptr->data[i] = t->out->data[i];
                    }
                    ptr->safe = 1;
                }else{
                    break;
                }
            }else{
                ptr = ptr->next;
            }
        }
    }
    if (t->op == PASS) {
        for (i = 0; i < pow(2, n); i ++) {
            if (t->in->data[i] == 1) {
                t->out->data[i] = 1;
            }else{
                t->out->data[i] = 0;
            }
        }
        t->out->safe = 1;
        struct Node *ptr = all;
        while (ptr != NULL) {
            if (strcmp(ptr->letter, t->out->letter) == 0) {
                if (ptr->safe == 0) {
                    ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
                    for (i = 0; i < pow(2, n); i ++) {
                        ptr->data[i] = t->out->data[i];
                    }
                    ptr->safe = 1;
                }else{
                    break;
                }
            }else{
                ptr = ptr->next;
            }
        }
    }
    instructs--;
}

void exec(struct Node *head, int n){
    
    int a = 0, i = 0, z = n, it = 0;
    for (i = 0; i < n; i++) {
        int x = pow(2, z-1);
        int y = x, j = 0;
        while (j < pow(2, n)) {
            int k = 0;
            while (k < y) {
                head->data[it] = a;
                it++;
                k++;
            }
            j = j + y;
            a = swap(a);
        }
        it = 0;
        z = z - 1;
        head->safe = 1;
        head = head->next;
    }
}
int checkvar(struct Node **d, int n){
    struct Node *ptr = *d;
    
    while (ptr != NULL){
        if ((ptr->letter[0] == '0' || ptr->letter[0] == '1') && ptr->letter[1] == '\0') {
            ptr->safe = 1;
            ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
            int i = 0;
            for (i = 0; i < pow(2, n); i++) {
                if (ptr->letter[0] == '0') {
                    ptr->data[i] = 0;
                }else{
                    ptr->data[i] = 1;
                }
            }
            
            
        }
        ptr = ptr->next;
    }
    ptr = *d;
    int ok = 0;
    while (ptr != NULL) {
        while (ptr != NULL && ptr->safe == 1) {
            ptr = ptr->next;
        }
        if (ptr == NULL) {
            return 1;
        }
        struct Node *star = all;
        while (star != NULL) {
            if (strcmp(star->letter, ptr->letter) == 0) {
                break;
            }
            star = star->next;
        }
        int i = 0;
        if (star->safe == 1) {
            ptr->data = (int*)malloc(sizeof(int) * pow(2, n));
            for (i = 0; i < pow(2, n); i++) {
                ptr->data[i] = star->data[i];
            }
            ptr->safe = 1;
            ok = 1;
        } else{
            return 0;
        }
        ptr = ptr->next;
        if (ptr == NULL && ok == 1) {
            return 1;
        }
    }
    return 0;
}
void reada(int n) {
    exec(all, n);
    struct instruction *t = directive;
    
    while (instructs > 0) {
        if (t->out->safe == 0) {
            if (checkvar(&t->in, n) == 1) {
                evalInstruction(&t,n);
            }
        }
            t = t->next;
    }
    int i= 0;
    for (i = 0; i < pow(2, n); i++) {
        struct Node *ptr = all;
        int j = 0;
        for (j = 0; j < n; j++) {
            printf("%d ", ptr->data[i]);
            ptr = ptr->next;
        }
        printf("| ");
        for (j = 0; j < outnumber; j++) {
            if(j == outnumber - 1){
                printf("%d\n", ptr->data[i]);
            }else{
                printf("%d ", ptr->data[i]);
            }
            ptr = ptr->next;
        }
    }
    
}

int readInstructions(FILE *fp, int n) {
    char string[16];
    int i;
    int j;
    while (fscanf(fp, "%s", string) != EOF) {
        struct instruction *t;
        
        if (strcmp(string,"INPUT") == 0) {
            fscanf(fp, "%s", string);
            n = atoi(string);
            
            for (i= 0; i < n; i++) {
                fscanf(fp, "%s", string);
                
                append(&all, string, n);
                icount++;
            }
        }else if (strcmp(string,"OUTPUT") == 0) {
            fscanf(fp, "%s", string);
            int it = atoi(string);
            outnumber = it;
            for (i = 0; i < it; i++) {
                fscanf(fp, "%s", string);
                
                append(&all, string, n);
                icount++;
                
            }
        }else if (strcmp(string,"MULTIPLEXER") == 0) {
            instructs++;
            t = (struct instruction*)malloc(sizeof(struct instruction));
            t->op = MULTIPLEXER;
            fscanf(fp, "%s", string);
            t->gate= atoi(string);
            t->in = NULL;
            t->next = NULL;
            i = 0;
            int x = pow(2, t->gate);
            struct Node *ptr = NULL;
            
            for (i = 0; i < x; i++) {
                fscanf(fp, "%s", string);
                if (string[0] == ':') {
                    fscanf(fp, "%s", string);
                }
                struct Node *point = all;
                for (j = 0; j < icount; j++) {
                    if (strcmp(point->letter, string) == 0) {
                        break;
                    }
                    point = point->next;
                }
                if (j == icount) {
                    append(&all, string, n);
                    icount++;
                }
                if (t->in == NULL) {
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    t->in = p;
                    t->in->data = NULL;
                    ptr = t->in;
                    
                }else{
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    ptr->next = p;
                    ptr = ptr->next;
                    ptr->data = NULL;
                }
                
            }
            for (i = 0; i < t->gate; i++) {
                fscanf(fp, "%s", string);
                if (string[0] == ':') {
                    fscanf(fp, "%s", string);
                }
                struct Node *point = all;
                for (j = 0; j < icount; j++) {
                    if (strcmp(point->letter, string) == 0) {
                        break;
                    }
                    point = point->next;
                }
                if (j == icount) {
                    append(&all, string, n);
                    icount++;
                }
                struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                strcpy(p->letter, string);
                p->safe = 0;
                ptr->next = p;
                ptr = ptr->next;
                ptr->data = NULL;
            }
            
            fscanf(fp, "%s", string);
            struct Node *point = all;
            for (j = 0; j < icount; j++) {
                if (strcmp(point->letter, string) == 0) {
                    break;
                }
                point = point->next;
            }
            if (j == icount) {
                append(&all, string, n);
                icount++;
            }
            struct Node *p = (struct Node*) malloc(sizeof(struct Node));
            strcpy(p->letter, string);
            p->safe = 0;
            t->out = p;
            t->out->data = NULL;
            add(&t);
            
        }else if (strcmp(string,"DECODER") == 0) {
            instructs++;
            t = (struct instruction*)malloc(sizeof(struct instruction));
            t->op = DECODER;
            t->in = NULL;
            t->next = NULL;
            fscanf(fp, "%s", string);
            t->gate = atoi(string);
            int x = pow(2,t->gate);
            struct Node *ptr = NULL;
            
            for (i = 0; i < t->gate; i++) {
                fscanf(fp, "%s", string);
                if (string[0] == ':') {
                    fscanf(fp, "%s", string);
                }
                struct Node *point = all;
                for (j = 0; j < icount; j++) {
                    if (strcmp(point->letter, string) == 0) {
                        break;
                    }
                    point = point->next;
                }
                if (j == icount) {
                    append(&all, string, n);
                    icount++;
                }
                if (t->in == NULL) {
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    p->flip = 0;
                    t->in = p;
                    t->in->data = NULL;
                    ptr = t->in;
                    
                }else{
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    p->flip = 0;
                    ptr->next = p;
                    ptr = ptr->next;
                    ptr->data = NULL;
                }
            }
            t->out = NULL;
            for (i = 0; i < x; i++) {
                fscanf(fp, "%s", string);
                if (string[0] == ':') {
                    fscanf(fp, "%s", string);
                }
                struct Node *point = all;
                for (j = 0; j < icount; j++) {
                    if (strcmp(point->letter, string) == 0) {
                        break;
                    }
                    point = point->next;
                }
                if (j == icount) {
                    append(&all, string, n);
                    icount++;
                }
                if (t->out == NULL) {
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    p->flip = 0;
                    t->out = p;
                    t->out->data = NULL;
                    ptr = t->out;
                    
                }else{
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    p->flip = 0;
                    ptr->next = p;
                    ptr = ptr->next;
                    ptr->data = NULL;
                }
            }
            add(&t);
            
        }else if (strcmp(string,"AND") == 0 || strcmp(string,"OR") == 0) {
            instructs++;
            t = (struct instruction*)malloc(sizeof(struct instruction));
            if (string[0] == 'A') t->op = AND;
            else t->op = OR;
            t->next = NULL;
            t->in = NULL;
            t->out = NULL;
            struct Node *ptr = NULL;
            
            for (i = 0; i < 2; i++) {
                fscanf(fp, "%s", string);
                struct Node *point = all;
                for (j = 0; j < icount; j++) {
                    if (strcmp(point->letter, string) == 0) {
                        break;
                    }
                    point = point->next;
                }
                if (j == icount) {
                    append(&all, string, n);
                    icount++;
                }
                if (t->in == NULL) {
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    p->flip = 0;
                    t->in = p;
                    t->in->data = NULL;
                    ptr = t->in;
                    
                }else{
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    p->flip = 0;
                    ptr->next = p;
                    ptr = ptr->next;
                    ptr->data = NULL;
                }
            }
            fscanf(fp, "%s", string);
            struct Node *point = all;
            for (j = 0; j < icount; j++) {
                if (strcmp(point->letter, string) == 0) {
                    break;
                }
                point = point->next;
            }
            if (j == icount) {
                append(&all, string, n);
                icount++;
            }
            struct Node *p = (struct Node*) malloc(sizeof(struct Node));
            strcpy(p->letter, string);
            p->safe = 0;
            p->flip = 0;
            t->out = p;
            add(&t);
        }
        else if (strcmp(string,"NAND") == 0 || strcmp(string,"NOR") == 0 || strcmp(string,"XOR") == 0) {
            instructs++;
            t = (struct instruction*)malloc(sizeof(struct instruction));
            if (string[1] == 'A') t->op = NAND;
            else if (string[0] == 'N' && string[1] == 'O') t->op = NOR;
            else if (string[0] == 'X') t->op = XOR;
            t->next = NULL;
            t->in = NULL;
            t->out = NULL;
            struct Node *ptr = NULL;
            
            for (i = 0; i < 2; i++) {
                fscanf(fp, "%s", string);
                struct Node *point = all;
                for (j = 0; j < icount; j++) {
                    if (strcmp(point->letter, string) == 0) {
                        break;
                    }
                    point = point->next;
                }
                if (j == icount) {
                    append(&all, string, n);
                    icount++;
                }
                if (t->in == NULL) {
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    p->flip = 0;
                    t->in = p;
                    t->in->data = NULL;
                    ptr = t->in;
                    
                }else{
                    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(p->letter, string);
                    p->safe = 0;
                    p->flip = 0;
                    ptr->next = p;
                    ptr = ptr->next;
                    ptr->data = NULL;
                }
            }
            fscanf(fp, "%s", string);
            struct Node *point = all;
            for (j = 0; j < icount; j++) {
                if (strcmp(point->letter, string) == 0) {
                    break;
                }
                point = point->next;
            }
            if (j == icount) {
                append(&all, string, n);
                icount++;
            }
            struct Node *p = (struct Node*) malloc(sizeof(struct Node));
            strcpy(p->letter, string);
            p->safe = 0;
            p->flip = 0;
            t->out = p;
            t->out->data = NULL;
            add(&t);
            
        }else if (strcmp(string,"PASS") == 0  || strcmp(string,"NOT") == 0) {
            instructs++;
            t = (struct instruction*)malloc(sizeof(struct instruction));
            if (string[0] == 'P') t->op = PASS;
            else t->op = NOT;
            t->next = NULL;
            t->in = NULL;
            t->out = NULL;
            fscanf(fp, "%s", string);
            struct Node *point = all;
            for (j = 0; j < icount; j++) {
                if (strcmp(point->letter, string) == 0) {
                    break;
                }
                point = point->next;
            }
            if (j == icount) {
                append(&all, string, n);
                icount++;
            }
            struct Node *p = (struct Node*) malloc(sizeof(struct Node));
            strcpy(p->letter, string);
            p->safe = 0;
            p->flip = 0;
            t->in = p;
            
            t->in->data = NULL;
            fscanf(fp, "%s", string);
            point = all;
            for (j = 0; j < icount; j++) {
                if (strcmp(point->letter, string) == 0) {
                    break;
                }
                point = point->next;
            }
            if (j == icount) {
                append(&all, string, n);
                icount++;
            }
            struct Node *d = (struct Node*) malloc(sizeof(struct Node));
            strcpy(d->letter, string);
            d->safe = 0;
            d->flip = 0;
            t->out = d;
            t->out->data = NULL;
            add(&t);
        }
    }
    return n;
}


int main(int argc, char *argv[]) {
    FILE *fp;
    
    
    fp = fopen("circuit.txt","r");
    if (fp == NULL) {
        printf("error\n");
        return 0;
    }
    int n = 0;
    n = readInstructions(fp, n);
    
    struct instruction *ptr = directive;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = directive;
    
    reada(n);
    struct Node* tmp;
    
    while (all != NULL)
    {
        tmp = all;
        all = all->next;
        free(tmp);
    }
    
    return 0;
}
