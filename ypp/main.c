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
 * What exactly does readln function and how does it do it? -replaced with za]otogets()
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
 * create a struct array in which the entries to be read - I think I did it create it 
 * 
 * TO DO 16.07.2016:
 * indexing/numeration of stored medicines - done
 * 
 * TO DO 17.07.2016:
 * create modify medicine functionality
 * 
 * TO DO: 21.07.2016:
 * Maybe the variables inside the functions should be global?
 * Algorithm to modify medicine - from Huw
 * I am skipping some input error checking! will dp later
 * transfer functions to a separate file also use a header file to declare them = not done
 * 
 * TO DO 23.07.2016:
 * transfer functions to a separate file also use a header file to declare them
 * 
 * 24.07.2016: 
 * build'n'run successful
 * 
 * 25.07.2016:
 * review
 * 
 * TO DO 27.05.2016:
 * 
 * TO DO 30.07.2016:
 * 1. run the program, test features and add new ones. New feature to add:
 * Delete all the records stored in file, but how?!!!!
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
//#include "functions.c"
#include "declarations.h"
#define filename "medicine_database1.bin"

int main(int argc, char** argv) {
    int meds_count, keep_going = 1;
    
    printf("WELCOME TO YPP(Your Pills Program)\n\n");
    
    while (keep_going) {
        display_main_menu();
        switch(getchar()) {
            case 'a': // add a medicine in database
                //system("clear");
                printf("\nAdd a medicine to the database\n");
                add_medicine(filename);
                break;
            case 'd':
                system("clear");
                printf("STORED MEDICINES: \n\n");
                getchar(); //flush
                meds_count = number_of_stored_medicines(filename);
                if (meds_count < 0) {
                    printf("Cannot open file: %s\n", filename);
                } else {
                    display_medicines(filename);
                }
                break;
            case 'm':
                //system("clear");
                printf("MODIFY MEDICINE\n\n");
                getchar(); //flush
                //printf("Enter the number of a stored medicine that you wish to modify: ");
                modify_stored_medicine(filename);
                break;
            case 'n':
                printf("Number of records\n");
                printf("Database contains %d records\n", number_of_stored_medicines(filename));
                getchar();
                break;
            case 'c': 
                printf("Clear medicines database\n");
                clear_stored_medicines(filename);
                getchar();
                break;
            case 'q':
                getchar();
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


















