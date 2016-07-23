#define MAXSTRLEN 200

/*
struct medicine {
    char name[32];
    int mg;
    char dosage[12];
    char producer[32];
};

struct medicine temp_med;
struct medicine *stored_medicines;
int medicines_array_len;
*/
void init_temp_med();
void read_meds_data();
void add_medicine(char *filename1);
void display_main_menu(void);
int number_of_stored_medicines(char *filename);
int load_stored_medicines(char *filename);
void display_medicines(char *filename);
void change_medicine(char *filename, int medicine_number);
void modify_stored_medicine();

