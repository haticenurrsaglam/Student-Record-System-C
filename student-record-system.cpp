#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void add_student();
void list_students();
void update_student();
void delete_student();
void class_average();
void top_student();
void save_records();
void load_records();
void menu();

typedef struct node {
    char name[50];
    int  id;
    float midterm;
    float final;
    struct node* next;
} Student;

Student* head = NULL;

float average(Student* n) {
    return (n->midterm * 0.4f + n->final * 0.6f);
}

int main(void) {
    int choice = 0;

    load_records();

    while (1) {
        menu();

        printf("Enter choice (1-7): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input!\n");
            continue;
        }

        switch (choice) {
            case 1: add_student();    break;
            case 2: list_students();  break;
            case 3: update_student(); break;
            case 4: delete_student(); break;
            case 5: class_average();  break;
            case 6: top_student();    break;
            case 7:
                save_records();
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please enter between 1-7.\n");
        }
    }

    return 0;
}

void menu() {
    printf("\n====== MENU ======\n");
    printf("1 - Add Student\n");
    printf("2 - List Students\n");
    printf("3 - Update Student\n");
    printf("4 - Delete Student\n");
    printf("5 - Class Average\n");
    printf("6 - Top Student\n");
    printf("7 - Exit\n");
    printf("==================\n");
}

