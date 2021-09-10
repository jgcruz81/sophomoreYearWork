#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc,char* argv[]) {
    char poop[300];
    
    int p = 1, z =0,y=0;
    for (p = 1; p < argc; p++) {
        while (argv[p][y] != '\0' ) {
            poop[z] = argv[p][y];
            y++;
            z++;
        }
        y=0;
        if (p != argc-1) {
            poop[z] = ' ';
            z++;
        }
    }
    int size1 = z;
    char ret[z* 2];
    
    int i = 0, inc = 0, count = 1;
    while(i < size1){
        if (isdigit(poop[i])) {
            printf("error");
            return 0;
            
        }
        else if(poop[i] == poop[i+1]){
            count++;
        }
        else if(poop[i] != poop[i+1]){
            ret[inc] = poop[i];
            inc++;
            if(count >= 10 && count <= 99){
                int one = count/10;
                ret[inc] = one + '0';
                inc++;
                int two = count%10;
                ret[inc] = two + '0';
                inc++;
            }
            else {
                ret[inc] = count + '0';
                inc++;
            }
            count = 1;
        }
        i++;
    }
    ret[inc]='\0';
    if (inc <= size1) {
        printf("%s",ret);
    }else{
        printf("%s", poop);
    }
    return 0;
}
