#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    
    argc = 4;
    argv[1] = "poop";
    argv[2] = "caca";
    argv[3] = "poop";
    if (argc == 1) {
        return 0;
    }
    char poop[200];
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
    poop[z] = '\0';
    z = z-1;
    int i = 0;
    char lower[26] = "abcdefghijklmnopqrstuvwxyz";
    char upper[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int num = 0;
    while(i <= z){
        if (poop[i] >= 'A' && poop[i] <= 'Z'){
            num = poop[i] - 'A';
            if(num >= 13){
                num = num - 13;
                poop[i] = upper[num];
            }else{
                num = num + 13;
                poop[i] = upper[num];
            }
        }
        else if (poop[i] >= 'a' && poop[i] <= 'z'){
            num = poop[i] - 'a';
            if(num >= 13){
                num = num - 13;
                poop[i] = lower[num];
            }else{
                num = num + 13;
                poop[i] = lower[num];
            }
        }
        i++;
    }
    printf("%s", poop);
    return 0;
}
