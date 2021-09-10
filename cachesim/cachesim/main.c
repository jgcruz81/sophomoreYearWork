#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int miss;
int hit;
int mr;
struct line** cache;
unsigned long int count;
int mw;
typedef struct line{
    
    unsigned long int tag;
    int valid;
    unsigned long int time;
    
}line;


/**************************malloc cache funtion**********************/
line** createcache(int setnum,int assoc){
    int i,j;
    cache=(line**)malloc(setnum*sizeof(line*));
    for(i=0;i<setnum;i++){
        cache[i]=(line*)malloc((assoc)*sizeof(line));
    }
    for(i=0;i<setnum;i++){
        for(j=0;j<assoc;j++){
            cache[i][j].valid=0;
            
        }
    }
    return cache;
}



///**************************read mode funtion**********************/
void readsim(unsigned long int tagindex,unsigned long int setindex,int assoc){
    int i,j,min;
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            mr++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                return;
            }
            
            if(i==(assoc-1)){
                miss++;
                mr++;
                
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                return;
            }
        }
    }
}
///**************************write mode funtion**********************/
void writesim(unsigned long int tagindex,unsigned long int setindex,int assoc){
    int i,j,min;
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            mr++;
            mw++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                mw++;
                return;
            }
            if(i==(assoc-1)){
                miss++;
                mr++;
                mw++;
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                return;
            }
        }
    }
}
void empty(int setnum, int assoc){
    int i,j;
    for(i=0;i<setnum;i++){
        for(j=0;j<assoc;j++){
            cache[i][j].tag=0;
            cache[i][j].valid=0;
            cache[i][j].time=0;
            
        }
    }
    miss=0;
    hit=0;
    mr=0;
    mw=0;
    count=0;
}

void prefetchww(unsigned long int tagindex,unsigned long int setindex,int assoc){
    
    int i,j,min;
    
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            mr++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                
                return;
            }
            if(i==(assoc-1)){
                mr++;
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                return;
            }
        }
    }
}
void prefetchrr(unsigned long int tagindex,unsigned long int setindex,int assoc){
    
    int i,j,min;
    
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            
            mr++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                
                return;
            }
            
            if(i==(assoc-1)){
                
                mr++;
                
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                
                
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                return;
            }
        }
    }
}



void prefetchw(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn){
    
    int i,j,min;
    
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            mr++;
            mw++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            prefetchww(tagindexn,setindexn,assoc);
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                mw++;
                return;
            }
            
            if(i==(assoc-1)){
                miss++;
                mr++;
                mw++;
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                prefetchww(tagindexn, setindexn,assoc);
                return;
            }
        }
    }
}
void prefetchr(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn){
    
    
    int i,j,min;
    
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            mr++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            
            prefetchrr(tagindexn,setindexn,assoc);
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                return;
            }
            
            if(i==(assoc-1)){
                miss++;
                mr++;
                
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                prefetchrr(tagindexn,setindexn,assoc);
                return;
            }
            
        }
    }
}
void readsiml(unsigned long int tagindex,unsigned long int setindex,int assoc){
    
    int i,j,min;
    
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            mr++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                count++;
                cache[setindex][i].time=count;
                return;
            }
            
            if(i==(assoc-1)){
                miss++;
                mr++;
                
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                
                
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                
                return;
            }
        }
        
    }
}
///**************************write mode funtion**********************/
void writesiml(unsigned long int tagindex,unsigned long int setindex,int assoc){
    int i,j,min;
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            mr++;
            mw++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                mw++;
                count++;
                cache[setindex][i].time=count;
                return;
            }
            if(i==(assoc-1)){
                miss++;
                mr++;
                mw++;
                min=0;
                for(j=0;j<assoc;j++){
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                return;
            }
        }
    }
}

