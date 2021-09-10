//
//  main.c
//  csvfile
//
//  Created by Juan Cruz on 10/24/18.
//  Copyright © 2018 Juan Cruz. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    FILE *fp1;
    fp1=fopen("lastnames.txt","r");
    char str[200][255];
    char x;
    int i = 0, j = 0;
    for (i = 0; i < 200; i++) {
        x = fgetc(fp1);
        while (x != '\n' ) {
            str[i][j] = x;
            j++;
            x = fgetc(fp1);
        }
        str[i][j] = '\0';
        j = 0;
    }
    int phone[400][10];
    srand ( time(NULL) );
    for (i = 0; i < 400; i++) {
        for (j = 0; j < 10; j++) {
            int r = rand() % 10;
            phone[i][j] = r;
        }
    }
    FILE * fp3;
    fp3 = fopen ("new.txt","w");
    for (j = 0; j < 400; j++) {
        for(i = 0; i < 10; i++){
            fprintf (fp3, "%d", phone[j][i]);
        }
        fprintf(fp3,"\n");
    }
    
    fclose (fp3);
    
    char street[465][20];
    char lane [6][20];
    FILE *fp;
    fp = fopen ("street.txt","r");
    //populate street
    j = 0;
    for (i = 0; i < 465; i++) {
        x = fgetc(fp);
        while (x != '\n' ) {
            street[i][j] = x;
            j++;
            x = fgetc(fp);
        }
        street[i][j] = '\0';
        j = 0;
    }
    FILE *fp2;
    fp2 = fopen ("lane.txt","r");
    //populate lane
    j = 0;
    for (i = 0; i < 6; i++) {
        x = fgetc(fp2);
        while (x != '\n' ) {
            lane[i][j] = x;
            j++;
            x = fgetc(fp2);
        }
        lane[i][j] = '\0';
        j = 0;
    }
    //make address
    char address[600][256];
    srand ( time(NULL) );
    int y = 0;
    int inc = 0;
    for (i = 0; i < 600; i++) {
        int ront = rand() % (3) + 1;
        j = 0;
        for (int pee = 0;pee < ront; pee++) {
            int rant = rand() % (9) + 1;
            address[i][j] = rant + 48;
            j++;
        }
        address[i][ront] = ' ';
        ront++;
        int r = rand() % 380;
        int streetstart = 0;
        for (j = ront; j < 40; j++) {
            address[i][j] = street[r][streetstart];
            if(street[r][streetstart+1] == '\0'){
                break;
            }
            streetstart++;
        }
        j++;
        if(r%10 == 0){
            address[i][j] = ' ';
            j++;
            r = rand() % 80;
            for (y = j; y < 40; y++) {
                address[i][y] = street[r][inc];
                if(street[r][inc+1] == '\0'){
                    break;
                }
                inc ++;
            }
            inc = 0;
            j = y +1;
        }
        address[i][j] = ' ';
        r = rand() % 6;
        j++;
        for (y = 0; y < 40; y++) {
            address[i][j] = lane[r][y];
            if(lane[r][y+1] == '\0'){
                break;
            }
            j++;
        }
        address[i][j+1] = '\0';
    }
    for (int a = 0; a < 600; a++) {
        printf("%s\n", address[a]);
    }
    return 0;
}
