#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

struct Student *studentHead = NULL;

void insertStudent(int id, const char *name, int age, const char *contactNumber) {
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    if (!newStudent) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newStudent->id = id;
    strncpy(newStudent->name, name, sizeof(newStudent->name) - 1);
    newStudent->name[sizeof(newStudent->name) - 1] = '\0';
    newStudent->age = age;
    strncpy(newStudent->contactNumber, contactNumber, sizeof(newStudent->contactNumber) - 1);
    newStudent->contactNumber[sizeof(newStudent->contactNumber) - 1] = '\0';
    newStudent->next = studentHead;
    studentHead = newStudent;
    printf("Student added successfully!\n");
}

void deleteStudent(int id) {
    struct Student *current = studentHead, *prev = NULL;
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Student with ID %d not found!\n", id);
        return;
    }
    if (prev == NULL) {
        studentHead = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("Student deleted successfully!\n");
}

void updateStudent(int id) {
    struct Student *current = studentHead;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Student with ID %d not found!\n", id);
        return;
    }
    printf("Enter new name: ");
    scanf(" %[^\n]", current->name);
    printf("Enter new age: ");
    scanf("%d", &current->age);
    printf("Enter new contact number: ");
    scanf(" %[^\n]", current->contactNumber);
    printf("Student updated successfully!\n");
}

void displayStudentDetails() {
    if (studentHead == NULL) {
        printf("No students found!\n");
        return;
    }
    printf("------Student Details:------\n");
    struct Student *current = studentHead;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Age: %d, Contact Number: %s\n",
               current->id, current->name, current->age, current->contactNumber);
        current = current->next;
    }
}

void sortStudentsByID() {
    if (studentHead == NULL || studentHead->next == NULL) {
        printf("Not enough students to sort.\n");
        return;
    }
    for (struct Student *i = studentHead; i != NULL; i = i->next) {
        for (struct Student *j = i->next; j != NULL; j = j->next) {
            if (i->id > j->id) {
                struct Student temp = *i;
                *i = *j;
                *j = temp;
                temp.next = i->next;
                i->next = j->next;
                j->next = temp.next;
            }
        }
    }
    printf("Students sorted by ID.\n");
    displayStudentDetails();
}

void sortStudentsByName() {
    if (studentHead == NULL || studentHead->next == NULL) {
        printf("Not enough students to sort.\n");
        return;
    }
    for (struct Student *i = studentHead; i != NULL; i = i->next) {
        for (struct Student *j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->name, j->name) > 0) {
                struct Student temp = *i;
                *i = *j;
                *j = temp;
                temp.next = i->next;
                i->next = j->next;
                j->next = temp.next;
            }
        }
    }
    printf("Students sorted by Name.\n");
    displayStudentDetails();
}

void addStudentToList(struct Student *newStudent) {
    newStudent->next = studentHead;
    studentHead = newStudent;
}

int getTotalStudentCount() {
    int count = 0;
    struct Student *current = studentHead;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
