//
//  main.c
//  mexp
//
//  Created by Juan Cruz on 9/27/18.
//  Copyright © 2018 Juan Cruz. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    FILE *fp1;
    if(argc != 2) {
        printf("\n insufficient arguments.\n");
        return 0;
     }
    
    fp1=fopen(argv[1],"r");
    
    if(fp1==NULL) {
        printf("\n File not created.\n");
        return 0;
    }
    
    int n;
    fscanf(fp1, "%d", &n);
    int i = 0, j = 0, t = 0;
    int arr[n][n];
    
    for (i = 0; i < n; i++) {
        for( j = 0; j < n; j++){
            fscanf(fp1, "%d", &arr[i][j]);
        }
    }
    int k;
    fscanf(fp1, "%d", &k);
    
    if(k == 0){
        for (i = 0; i < n; i++) {
            for( j = 0; j < n; j++){
                if(i == j){
                    if (j != n - 1) {
                        printf("1 ");
                    }else{
                        printf("1");
                    }
                }else{
                    if (j != n - 1) {
                        printf("0 ");
                    }else{
                        printf("0");
                    }
                }
            }
            printf("\n");
        }
        return 0;
    }
    
    int temp[n][n];
    for (i = 0; i < n; i++) {
        for( j = 0; j < n; j++){
            temp[i][j] = arr[i][j];
        }
    }
    for(t = 1; t < k; t++){
        int cont[n][n];
        for (i = 0; i < n; i++) {
            for( j = 0; j < n; j++){
                cont[i][j] = temp[i][j];
            }
        }
        
        int a = 0;
        for (a = 0; a < n; a++) {
            int b = 0;
            for (b = 0; b < n; b++) {
                int sum = 0;
                for (i = 0; i < n; i++) {
                    sum = sum + arr[a][i]*cont[i][b];
                }
                temp[a][b] = sum;
            }
        }
        if(t == k -1){
            for (i = 0; i < n; i++) {
                for( j = 0; j < n; j++){
                    arr[i][j] = temp[i][j];
                }
            }
        }
    }
    for (i = 0; i < n; i++) {
        for( j = 0; j < n; j++){
            printf("%d",arr[i][j]);
            if (j != n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
