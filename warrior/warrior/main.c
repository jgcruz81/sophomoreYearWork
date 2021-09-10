//
//  main.c
//  queens
//
//  Created by Juan Cruz on 10/3/18.
//  Copyright © 2018 Juan Cruz. All rights reserved.
//

#include <stdio.h>

int up(char arr[8][8], int x, int y, char poop[8][8]){
    x = x - 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(x >= 0){
            if (arr[x][y] == 'Q' || arr[x][y] == 'W') {
                return 0;
            }else{
                poop[x][y] = '-';
            }
        }else{
            return 1;
        }
        x = x-1;
    }
    return 1;
}
int down(char arr[8][8], int x, int y, char poop[8][8]){
    x = x + 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(x <= 7){
            if (arr[x][y] == 'Q' || arr[x][y] == 'W') {
                return 0;
            }else{
                poop[x][y] = '-';
            }
        }else{
            return 1;
        }
        x = x+1;
    }
    return 1;
}
int left(char arr[8][8], int x, int y, char poop[8][8]){
    y = y - 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(y >= 0){
            if (arr[x][y] == 'Q' || arr[x][y] == 'W') {
                return 0;
            }else{
                poop[x][y] = '-';
            }
        }else{
            return 1;
        }
        y = y-1;
    }
    return 1;
}
int right(char arr[8][8], int x, int y, char poop[8][8]){
    y = y + 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(y <= 7){
            if (arr[x][y] == 'Q' || arr[x][y] == 'W') {
                return 0;
            }else{
                poop[x][y] = '-';
            }
        }else{
            return 1;
        }
        y = y+1;
    }
    return 1;
}
int topleft(char arr[8][8], int x, int y, char poop[8][8]){
    x = x -1;
    y = y - 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(y >= 0 && x >= 0){
            if (arr[x][y] == 'Q' || arr[x][y] == 'W') {
                return 0;
            }else{
                poop[x][y] = '-';
            }
        }else{
            return 1;
        }
        x = x -1;
        y = y - 1;
    }
    return 1;
}
int topright(char arr[8][8], int x, int y, char poop[8][8]){
    x = x-1;
    y = y + 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(y <= 7 && x >= 0){
            if (arr[x][y] == 'Q' || arr[x][y] == 'W') {
                return 0;
            }else{
                poop[x][y] = '-';
            }
        }else{
            return 1;
        }
        x = x-1;
        y = y + 1;
    }
    return 1;
}
int botleft(char arr[8][8], int x, int y, char poop[8][8]){
    x = x +1;
    y = y - 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(y >= 0 && x <= 7){
            if (arr[x][y] == 'Q' || arr[x][y] == 'W') {
                return 0;
            }else{
                poop[x][y] = '-';
            }
        }else{
            return 1;
        }
        x = x+1;
        y = y-1;
    }
    return 1;
}
int botright(char arr[8][8], int x, int y, char poop[8][8]){
    x = x+1;
    y = y + 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(y <= 7 && x <= 7){
            if (arr[x][y] == 'Q' || arr[x][y] == 'W') {
                return 0;
            }else{
                poop[x][y] = '-';
            }
        }else{
            return 1;
        }
        x = x+1;
        y = y+1;
    }
    return 1;
}

