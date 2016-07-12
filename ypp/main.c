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

/* TO DO 11.07.2016:
 *  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 200

struct medicine {
    char name[32];
    int mg;
    char dosage[12];
    char producer[32];
};

struct medicine temp_med;

int main(int argc, char** argv) {
    int meds_count;   
    
    int readln(char s[]); // why the fuck I need you stupid function
    void init_temp_med(); // what this init do?
    void read_meds_data(); // what do you mean "reading them"?
    
    printf("WELCOME TO YPP(Your Pills Program\n\n");
    printf("How many medicines you use?\n");
    scanf("%i", &meds_count); // create an array of struct for each medicine
    struct medicine meds_database[meds_count]; //create a struct array to store meds
    
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
// this gives initial values to begin with
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
    int slen = 0; //wtf?
    
    init_temp_med();
    
    while (slen == 0) {
        printf("\nEnter medicine name: ");
        slen = readln(medicine_name); // what is slen for?
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



