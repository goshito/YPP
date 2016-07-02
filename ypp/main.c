/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: georgi
 *
 * Created on June 30, 2016, 11:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 200

/*
 * struct array malloc
 */

struct medicine {
    char name[32];
    int mg;
    char dosage[12];
    char producer[32];
};

struct medicine temp_med;

int main(int argc, char** argv) {
    int meds_num;   
    
    int readln(char s[]);
    void init_temp_med();
    void read_meds_data();
    
    printf("WELCOME TO YPP(Your Pills Program\n\n");
    printf("How many medicines you use?\n");
    scanf("%i", &meds_num); // create an array of struct for each medicine
    struct medicine database[meds_num];
    
    read_meds_data();  
   

    return (EXIT_SUCCESS);
}

int readln(char s[]) {
    char ch;
    int i;
    int chars_remain;
    i = 0;
    chars_remain = 1;
    while (chars_remain) {
        ch = getchar();
        if ((ch == '\n') || (ch == EOF)) {
            chars_remain = 0;
        } else if (i < MAXSTRLEN - 1) {
            s[i] = ch;
            i++;
        }
    }
    s[i] = '\0';
    return i;
}

void init_temp_med() {
    strcpy(temp_med.name, "");
    temp_med.mg = 0;
    strcpy(temp_med.dosage, "");
    strcpy(temp_med.producer, "");
}

void read_meds_data() {
    char medicine_name[MAXSTRLEN];
    int mg;
    char dosage[MAXSTRLEN];
    char producer[MAXSTRLEN];
    int slen = 0;
    
    init_temp_med();
    
    while (slen == 0) {
        printf("\nEnter medicine name: ");
        slen = readln(medicine_name);
    }
    
    slen = 0;
    while (slen == 0) {
        printf("\nEnter mg: ");
        slen = readln(mg); // convert it to number using atoi() later?
        //scanf("%i", &mg);
    }
    
    slen = 0;
    while (slen == 0) {
        printf("\nEnter dosage: ");
        slen = readln(dosage);
    }
    
    slen = 0;
    while (slen == 0) {
        printf("\nEnter producer name: ");
        slen = readln(producer);
    }     
    
    strcpy(temp_med.name, medicine_name);
    temp_med.mg = mg;
    strcpy(temp_med.dosage, dosage);
    strcpy(temp_med.producer, producer);    
    
}