int check(char arr[8][8], int x, int y, char poop[8][8] ){
    if(up(arr, x, y, poop) == 1 && down(arr, x, y, poop) == 1){
        
    }else{
        printf("Invalid");
        return 0;
    }
    if(left(arr, x, y, poop) == 1 && right(arr, x, y, poop) == 1){
        
    }else{
        printf("Invalid");
        return 0;
    }
    if(topleft(arr, x, y, poop) == 1 && topright(arr, x, y, poop) == 1){
        
    }else{
        printf("Invalid");
        return 0;
    }
    if(botleft(arr, x, y, poop) == 1 && botright(arr, x, y, poop) == 1){
        return 1;
    }else{
        printf("Invalid");
        return 0;
    }
}
int wartopleft(int x, int y, char poop[8][8]){
    int rad = x - 2;
    int rod = y - 1;
    if(rad >= 0 && rod >= 0){
        if (poop[rad][rod] == 'Q' || poop[rad][rod] == 'W') {
            return 0;
        }
    }
    rad = x - 1;
    rod = y - 2;
    if(rad >= 0 && rod >= 0){
        if (poop[rad][rod] == 'Q' || poop[rad][rod] == 'W') {
            return 0;
        }else{
            return 1;
        }
    }
    return 1;
}
int wartopright(int x, int y, char poop[8][8]){
    int rad = x + 2;
    int rod = y - 1;
    if(rad <= 7 && rod >= 0){
        if (poop[rad][rod] == 'Q' || poop[rad][rod] == 'W') {
            return 0;
        }
    }
    rad = x + 1;
    rod = y - 2;
    if(rad <= 7 && rod >= 0){
        if (poop[rad][rod] == 'Q' || poop[rad][rod] == 'W') {
            return 0;
        }else{
            return 1;
        }
    }
    return 1;
}
int warbotleft(int x, int y, char poop[8][8]){
    int rad = x - 2;
    int rod = y + 1;
    if(rad >= 0 && rod <= 7){
        if (poop[rad][rod] == 'Q' || poop[rad][rod] == 'W') {
            return 0;
        }
    }
    rad = x - 1;
    rod = y + 2;
    if(rad >= 0 && rod <= 7){
        if (poop[rad][rod] == 'Q' || poop[rad][rod] == 'W') {
            return 0;
        }else{
            return 1;
        }
    }
    return 1;
}
int warbotright(int x, int y, char poop[8][8]){
    int rad = x + 2;
    int rod = y + 1;
    if(rad <= 7 && rod <= 7){
        if (poop[rad][rod] == 'Q' || poop[rad][rod] == 'W') {
            return 0;
        }
    }
    rad = x + 1;
    rod = y + 2;
    if(rad <= 7 && rod <= 7){
        if (poop[rad][rod] == 'Q' || poop[rad][rod] == 'W') {
            return 0;
        }else{
            return 1;
        }
    }
    return 1;
}

