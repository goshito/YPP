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
 * TO DO 14.07.2016:
 * implement add medicine option - done
 * system("clear"); might be good at some points - implemented
 * add display meds database 'd' - 1. determine number of meds in the binary file
 * display number of stored meds problem, spils memory - fixed with getchar();
 * must have a struct array, store the data in a struct array!!!
 * 
 * TO DO 15.07.2016:
 * 
 *  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define backupfilename "medicine_database.bak"
#define MAXSTRLEN 200
//#define filename "medicine_database1.bin"
char filename[] = "medicine_database1.bin";

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
        slen = gets(producer);
    }     
    
    strcpy(temp_med.name, medicine_name);
    temp_med.mg = mg;
    strcpy(temp_med.dosage, dosage);
    strcpy(temp_med.producer, producer);    
    
}

void add_medicine(char *filename1) {
    FILE *f;
    
    read_meds_data();
    f = fopen(filename, "ab");
    if (f == 0) {
        printf("Cannot write to file: %s\n", filename);
    } else {
        fwrite(&temp_med, sizeof(temp_med), 1, f);
        fclose(f);
        system("clear");
        printf("Medicine added. \nReturning to main menu.\n\n");
    }
}

void display_main_menu(void) {    
    printf("\nPlease select an option:\n");
    printf("a - Add a medicine to the database\n");
    printf("d - Display list of stored medicines\n");
    printf("m - Modify medicine\n");
    printf("q - End program\n\n");
}    

int number_of_stored_medicines(char *filename) {
    FILE *f;
    int end_position, number_of_stored_meds = 0;
    
    f = fopen(filename, "rb");
    if (f == 0) {
        //printf("Cannot open file: %s", filename);
        return -1;
    }
    else {
        fseek(f, 0, SEEK_END);
        end_position = ftell(f);
        number_of_stored_meds = end_position / sizeof(temp_med);
        fclose(f);
        return number_of_stored_meds;
    }    
}



int main(int argc, char** argv) {
    int meds_count, keep_going = 1;
    
    printf("WELCOME TO YPP(Your Pills Program)\n\n");
    
    while (keep_going) {
        display_main_menu();
        switch(getchar()) {
        case 'a': // add a medicine in database
            system("clear");
            printf("Add a medicine to the database\n");
            add_medicine(filename);
            break;
        case 'd':
            system("clear");
            printf("Display list of stored medicines\n");
            getchar(); //flush
            meds_count = number_of_stored_medicines(filename);
            if (meds_count < 0) {
                system("clear");
                printf("Cannot open file: %s\n", filename);
            }
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

    return (EXIT_SUCCESS);
}





