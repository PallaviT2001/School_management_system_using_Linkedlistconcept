#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "faculty.h"

struct Faculty *facultyHead = NULL;

void insertFaculty(int id, const char *name, const char *department, int age, const char *qualification) {
    struct Faculty *newFaculty = (struct Faculty *)malloc(sizeof(struct Faculty));
    if (!newFaculty) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newFaculty->id = id;
    strncpy(newFaculty->name, name, sizeof(newFaculty->name) - 1);
    newFaculty->name[sizeof(newFaculty->name) - 1] = '\0';
    strncpy(newFaculty->department, department, sizeof(newFaculty->department) - 1);
    newFaculty->department[sizeof(newFaculty->department) - 1] = '\0';
    newFaculty->age = age;
    strncpy(newFaculty->qualification, qualification, sizeof(newFaculty->qualification) - 1);
    newFaculty->qualification[sizeof(newFaculty->qualification) - 1] = '\0';
    newFaculty->next = facultyHead; // Insert at the beginning
    facultyHead = newFaculty;
    printf("Faculty added successfully!\n");
}

void deleteFaculty(int id) {
    struct Faculty *current = facultyHead, *prev = NULL;
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Faculty with ID %d not found!\n", id);
        return;
    }
    if (prev == NULL) {
        facultyHead= current->next; // Deleting the head node
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("Faculty deleted successfully!\n");
}

void updateFaculty(int id) {
    struct Faculty *current = facultyHead;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Faculty with ID %d not found!\n", id);
        return;
    }
    printf("Enter new name: ");
    scanf(" %[^\n]", current->name);
    printf("Enter new department: ");
    scanf(" %[^\n]", current->department);
    printf("Enter new age: ");
    scanf("%d", &current->age);
    printf("Enter new qualification: ");
    scanf(" %[^\n]", current->qualification);
    printf("Faculty updated successfully!\n");
}

void displayFacultyDetails() {
    if (facultyHead == NULL) {
        printf("No faculties available.\n");
        return;
    }
    printf("\nFaculty Details:\n");
    struct Faculty *current = facultyHead;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Department: %s, Age: %d, Qualification: %s\n",
               current->id, current->name, current->department, current->age, current->qualification);
        current = current->next;
    }
}

void sortFacultiesByID() {
    if (facultyHead== NULL || facultyHead->next == NULL) {
        printf("Not enough faculties to sort.\n");
        return;
    }
    for (struct Faculty *i = facultyHead; i != NULL; i = i->next) {
        for (struct Faculty *j = i->next; j != NULL; j = j->next) {
            if (i->id > j->id) {
                struct Faculty temp = *i;
                *i = *j;
                *j = temp;
                temp.next = i->next;
                i->next = j->next;
                j->next = temp.next;
            }
        }
    }
    printf("Faculties sorted by ID.\n");
    displayFacultyDetails();
}

void sortFacultiesByName() {
    if (facultyHead== NULL || facultyHead->next == NULL) {
        printf("Not enough faculties to sort.\n");
        return;
    }
    for (struct Faculty *i = facultyHead; i != NULL; i = i->next) {
        for (struct Faculty *j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->name, j->name) > 0) {
                struct Faculty temp = *i;
                *i = *j;
                *j = temp;
                temp.next = i->next;
                i->next = j->next;
                j->next = temp.next;
            }
        }
    }
    printf("Faculties sorted by Name.\n");
    displayFacultyDetails();
}

int getTotalFacultyCount() {
    struct Faculty *current = facultyHead;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void addFacultyToList(struct Faculty *newFaculty) {
    if (facultyHead == NULL) {
        facultyHead = newFaculty;
    } else {
        struct Faculty *current = facultyHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newFaculty;
    }
}