int warrior(int x, int y, char poop[8][8] ){
    if(wartopleft(x, y, poop) == 1 && wartopright(x, y, poop) == 1){
        
    }else{
        return 0;
    }
    if(warbotleft(x, y, poop) == 1 && warbotright(x, y, poop) == 1){
        return 1;
    }else{
        return 0;
    }
}
int warcheck(char arr[8][8], int x, int y, char poop[8][8]){
    if(up(arr, x, y, poop) == 1 && down(arr, x, y, poop) == 1){
        
    }else{
        printf("Invalid");
        return 0;
    }
    if(left(arr, x, y, poop) == 1 && right(arr, x, y, poop) == 1){
        
    }else{
        printf("Invalid");
        return 0;
    }
    if(topleft(arr, x, y, poop) == 1 && topright(arr, x, y, poop) == 1){
        
    }else{
        printf("Invalid");
        return 0;
    }
    if(botleft(arr, x, y, poop) == 1 && botright(arr, x, y, poop) == 1){
        
    }else{
        printf("Invalid");
        return 0;
    }
    if(wartopleft(x, y, poop) == 1 && wartopright(x, y, poop) == 1){
        int rad = x - 2;
        int rod = y - 1;
        if(rad >= 0 && rod >= 0){
            poop[rad][rod] = '-';
        }
        rad = x - 1;
        rod = y - 2;
        if(rad >= 0 && rod >= 0){
            poop[rad][rod] = '-';
        }
        rad = x + 2;
        rod = y - 1;
        if(rad <= 7 && rod >= 0){
            poop[rad][rod] = '-';
        }
        rad = x + 1;
        rod = y - 2;
        if(rad <= 7 && rod >= 0){
            poop[rad][rod] = '-';
        }
    }else{
        printf("Invalid");
        return 0;
    }
    if(warbotleft(x, y, poop) == 1 && warbotright(x, y, poop) == 1){
        int rad = x - 2;
        int rod = y + 1;
        if(rad >= 0 && rod <= 7){
            poop[rad][rod] = '-';
        }
        rad = x - 1;
        rod = y + 2;
        if(rad >= 0 && rod <= 7){
            poop[rad][rod] = '-';
        }
        
        rad = x + 2;
        rod = y + 1;
        if(rad <= 7 && rod <= 7){
            poop[rad][rod] = '-';
        }
        rad = x + 1;
        rod = y + 2;
        if(rad <= 7 && rod <= 7){
            poop[rad][rod] = '-';
        }
        return 1;
    }else{
        printf("Invalid");
        return 0;
    }
}
int directional(int x, int y, char poop[8][8]){
    int count = 0;
    int rad = x - 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(rad >= 0){
            if (poop[rad][y] == 'q' || poop[rad][y] == 'w') {
                count++;
            }
        }else{
            break;
        }
        rad--;
    }
    rad = x + 1;
    for (i = 0; i < 7; i++) {
        if(rad <= 7){
            if (poop[rad][y] == 'q' || poop[rad][y] == 'w') {
                count++;
            }
        }else{
            break;
        }
        rad++;
    }
    rad = y - 1;
    for (i = 0; i < 7; i++) {
        if(rad >= 0){
            if (poop[x][rad] == 'q' || poop[x][rad] == 'w') {
                count++;
            }
        }else{
            break;
        }
        rad--;
    }
    rad = y + 1;
    for (i = 0; i < 7; i++) {
        if(rad <= 7){
            if (poop[x][rad] == 'q' || poop[x][rad] == 'w') {
                count++;
            }
        }else{
            break;
        }
        rad++;
    }
    return count;
}
int diagonal(int x, int y, char poop[8][8]){
    int count = 0;
    int rad = x - 1;
    int rod = y - 1;
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(rad >= 0 && rod >= 0){
            if (poop[rad][rod] == 'q' || poop[x][y] == 'w') {
                count++;
            }
        }else{
            break;
        }
        rad--;
        rod--;
    }
    rad = x - 1;
    rod = y + 1;
    for (i = 0; i < 7; i++) {
        if(rad >= 0 && rod <= 7){
            if (poop[rad][rod] == 'q' || poop[rad][rod] == 'w') {
                count++;
            }
        }else{
            break;
        }
        rad--;
        rod++;
    }
    rad = x + 1;
    rod = y - 1;
    for (i = 0; i < 7; i++) {
        if(rad <= 7 && rod >= 0){
            if (poop[rad][rod] == 'q' || poop[rad][rod] == 'w') {
                count++;
            }
        }else{
            break;
        }
        rad++;
        rod--;
    }
    rad = x + 1;
    rod = y + 1;
    for (i = 0; i < 7; i++) {
        if(rad <= 7 && rod <= 7){
            if (poop[rad][rod] == 'q' || poop[rad][rod] == 'w') {
                count++;
            }
        }else{
            break;
        }
        rad++;
        rod++;
    }
    return count;
}
int warsontop(int x, int y, char poop[8][8]){
    int count = 0;
    int rad = x - 2;
    int rod = y - 1;
    if(rad >= 0 && rod >= 0){
        if (poop[rad][rod] == 'w' || poop[rad][rod] == 'q') {
            count++;
        }
    }
    rad = x - 1;
    rod = y - 2;
    if(rad >= 0 && rod >= 0){
        if (poop[rad][rod] == 'w' || poop[rad][rod] == 'q') {
            count++;
        }
    }
    rad = x + 2;
    rod = y - 1;
    if(rad <= 7 && rod >= 0){
        if (poop[rad][rod] == 'w' || poop[rad][rod] == 'q') {
            count++;
        }
    }
    rad = x + 1;
    rod = y - 2;
    if(rad <= 7 && rod >= 0){
        if (poop[rad][rod] == 'w' || poop[rad][rod] == 'q') {
            count++;
        }
    }
    return count;
}
int warsonbot(int x, int y, char poop[8][8]){
    int count = 0;
    int rad = x - 2;
    int rod = y + 1;
    if(rad >= 0 && rod <= 7){
        if (poop[rad][rod] == 'w' || poop[rad][rod] == 'q') {
            count++;
        }
    }
    rad = x - 1;
    rod = y + 2;
    if(rad >= 0 && rod <= 7){
        if (poop[rad][rod] == 'w' || poop[rad][rod] == 'q') {
            count++;
        }
    }
    
    rad = x + 2;
    rod = y + 1;
    if(rad <= 7 && rod <= 7){
        if (poop[rad][rod] == 'w' || poop[rad][rod] == 'q') {
            count++;
        }
    }
    rad = x + 1;
    rod = y + 2;
    if(rad <= 7 && rod <= 7){
        if (poop[rad][rod] == 'w' || poop[rad][rod] == 'q') {
            count++;
        }
    }
    return count;
}

