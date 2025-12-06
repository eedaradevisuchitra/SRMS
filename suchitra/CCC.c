#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define DATAFILE "studentdata_list.txt"

/* --- STRUCTURES FOR DATA --- */
typedef struct Student {
    int roll;
    char name[40];
    float marks;
    struct Student *next; // Pointer to the next student in the list
} Student;

typedef struct {
    char username[20];
    char password[20];
    char type[10];
} User;

/* --- GLOBAL DATA --- */
Student *head = NULL; // Head of the linked list
char loggedUser[20];
char loggedType[10];

User predefinedUsers[] = {
    {"admin", "admin123", "admin"},
    {"staff1", "staff123", "staff"},
    {"guest", "guest", "guest"}
};
int totalUsers = 3;

/* --- FUNCTION PROTOTYPES --- */
void secure_input(char *p);
void load_data();
void save_data();
int authenticate();
void home_screen();
void admin_panel();
void staff_panel();
void guest_panel();
void add_student_list();
void display_students_list();
void find_student_list();
void edit_student_list();
void delete_student_list();

// Helper function to create a new Student node
Student* create_student_node(int roll, const char *name, float marks);
// Helper function to find a student by roll number
Student* get_student_by_roll(int roll);
// Helper function to check if roll number exists
int roll_exists(int roll);


/* ---------------- PASSWORD MASKING (Windows Compatible) ---------------- */
void secure_input(char *p) {
    int i = 0;
    int ch;

    while ((ch = _getch()) != '\r' && i < 19) { // '\r' is Enter key
        p[i++] = (char)ch;
        printf("*");
    }
    p[i] = '\0';

    printf("\n");
}

/* ---------------- LOAD DATA INTO LINKED LIST ---------------- */
void load_data() {
    FILE *fp = fopen(DATAFILE, "r");
    Student s;
    Student *current = NULL;

    if (fp == NULL) {
        // Initialize with sample data if file doesn't exist
        fp = fopen(DATAFILE, "w");
        fprintf(fp, "101 Arjun 85.50\n");
        fprintf(fp, "102 Meera 91.20\n");
        fprintf(fp, "103 Virat 78.90\n");
        fprintf(fp, "104 Nisha 93.75\n");
        fclose(fp);
        fp = fopen(DATAFILE, "r"); // Re-open for reading
        printf("Sample data initialized and loaded.\n");
    }

    if (fp != NULL) {
        while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
            Student *new_node = create_student_node(s.roll, s.name, s.marks);
            if (head == NULL) {
                head = new_node;
                current = new_node;
            } else {
                current->next = new_node;
                current = new_node;
            }
        }
        fclose(fp);
    }
}

/* ---------------- SAVE DATA FROM LINKED LIST ---------------- */
void save_data() {
    FILE *fp = fopen(DATAFILE, "w");
    Student *current = head;

    if (fp == NULL) {
        printf("Error saving data to file!\n");
        return;
    }

    while (current != NULL) {
        fprintf(fp, "%d %s %.2f\n", current->roll, current->name, current->marks);
        current = current->next;
    }

    fclose(fp);
}

/* ---------------- LINKED LIST HELPERS ---------------- */
Student* create_student_node(int roll, const char *name, float marks) {
    Student *new_node = (Student *)malloc(sizeof(Student));
    if (new_node == NULL) {
        perror("Failed to allocate memory for new student node");
        exit(EXIT_FAILURE);
    }
    new_node->roll = roll;
    strcpy(new_node->name, name);
    new_node->marks = marks;
    new_node->next = NULL;
    return new_node;
}

Student* get_student_by_roll(int roll) {
    Student *current = head;
    while (current != NULL) {
        if (current->roll == roll) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Not found
}

int roll_exists(int roll) {
    return get_student_by_roll(roll) != NULL;
}


/* ---------------- LOGIN SYSTEM (Unchanged logic) ---------------- */
int authenticate() {
    char u[20], p[20];

    printf("\n========= LOGIN =========\n");
    printf("Enter Username: ");
    scanf("%s", u);

    printf("Enter Password: ");
    getchar();
    secure_input(p);

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(u, predefinedUsers[i].username) == 0 &&
            strcmp(p, predefinedUsers[i].password) == 0) {

            strcpy(loggedUser, u);
            strcpy(loggedType, predefinedUsers[i].type);
            return 1;
        }
    }
    return 0;
}

/* ---------------- HOME SCREEN (Unchanged) ---------------- */
void home_screen() {
    if (strcmp(loggedType, "admin") == 0)
        admin_panel();
    else if (strcmp(loggedType, "staff") == 0)
        staff_panel();
    else
        guest_panel();
}

