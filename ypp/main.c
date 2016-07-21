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
 * create a struct array in which the entries to be read - I think I did it create it 
 * 
 * TO DO 16.07.2016:
 * indexing/numeration of stored medicines - done
 * 
 * TO DO 17.07.2016:
 * create modify medicine functionality
 * 
 * TO DO: 21.07.2016:
 * Maybe the variables inside the functions should be global
 * Algorithm to modify medicine
 * I am skipping some input error checking
 * transfer functions to a separate file also use a header file to declare them
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define backupfilename "medicine_database.bak"
#define MAXSTRLEN 200
//#define filename "medicine_database1.bin" for some reason this doesn't work
struct medicine {
    char name[32];
    int mg;
    char dosage[12];
    char producer[32];
};
char filename[] = "medicine_database1.bin";
int medicines_array_len;
struct medicine temp_med, *stored_medicines; // I think that this should be a struct array..not sure

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

int load_stored_medicines(char *filename) {
    FILE *f;
    int number_of_medicines, number_of_read_meds = 0;
    
    number_of_medicines = number_of_stored_medicines(filename);
    f = fopen(filename, "rb");
    if (f == 0) {
        printf("Cannot read file: %s\n", filename);
    } else {
        stored_medicines = (struct medicine *) malloc(sizeof(struct medicine) * number_of_medicines);
        number_of_read_meds = fread(stored_medicines, sizeof(stored_medicines), number_of_medicines, f);
        if (number_of_read_meds != number_of_medicines) {
            printf("Error: %d medicines in file but %d were read into memory", number_of_medicines, number_of_read_meds);
        }
        fclose(f);
    }
    medicines_array_len = number_of_read_meds; // is this necessary?
    return number_of_read_meds;
}

void display_medicines(char * filename) {
    int i, number_of_medicines;
    struct medicine this_medicine;
    
    number_of_medicines = load_stored_medicines(filename);
    for (i = 0; i < number_of_medicines; i++) {
        this_medicine = stored_medicines[i];
        printf("Medicine #%d:\nName: %s %dmg\nScheme: %s\nProducer: %s\n\n", i, this_medicine.name, this_medicine.mg, this_medicine.dosage, this_medicine.producer);
    }
}

void change_medicine(char *filename, int medicine_number) {
    FILE *f;
    struct medicine *medicine_pointer; // medicine pointer doesn't point anywhere
    size_t r, number_of_medicines;
    
    f = fopen(filename, "rb+");
    if (f == 0) {
        printf("Cannot open file: %s\n", filename);
    } else {
        medicine_pointer = (struct medicine *)malloc(sizeof(struct medicine));
        r = fseek(f, medicine_number * sizeof(struct medicine), SEEK_SET);
        r = fread(medicine_pointer, sizeof(struct medicine), 1, f);
        read_meds_data();
        strcpy(medicine_pointer->name, temp_med.name);
        medicine_pointer->mg = temp_med.mg;
        strcpy(medicine_pointer->dosage, temp_med.dosage);
        strcpy(medicine_pointer->producer, temp_med.producer);
        r = fseek(f, medicine_number * sizeof(struct medicine), SEEK_SET); //
        r = fwrite(medicine_pointer, sizeof(struct medicine), 1, f);        
        fclose(f);
        free(medicine_pointer);
    }
}

void modify_stored_medicine() {
    int medicine_number;
    
    printf("Enter number of stored medicine to modify: ");
    scanf("%i", &medicine_number);
    
    change_medicine(filename, medicine_number);
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





