#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int r;
int w;
int h;
int m;
int L;

struct cset** cache;
unsigned long int count;

typedef struct cset{
    int valid;
    unsigned long int tag;
    unsigned long int off;
}cset;

cset** create (int set,int a){
    int i,j;
    cache = (cset**)malloc(set*sizeof(cset*));
    
    for(i=0; i<set; i++){
        cache[i]=(cset*)malloc((a)*sizeof(cset));
    }
    for(i=0; i<set; i++){
        for(j=0;j<a;j++){
            cache[i][j].valid=0;
        }
    }
    return cache;
}

void cacheread(unsigned long int tag,unsigned long int set, int a){
    int i,j, z;
    for(i=0; i < a;i++){
        if(cache[set][i].valid == 1){
            if(cache[set][i].tag == tag){
                h++;
                if (L == 1) {
                    count++;
                    cache[set][i].off=count;
                }
                return;
            }
            if(i==(a-1)){
                r++;
                m++;
                z=0;
                for(j=0;j<a;j++){
                    if(cache[set][j].off<=cache[set][z].off){
                        z=j;
                    }
                }
                cache[set][z].valid = 1;
                cache[set][z].tag = tag;
                count++;
                cache[set][z].off = count;
                return;
            }
        }else{
            r++;
            m++;
            count++;
            cache[set][i].valid = 1;
            cache[set][i].tag = tag;
            cache[set][i].off = count;
            return;
        }
    }
}

void cachewrite(unsigned long int tag, unsigned long int set,int a){
    int i,j,k;
    for(i=0;i<a;i++){
        if(cache[set][i].valid==0){
            r++;
            w++;
            m++;
            count++;
            cache[set][i].valid = 1;
            cache[set][i].tag = tag;
            cache[set][i].off = count;
            return;
        }else{
            if(cache[set][i].tag == tag){
                w++;
                h++;
                if (L == 1) {
                    count++;
                    cache[set][i].off=count;
                }
                return;
            }
            if(i==(a-1)){
                r++;
                w++;
                m++;
                k = 0;
                for(j=0;j<a;j++){
                    if(cache[set][j].off<=cache[set][k].off){
                        k=j;
                    }
                }
                cache[set][k].valid=1;
                cache[set][k].tag=tag;
                count++;
                cache[set][k].off=count;
                return;
            }
        }
    }
}

void pww(unsigned long int tag,unsigned long int set,int a){
    int i,j,k;
    for(i=0;i<a;i++){
        if(cache[set][i].valid == 1){
            if(cache[set][i].tag == tag){
                return;
            }
            if(i == (a-1)){
                r++;
                k = 0;
                for(j = 0 ;j < a; j++){
                    if(cache[set][j].off<=cache[set][k].off){
                        k=j;
                    }
                }
                cache[set][k].valid = 1;
                cache[set][k].tag = tag;
                count++;
                cache[set][k].off=count;
                return;
            }
        }else{
            r++;
            count++;
            cache[set][i].valid = 1;
            cache[set][i].tag = tag;
            cache[set][i].off = count;
            return;
        }
    }
}
void prr(unsigned long int tag,unsigned long int set,int a){
    int i,j,k;
    for(i=0;i<a;i++){
        if(cache[set][i].valid == 1){
            if(cache[set][i].tag==tag){
                return;
            }
            if(i==(a-1)){
                r++;
                k = 0;
                for(j = 0; j < a; j++){
                    if(cache[set][j].off<=cache[set][k].off){
                        k=j;
                    }
                }
                cache[set][k].valid = 1;
                cache[set][k].tag = tag;
                count++;
                cache[set][k].off = count;
                return;
            }
        }else{
            r++;
            count++;
            cache[set][i].valid = 1;
            cache[set][i].tag = tag;
            cache[set][i].off = count;
            return;
        }
    }
}
void pw(unsigned long int tag,unsigned long int set,int a,unsigned long int newtag,unsigned long int newset){
    int i,j,k = 0;
    for(i=0;i<a;i++){
        if(cache[set][i].valid==1){
            if(cache[set][i].tag==tag){
                h++;
                w++;
                if (L == 1) {
                    count++;
                    cache[set][i].off=count;
                }
                return;
            }
            if(i==(a-1)){
                m++;
                r++;
                w++;
                k=0;
                for(j=0;j<a;j++){
                    if(cache[set][j].off<=cache[set][k].off){
                        k=j;
                    }
                }
                cache[set][k].valid=1;
                cache[set][k].tag=tag;
                count++;
                cache[set][k].off = count;
                pww(newtag, newset,a);
                return;
            }
        }else{
            r++;
            w++;
            m++;
            count++;
            cache[set][i].valid = 1;
            cache[set][i].tag = tag;
            cache[set][i].off = count;
            pww(newtag,newset,a);
            return;
        }
    }
}
void pr(unsigned long int tag,unsigned long int set,int a,unsigned long int newtag,unsigned long int newset){
    int i,j,k;
    for(i = 0; i < a; i++){
        if(cache[set][i].valid == 1){
            if(cache[set][i].tag == tag){
                h++;
                if(L == 1){
                    count++;
                    cache[set][i].off=count;
                }
                return;
            }
            if(i==(a-1)){
                m++;
                r++;
                k = 0;
                for(j = 0; j<a; j++){
                    if(cache[set][j].off<=cache[set][k].off){
                        k=j;
                    }
                }
                cache[set][k].valid = 1;
                cache[set][k].tag = tag;
                count++;
                cache[set][k].off=count;
                prr(newtag,newset,a);
                return;
            }
        }else{
            r++;
            m++;
            count++;
            cache[set][i].valid = 1;
            cache[set][i].tag = tag;
            cache[set][i].off = count;
            prr(newtag, newset,a);
            return;
        }
    }
}

int main(int argc, char** argv){
    int cachesize = atoi(argv[1]);
    int blocksize = atoi(argv[5]);
    int n, set, assoc, b, s;
    char instruct;
    unsigned long int address, setmask, tindex, sindex, newtindex, newsindex;
    FILE* file;
    file = fopen(argv[6],"r");
    
    if(argv[2][0]=='d'){
        assoc = 1;
        set = cachesize/blocksize;
    }else if(argv[2][5]!=':'){
        assoc = cachesize/blocksize;
        set = 1;
    }else{
        sscanf(argv[2],"assoc:%d",&n);
        assoc = n;
        set = cachesize/blocksize/n;
        
    }
    b = log(blocksize)/log(2);
    s = log(set)/log(2);
    setmask=((1<<s)-1);
    cache = create(set,assoc);
    
    if(argv[4][0]=='f'){
        L = 0;
    }else{
        L = 1;
    }
    if (argv[3][1] == '0') {
        while(fscanf(file, "%*x: %c %lx", &instruct, &address)==2){
            sindex=(address>>b)&setmask;
            tindex=address>>(b+s);
            if(instruct=='R'){
                cacheread(tindex,sindex,assoc);
            }else{
                cachewrite(tindex,sindex,assoc);
            }
        }
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",r,w,h,m);
    } else{
        while(fscanf(file, "%*x: %c %lx", &instruct, &address)==2){
            sindex=(address>>b)&setmask;
            tindex=address>>(b+s);
            address=address+blocksize;
            newsindex=(address>>b)&setmask;
            newtindex=address>>(b+s);
            if(instruct=='R'){
                pr(tindex,sindex,assoc,newtindex,newsindex);
            }else{
                pw(tindex,sindex,assoc,newtindex,newsindex);
            }
        }
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",r,w,h,m);
    }
    return 0;
}
