//
//  main.c
//  dateBBD
//
//  Created by Juan Cruz on 11/14/18.
//  Copyright © 2018 Juan Cruz. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

int tiempo(float f, char out[]){
    float temp = f;
    int lower = f;
    temp = temp - lower;
    temp = temp * 60;
    int minute = temp;
    float temp2 = temp;
    int lower2 = temp;
    temp2 = temp2 - lower2;
    temp2 = temp2 * 60;
    int second = temp2;
    int hour = f;
    if (hour >= 24) {
        hour = hour - 24;
    }
    out[0] = '0' + hour/10;
    out[1] = '0' + hour%10;
    out[2] = ':';
    out[3] = '0' + minute/10;
    out[4] = '0' + minute %10;
    out[5] = ':';
    out[6] = '0' + second/10;
    out[7] = '0' + second %10;
    //out[8] = '\0';
    return 0;
}
int fecha(int dia, char put[] ){
    int sun[4] = {4,11,18,25};
    int mon[4] = {5,12,19,26};
    int tue[4] = {6,13,20,27};
    int wed[4] = {7,14,21,28};
    int thu[5] = {1,8,15,22,29};
    int fri[5] = {2,9,16,23,30};
    int sat[5] = {3,10,17,24,31};
    if (dia == 0) {
        int d = rand() %4;
        put[8] = '0' + mon[d]/10;
        put [9] = '0' + mon[d]%10;
    }
    if (dia == 1) {
        int d = rand() %4;
        put[8] = '0' + tue[d]/10;
        put [9] = '0' + tue[d]%10;
    }
    if (dia == 2) {
        int d = rand() %4;
        put[8] = '0' + wed[d]/10;
        put[9] = '0' + mon[d]%10;
    }
    if (dia == 6) {
        int d = rand() %4;
        put[8] = '0' + sun[d]/10;
        put[9] = '0' + sun[d]%10;
    }
    if (dia == 3) {
        int d = rand() %5;
        put[8] = '0' + thu[d]/10;
        put[9] = '0' + thu[d]%10;
    }
    if (dia == 4) {
        int d = rand() %5;
        put[8] = '0' + fri[d]/10;
        put[9] = '0' + fri[d]%10;
    }
    if (dia == 5) {
        int d = rand() %5;
        put[8] = '0' + sat[d]/10;
        put[9] = '0' + sat[d]%10;
    }
    //put[8] = '\0';
    return 0;
}

int main(int argc, const char * argv[]) {
    srand ( time(NULL) );
    char x;
    FILE *open;
    open = fopen("open.txt", "r");
    FILE *close;
    close = fopen("close.txt", "r");
    FILE *ftime;
    ftime = fopen("time.txt", "r");
    FILE *bar;
    bar = fopen("bar.txt", "r");
    FILE *output;
    output = fopen("output.txt", "w");
    
    float op[60];
    float cl[60];
    float time[60];
    char b[60][50];
    for (int i = 0; i < 60; i++) {
        fscanf(open, "%f", &op[i]);
        fscanf(close, "%f", &cl[i]);
        fscanf(ftime, "%f", &time[i]);
        //bar
        int j = 0;
        x = fgetc(bar);
        while (x != '\n' ) {
            b[i][j] = x;
            j++;
            x = fgetc(bar);
        }
        b[i][j] = '\0';
    }
    fclose(bar);
    fclose(open);
    fclose(close);
    fclose(ftime);
    FILE *all;
    all = fopen("all.txt", "r");
    int t = 0;
    char bigbar[4800][50];
    for (t = 0; t < 4800; t++) {
        //all
        int j = 0;
        x = fgetc(all);
        while (x != '\n' ) {
            bigbar[t][j] = x;
            j++;
            x = fgetc(all);
        }
        bigbar[t][j] = '\0';
    }
    FILE * date;
    date = fopen("date.txt", "w");
    
    for (int a = 0; a < 4800; a++) {
        for(t = 0; t < 60; t++){
            if (strcmp(bigbar[a], b[t]) == 0) {
                break;
            }
        }
        //Bound 1
        int b1[10] = {1,3,7,12,21,35,59,77,91,100};
        //Bound 2
        int b2[10] = {2,5,11,18,28,42,65,81,93,100};
        //Bound 3
        int b3[10] = {3,8,15,24,36,50,70,85,95,100};
        
        int day[17] = {0,1,1,2,3,3,3,4,4,4,4,5,5,5,5,6,6};
        int dia = rand() %17;
        dia = day[dia];
        
        int bound = rand() % 3 + 1;
        int r = rand() % 101;
        int i = 0;
        if (bound == 1) {
            //use b1
            for (i = 0; i < 10; i++) {
                if (r < b1[i]) {
                    break;
                }
            }
        }else if(bound == 2){
            //use b2
            for (i = 0; i < 10; i++) {
                if (r < b2[i]) {
                    break;
                }
            }
        }else{
            //use b3
            for (i = 0; i < 10; i++) {
                if (r >= b3[i]) {
                    break;
                }
            }
        }
        float f = time[t] *(.1) * i;

        f = op[t] + f;
        if (i != 9) {
            float m = rand() % 100;
            float s = rand() % 100;
            m = m * 60 * .01;
            s = s * 60 *.0001;
            m = (m + s)/60;
            f = f + m;
        }
        char out[8];
        char out2[10];
        //tiempo(f, out);
        out2[0] = '2';
        out2[1] = '0';
        out2[2] = '1';
        out2[3] = '8';
        out2[4] = '-';
        out2[5] ='1';
        out2[6] = '0';
        out2[7] = '-';
        fecha(dia,out2);
        //printf("%s\n", out);
        fprintf(output, "%s\n", out);
        printf("%s\n", out2);
        
    }
    fclose(output);
    
    return 0;
}
