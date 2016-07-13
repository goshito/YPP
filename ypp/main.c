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
 * forgotten to write what I did
 * 
 * TO DO 12.07.2016:
 * What exactly does readln function and how does it do it? -replaced with gets()
 * When user enters that he/she uses more than one medicine keep asking until 4 medicines are entered
 * temp_med should go into an array - I already have an array(where to put it?
 * 
 *  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#define filename "medicine_database.bin"
#define backupfilename "medicine_database.bak"
#define MAXSTRLEN 200
#define filename1 "medicine_database1.bin" 

struct medicine {
    char name[32];
    int mg;
    char dosage[12];
    char producer[32];
};

struct medicine temp_med; // I think that this should be a struct array..not sure

// this gives initial values to begin with
void init_temp_med() {
    strcpy(temp_med.name, "");
    temp_med.mg = 0;
    strcpy(temp_med.dosage, "");
    strcpy(temp_med.producer, "");
}

void read_meds_data() { // what should happend after that? what to do with the temp_med structure?
    char medicine_name[MAXSTRLEN];
    int mg;
    char dosage[MAXSTRLEN];
    char producer[MAXSTRLEN];
    int slen = 0; //what is mean "slen", string length? What exactly is the purpose of this variable?
    
    init_temp_med(); //give initial values because if nothing is here the garbage values will
    
    while (slen == 0) {
        printf("\nEnter medicine name: ");        
        getchar(); // flush
        slen = gets(medicine_name); // what does gets() return - This function returns str on success, and NULL on error or when end of file occurs, while no characters have been read.
    }
    
    slen = 0;
    while (slen == 0) {
        printf("\nEnter mg: ");
        scanf("%i", &mg);
        slen = mg;
        getchar(); // flush
    }
    
    slen = 0;
    while (slen == 0) {
        printf("\nEnter dosage: ");
        //slen = readln(dosage);
        slen = gets(dosage);
    }
    
    slen = 0;
    while (slen == 0) {
        printf("\nEnter producer name: ");
        //slen = readln(producer);
        slen = gets(producer);
    }     
    
    strcpy(temp_med.name, medicine_name);
    temp_med.mg = mg;
    strcpy(temp_med.dosage, dosage);
    strcpy(temp_med.producer, producer);    
    
}

void add_medicine(char *filename) {
    FILE *f;
    
    read_meds_data();
    f = fopen(filename1, "rb");
    if (f == 0) {
        printf("Cannot write to file: %s\n", filename1);
    } else {
        fwrite(&temp_med, sizeof(temp_med), 1, f);
        fclose(f);
    }
}

int main(int argc, char** argv) {
    int meds_count, keep_going = 1;
    char choice;
    
    printf("WELCOME TO YPP(Your Pills Program)\n\n");
    printf("Please select an option:\n");
    
    while (keep_going) {
        switch(choice) {
        case 'a': // add a medicine in database
            printf("Add a medicine to the database\n");
            add_medicine(filename1);
            break;
        case 'd':
            printf("Display medicines\n");
            // fill what's necessary here
            break;
        case 'm':
            printf("Modify medicine\n");
            // fill what's necessary here
            break;
        case 'q':
            printf("Ending...\n");
            keep_going = 0;
            break;
        default:
            printf("Invalid command.\n");
            break;
        }
    }
    
    /*
    printf("How many medicines you use? "); //this must be beneath case 'a'
    scanf("%i", &meds_count); // create an array of struct for each medicine
    struct medicine meds_database[meds_count]; //create a struct array to store meds
    
    read_meds_data();  
   */

    return (EXIT_SUCCESS);
}