/* ---------------- ADMIN MENU (Changed function calls) ---------------- */
void admin_panel() {
    int ch;
    while (1) {
        printf("\n===== ADMIN DASHBOARD =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter option: ");
        if (scanf("%d", &ch) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            printf("Invalid Option!\n");
            continue;
        }

        switch (ch) {
            case 1: add_student_list(); break;
            case 2: display_students_list(); break;
            case 3: find_student_list(); break;
            case 4: edit_student_list(); break;
            case 5: delete_student_list(); break;
            case 6: return;
            default: printf("Invalid Option!\n");
        }
    }
}

/* ---------------- STAFF MENU (Changed function calls) ---------------- */
void staff_panel() {
    int ch;
    while (1) {
        printf("\n===== STAFF MENU =====\n");
        printf("1. View Students\n");
        printf("2. Search\n");
        printf("3. Logout\n");
        printf("Choose: ");
        if (scanf("%d", &ch) != 1) {
            while (getchar() != '\n');
            printf("Invalid!\n");
            continue;
        }

        switch (ch) {
            case 1: display_students_list(); break;
            case 2: find_student_list(); break;
            case 3: return;
            default: printf("Invalid!\n");
        }
    }
}

/* ---------------- GUEST MENU (Changed function calls) ---------------- */
void guest_panel() {
    int ch;
    while (1) {
        printf("\n===== GUEST MENU =====\n");
        printf("1. View Students\n");
        printf("2. Logout\n");
        printf("Choose: ");
        if (scanf("%d", &ch) != 1) {
            while (getchar() != '\n');
            printf("Not Allowed!\n");
            continue;
        }

        if (ch == 1) display_students_list();
        else if (ch == 2) return;
        else printf("Not Allowed!\n");
    }
}

/* ---------------- ADD STUDENT (Linked List) ---------------- */
void add_student_list() {
    int roll;
    char name[40];
    float marks;

    printf("Enter Roll No: ");
    scanf("%d", &roll);

    if (roll_exists(roll)) {
        printf("Error: Roll number already exists.\n");
        return;
    }

    printf("Enter Name: ");
    scanf("%s", name);
    printf("Enter Marks: ");
    scanf("%f", &marks);

    Student *new_node = create_student_node(roll, name, marks);

    if (head == NULL) {
        head = new_node;
    } else {
        Student *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    save_data(); // Save changes to the file
    printf("Student Added Successfully!\n");
}

/* ---------------- DISPLAY ALL (Linked List) ---------------- */
void display_students_list() {
    Student *current = head;

    printf("\n--- STUDENT LIST ---\n");
    if (current == NULL) {
        printf("No students records found.\n");
        return;
    }

    while (current != NULL) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", current->roll, current->name, current->marks);
        current = current->next;
    }
}

/* ---------------- SEARCH STUDENT (Linked List) ---------------- */
void find_student_list() {
    int r;

    printf("Enter Roll No to Search: ");
    scanf("%d", &r);

    Student *found_student = get_student_by_roll(r);

    if (found_student != NULL) {
        printf("FOUND: %d | %s | %.2f\n", found_student->roll, found_student->name, found_student->marks);
    } else {
        printf("No student found.\n");
    }
}

/* ---------------- UPDATE STUDENT (Linked List) ---------------- */
void edit_student_list() {
    int r;

    printf("Enter Roll to Update: ");
    scanf("%d", &r);

    Student *found_student = get_student_by_roll(r);

    if (found_student != NULL) {
        printf("Current Roll: %d | Name: %s | Marks: %.2f\n", found_student->roll, found_student->name, found_student->marks);

        printf("New Name (Current: %s): ", found_student->name);
        scanf("%s", found_student->name);

        printf("New Marks (Current: %.2f): ", found_student->marks);
        scanf("%f", &found_student->marks);

        save_data(); // Save changes to the file
        printf("Record Updated!\n");
    } else {
        printf("Record Not Found!\n");
    }
}

/* ---------------- DELETE STUDENT (Linked List) ---------------- */
void delete_student_list() {
    int r;

    printf("Enter Roll to Delete: ");
    scanf("%d", &r);

    Student *current = head;
    Student *prev = NULL;
    int found = 0;

    while (current != NULL) {
        if (current->roll == r) {
            found = 1;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (found) {
        if (prev == NULL) {
            // Deleting the head node
            head = current->next;
        } else {
            // Deleting a non-head node
            prev->next = current->next;
        }
        free(current); // Free memory allocated for the deleted node
        save_data(); // Save changes to the file
        printf("Deleted Successfully!\n");
    } else {
        printf("Record Not Found!\n");
    }
}

/* ---------------- MAIN FUNCTION ---------------- */
int main() {
    load_data(); // Load data into the linked list at startup

    if (authenticate()) {
        home_screen();
    } else {
        printf("Login Failed. Exiting...\n");
    }

    // Note: In this version, save_data is called after every modification (add, edit, delete).
    // In a production system, you might only call it here at the end.
    
    // Free all allocated memory for the linked list before exit
    Student *current = head;
    Student *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    return 0;
}