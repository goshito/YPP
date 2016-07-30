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
struct medicine *stored_medicines;
int medicines_array_len;


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
        //scanf("%s", &medicine_name);
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
        //scanf("%s", dosage);
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

void add_medicine(char *filename) {
    FILE *f;
    
    read_meds_data();
    f = fopen(filename, "ab");
    if (f == 0) {
        printf("Cannot write to file: %s\n", filename);
    } else {
        fwrite(&temp_med, sizeof(temp_med), 1, f);
        fclose(f);
        printf("Medicine added. \nReturning to main menu.\n\n");
    }
}

void display_main_menu(void) {    
    printf("\nPlease select an option:\n");
    printf("a - Add a medicine to the database\n");
    printf("d - Display list of stored medicines\n");
    printf("m - Modify medicine\n");
    printf("n - Number of stored medicines\n");
    printf("c - Delete all stored medicines\n");
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

void modify_stored_medicine(char *filename) {
    int medicine_number;
    
    printf("Enter number of stored medicine to modify: ");
    scanf("%i", &medicine_number);
    
    change_medicine(filename, medicine_number);
}

void clear_stored_medicines(char *filename) {
    FILE *f;
    
    f = fopen(filename, "w");
    printf("\nStored medicines deleted\n");
}