void prefetchwwl(unsigned long int tagindex,unsigned long int setindex,int assoc){
    int i,j,min;
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            mr++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                
                return;
            }
            if(i==(assoc-1)){
                
                mr++;
                
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                return;
            }
        }
    }
}
void prefetchrrl(unsigned long int tagindex,unsigned long int setindex,int assoc){
    int i,j,min;
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            mr++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                
                return;
            }
            
            if(i==(assoc-1)){
                
                mr++;
                
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                
                
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                return;
            }
        }
    }
    
}
void prefetchwl(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn){
    
    int i,j,min;
    
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            mr++;
            mw++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            prefetchww(tagindexn,setindexn,assoc);
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                mw++;
                count++;
                cache[setindex][i].time=count;
                return;
            }
            
            if(i==(assoc-1)){
                miss++;
                mr++;
                mw++;
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                prefetchww(tagindexn, setindexn,assoc);
                return;
            }
            
        }
        
        
    }
}
void prefetchrl(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn){
    int i,j,min;
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            mr++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].time=count;
            
            prefetchrr(tagindexn,setindexn,assoc);
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                count++;
                cache[setindex][i].time=count;
                return;
            }
            
            if(i==(assoc-1)){
                miss++;
                mr++;
                
                min=0;
                for(j=0;j<assoc;j++){
                    
                    if(cache[setindex][j].time<=cache[setindex][min].time){
                        min=j;
                    }
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                count++;
                cache[setindex][min].time=count;
                prefetchrr(tagindexn,setindexn,assoc);
                return;
            }
        }
    }
}
int main(int argc, char** argv){
    int cachesize=atoi(argv[1]);
    int blocksize=atoi(argv[4]);
    int n;
    int setnum;
    int assoc;
    int b;
    int s;
    char work;
    unsigned long int address;
    unsigned long int newaddress;
    unsigned long int setmask;
    unsigned long int tagindex;
    unsigned long int setindex;
    unsigned long int tagindexn;
    unsigned long int setindexn;
    if(argv[3][0]=='f'){
        FILE* fl;
        fl=fopen(argv[5],"r");
        if(argv[2][0]=='d'){
            assoc=1;
            setnum=cachesize/blocksize;
        }else if(argv[2][5]!=':'){//fullassoc
            setnum=1;
            assoc=cachesize/blocksize;
        }else{//n way associat chache
            sscanf(argv[2],"assoc:%d",&n);
            assoc=n;
            setnum=cachesize/blocksize/n;
            
        }
        b=log(blocksize)/log(2);
        s=log(setnum)/log(2);
        setmask=((1<<s)-1);
        cache=createcache(setnum,assoc);
        while(fscanf(fl, "%*x: %c %lx", &work, &address)==2){
            setindex=(address>>b)&setmask;
            tagindex=address>>(b+s);
            if(work=='R'){
                readsim(tagindex,setindex,assoc);
            }else if(work=='W'){
                writesim(tagindex,setindex,assoc);
            }
        }
        fclose(fl);
        fl=fopen(argv[5],"r");
        printf("no-prefetch\n");
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",mr,mw,hit,miss);
        empty(setnum,assoc);
        while(fscanf(fl, "%*x: %c %lx", &work, &address)==2){
            setindex=(address>>b)&setmask;
            tagindex=address>>(b+s);
            
            newaddress=address+blocksize;
            setindexn=(newaddress>>b)&setmask;
            tagindexn=newaddress>>(b+s);
            if(work=='R'){
                
                prefetchr(tagindex,setindex,assoc,tagindexn,setindexn);
            }else if(work=='W'){
                prefetchw(tagindex,setindex,assoc,tagindexn,setindexn);
            }
        }
        printf("with-prefetch\n");
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",mr,mw,hit,miss);
    }else if(argv[3][0]=='l'){
        FILE* fl;
        fl=fopen(argv[5],"r");
        if(argv[2][0]=='d'){//direct map
            assoc=1;
            setnum=cachesize/blocksize;
            
        }else if(argv[2][5]!=':'){//fullassoc
            setnum=1;
            assoc=cachesize/blocksize;
        }else{//n way associat chache
            
            sscanf(argv[2],"assoc:%d",&n);
            assoc=n;
            setnum=cachesize/blocksize/n;
            
        }
        b=log(blocksize)/log(2);
        s=log(setnum)/log(2);
        setmask=((1<<s)-1);
        cache=createcache(setnum,assoc);
        while(fscanf(fl, "%*x: %c %lx", &work, &address)==2){
            setindex=(address>>b)&setmask;
            tagindex=address>>(b+s);
            if(work=='R'){
                readsiml(tagindex,setindex,assoc);
            }else if(work=='W'){
                writesiml(tagindex,setindex,assoc);
            }
        }
        fclose(fl);
        fl=fopen(argv[5],"r");
        if(fl==NULL){
            printf("cannot find tracefile with that name\n");
            return 0;
        }
        printf("no-prefetch\n");
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",mr,mw,hit,miss);
        empty(setnum,assoc);
        while(fscanf(fl, "%*x: %c %lx", &work, &address)==2){
            setindex=(address>>b)&setmask;
            tagindex=address>>(b+s);
            newaddress=address+blocksize;
            setindexn=(newaddress>>b)&setmask;
            tagindexn=newaddress>>(b+s);
            if(work=='R'){
                prefetchrl(tagindex,setindex,assoc,tagindexn,setindexn);
            }else if(work=='W'){
                prefetchwl(tagindex,setindex,assoc,tagindexn,setindexn);
            }
        }
        printf("with-prefetch\n");
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCachemisses: %d\n",mr,mw,hit,miss);
    }
    return 0;
}