int test(int x, int y, char poop[8][8]){
    int sum = 0;
    sum = directional(x, y, poop) + diagonal(x, y, poop);
    if (poop[x][y] == 'w') {
        sum = sum + warsontop(x, y, poop) + warsonbot(x, y, poop);
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    FILE *fp1;
    const char *file;
    
    if (argc == 2) {
        file = argv[1];
    }else if (argc == 3){
        file = argv[2];
    }else if(argc == 4){
        file = argv[3];
    }
    fp1 = fopen(file,"r");
    int i = 0, j = 0;
    char life[8][8];
    char poop[8][8];
    char pee;
    
    for(i=0; i<8; i++) {
        for(j=0;j<8;j++) {
            pee = fgetc(fp1);
            life[i][j] = pee;
            poop[i][j] = life[i][j];
        }
        pee = fgetc(fp1);
    }
    fclose(fp1);
    for (i =0; i <= 7; i ++) {
        for (j = 0; j<= 7; j++) {
            if (life[i][j] == 'Q') {
                if(check(life, i, j, poop) != 1){
                    return 0;
                }
            }
        }
    }
    for (i =0; i <= 7; i ++) {
        for (j = 0; j<= 7; j++) {
            if (life[i][j] == 'W') {
                if(warcheck(life, i, j, poop) != 1){
                    return 0;
                }
            }
        }
    }
    int count = 0;
    for (i =0; i <= 7; i ++) {
        for (j = 0; j<= 7; j++) {
            if (poop[i][j] == '.') {
                poop[i][j] = 'q';
                count++;
            } else if(poop[i][j] == '-'){
                poop[i][j] = '.';
            }
        }
    }
    if (argc > 2) {
        if (argv[1][0] == '-' || argv[2][0] == '-') {
            for (i =0; i <= 7; i ++) {
                for (j = 0; j<= 7; j++) {
                    if (poop[i][j] == 'q') {
                        if (warrior(i, j, poop) == 1) {
                            poop[i][j] = 'w';
                        }
                    }
                }
            }
        }
    }
    
    for(i=0; i<8; i++) {
        for(j=0;j<8;j++) {
            printf("%c",poop[i][j]);
        }
        printf("\n");
    }
    int truecount = count;
    int newcount = 0;
    
    if(argc > 2){
        if (argv[1][0] == '+' || argv[2][0] == '+') {
            for (i =0; i <= 7; i ++) {
                for (j = 0; j<= 7; j++) {
                    if (poop[i][j] == 'q' || poop[i][j] == 'w') {
                        truecount = count - test(i, j, poop);
                        if(truecount > newcount){
                            newcount = truecount;
                        }
                    }
                }
            }
            if (count == 0) {
                printf("Zero");
            }else if (newcount == 1) {
                printf("One");
            }else if(newcount >= 2){
                printf("Two or more");
            }
        }
    }
    return 0;
}
