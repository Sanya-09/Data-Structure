#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define FILE_NAME "students.txt"

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int attendance;
} Student;

void displayMenu() {
    printf("\nStudent Management System \n");
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Update Student\n");
    printf("4. View All Students\n");
    printf("5. Exit\n");
    printf("\n");
}

void addStudent() {
    Student s;
    FILE *fp = fopen(FILE_NAME, "a");

    if (!fp) {
        perror("Unable to open file");
        return;
    }

    printf("Enter student ID: ");
    scanf("%d", &s.id);
    getchar();
    printf("Enter student name: ");
    fgets(s.name, MAX_NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    printf("Enter attendance percentage: ");
    scanf("%d", &s.attendance);

    fprintf(fp, "%d,%s,%d\n", s.id, s.name, s.attendance);
    fclose(fp);
    printf("Student added successfully!\n");
}

void deleteStudent() {
    int id;
    printf("Enter ID of student to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    Student s;
    char line[150];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%d", &s.id, s.name, &s.attendance);
        if (s.id != id) {
            fprintf(temp, "%d,%s,%d\n", s.id, s.name, s.attendance);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("Student deleted successfully!\n");
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

void updateStudent() {
    int id;
    printf("Enter ID of student to update: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    Student s;
    char line[150];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%d", &s.id, s.name, &s.attendance);
        if (s.id == id) {
            printf("Enter new name: ");
            fgets(s.name, MAX_NAME_LEN, stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("Enter new attendance: ");
            scanf("%d", &s.attendance);
            found = 1;
        }
        fprintf(temp, "%d,%s,%d\n", s.id, s.name, s.attendance);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("Student updated successfully!\n");
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

void viewAllStudents() {
    FILE *fp = fopen(FILE_NAME, "r");
    Student s;
    char line[150];

    if (!fp) {
        perror("Unable to open file");
        return;
    }

    printf("\nID\tName\t\tAttendance\n");
    printf("\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%d", &s.id, s.name, &s.attendance);
        printf("%d\t%-15s%d%%\n", s.id, s.name, s.attendance);
    }

    fclose(fp);
}

int main() {
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: updateStudent(); break;
            case 4: viewAllStudents(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);

    return 0;
}