void add_student() {
    Student* new_std = (Student*)malloc(sizeof(Student));

    if (new_std == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    new_std->next = NULL;

    printf("Name: ");
    scanf(" %49[^\n]", new_std->name);

    printf("ID: ");
    scanf("%d", &new_std->id);


    Student* check = head;
    while (check != NULL) {
        if (check->id == new_std->id) {
            printf("This ID is already registered!\n");
            free(new_std);
            return;
        }
        check = check->next;
    }

    printf("Midterm grade: ");
    do {
        scanf("%f", &new_std->midterm);
        if (new_std->midterm < 0 || new_std->midterm > 100)
            printf("Invalid grade! Enter between 0-100: ");
    } while (new_std->midterm < 0 || new_std->midterm > 100);

    printf("Final grade: ");
    do {
        scanf("%f", &new_std->final);
        if (new_std->final < 0 || new_std->final > 100)
            printf("Invalid grade! Enter between 0-100: ");
    } while (new_std->final < 0 || new_std->final > 100);

    if (head == NULL) {
        head = new_std;
    } else {
        Student* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_std;
    }

    printf("Student added successfully.\n");
}

void list_students() {
    int option;
    int found = 0;

    printf("\nSearch Menu:\n");
    printf("1 - Search by ID\n");
    printf("2 - Search by Name\n");
    printf("3 - List students with average >= 60\n");
    printf("Choice: ");
    scanf("%d", &option);

    Student* temp = head;

    if (option == 1) {
        int search_id;
        found = 0;
        printf("Enter ID: ");
        scanf("%d", &search_id);

        while (temp != NULL) {
            if (temp->id == search_id) {
                printf("Name    : %s\n",temp->name);
                printf("ID      : %d\n",temp->id);
                printf("Midterm : %.2f\n", temp->midterm);
                printf("Final   : %.2f\n", temp->final);
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found)
            printf("No student found with this ID.\n");

    } else if (option == 2) {
        char search_name[50];
        found = 0;
        printf("Enter name: ");
        scanf(" %49[^\n]", search_name);
 
        while (temp != NULL) {
            if (strcmp(temp->name, search_name) == 0) {
                printf("Name    : %s\n",temp->name);
                printf("ID      : %d\n", temp->id);
                printf("Midterm : %.2f\n", temp->midterm);
                printf("Final   : %.2f\n", temp->final);
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found)
            printf("No student found with this name.\n");

    } else if (option == 3) {
        found = 0;
        while (temp != NULL) {
            if (average(temp) >= 60.0f) {
                printf("Name    : %s\n",   temp->name);
                printf("ID      : %d\n",   temp->id);
                printf("Midterm : %.2f\n", temp->midterm);
                printf("Final   : %.2f\n", temp->final);
                printf("Average : %.2f\n", average(temp));
                printf("----------\n");
                found = 1;
            }
            temp = temp->next;
        }
        if (!found)
            printf("No students with average >= 60 found.\n");

    } else {
        printf("Invalid choice!\n");
    }
}

void update_student() {
    int search_id, found = 0;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Enter ID of student to update: ");
    scanf("%d", &search_id);

    Student* temp = head;

    while (temp != NULL) {
        if (temp->id == search_id) {
            printf("New name: ");
            scanf(" %49[^\n]", temp->name);

            printf("New ID: ");
            scanf("%d", &temp->id);

            printf("New midterm grade: ");
            do {
                scanf("%f", &temp->midterm);
                if (temp->midterm < 0 || temp->midterm > 100)
                    printf("Invalid grade! Enter between 0-100: ");
            } while (temp->midterm < 0 || temp->midterm > 100);

            printf("New final grade: ");
            do {
                scanf("%f", &temp->final);
                if (temp->final < 0 || temp->final > 100)
                    printf("Invalid grade! Enter between 0-100: ");
            } while (temp->final < 0 || temp->final > 100);

            printf("\n--- Updated ---\n");
            printf("Name    : %s\n", temp->name);
            printf("ID      : %d\n", temp->id);
            printf("Midterm : %.2f\n", temp->midterm);
            printf("Final   : %.2f\n", temp->final);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found)
        printf("No student found with this ID.\n");
}

void delete_student() {
    if (head == NULL) {
        printf("List is empty, nothing to delete.\n");
        return;
    }

    int del_id;
    printf("Enter ID to delete: ");
    scanf("%d", &del_id);

    Student* temp = head;
    Student* prev = NULL;

    while (temp != NULL) {
        if (temp->id == del_id) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;
            free(temp);
            printf("Student deleted successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("No student found with this ID.\n");
}

void class_average() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    float midterm_sum = 0.0f;
    float final_sum = 0.0f;
    int   counter = 0;

    Student* temp = head;
    while (temp != NULL) {
        midterm_sum += temp->midterm;
        final_sum += temp->final;
        counter++;
        temp = temp->next;
    }

    printf("Midterm average : %.2f\n", midterm_sum / counter);
    printf("Final average   : %.2f\n", final_sum   / counter);
}

void top_student() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Student* temp = head->next;
    Student* best = head;
    float    max  = average(head);

    while (temp != NULL) {
        if (average(temp) > max) {
            max  = average(temp);
            best = temp;
        }
        temp = temp->next;
    }

    printf("\n--- Top Student ---\n");
    printf("Name    : %s\n", best->name);
    printf("ID      : %d\n", best->id);
    printf("Midterm : %.2f\n", best->midterm);
    printf("Final   : %.2f\n", best->final);
    printf("Average : %.2f\n", max);
}

void save_records() {
    FILE* fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        printf("Could not open file!\n");
        return;
    }

    Student* temp = head;
    while (temp != NULL) {
        fwrite(temp->name,sizeof(char),50, fp);
        fwrite(&temp->id,sizeof(int),1,fp);
        fwrite(&temp->midterm,sizeof(float), 1,fp);
        fwrite(&temp->final,sizeof(float), 1,fp);
        temp = temp->next;
    }

    fclose(fp);
    printf("Records saved to file.\n");
}

void load_records() {
    FILE* fp = fopen("students.dat", "rb");
    if (fp == NULL)
        return;

    Student* new_std;
    while (1) {
        new_std = (Student*)malloc(sizeof(Student));
        if (new_std == NULL) break;
        new_std->next = NULL;

        if (fread(new_std->name,sizeof(char),50,fp) != 50)  { free(new_std); break; }
        if (fread(&new_std->id,sizeof(int),1,fp) != 1)  { free(new_std); break; }
		if (fread(&new_std->midterm,sizeof(float),1,fp) != 1)  { free(new_std); break; }
        if (fread(&new_std->final,sizeof(float),1,fp) != 1)  { free(new_std); break; }

        if (head == NULL) {
            head = new_std;
        } else {
            Student* temp = head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = new_std;
        }
    }

    fclose(fp);
    printf("Records loaded.\n");
}
