#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "section.h"
#include "student.h"

struct Section *sectionHead = NULL;

void insertSection(int studentID, int section_id, const char *section_name) {
    struct Student *student = NULL;

    for (struct Student *current = studentHead; current != NULL; current = current->next) {
        if (current->id == studentID) {
            student = current;
            break;
        }
    }
    if (student == NULL) {
        printf("Student with ID %d not found!\n", studentID);
        return;
    }
    struct Section *newSection = (struct Section *)malloc(sizeof(struct Section));
    if (!newSection) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newSection->studentDetails = student;
    newSection->section_id = section_id;
    strncpy(newSection->section_name, section_name, sizeof(newSection->section_name) - 1);
    newSection->section_name[sizeof(newSection->section_name) - 1] = '\0';
    newSection->next = sectionHead;
    sectionHead = newSection;

    printf("Section record for student ID %d added successfully!\n", studentID);
}

void displaySectionDetails() {
    if (sectionHead == NULL) {
        printf("No section records available.\n");
        return;
    }

    printf("\nSection Details:\n");
    struct Section *current = sectionHead;
    while (current != NULL) {
        printf("Section ID: %d, Section Name: %s\n", current->section_id, current->section_name);
        printf("Student ID: %d, Name: %s, Age: %d, Contact Number: %s\n",
               current->studentDetails->id,
               current->studentDetails->name,
               current->studentDetails->age,
               current->studentDetails->contactNumber);
        current = current->next;
    }
}

void addSectionToList(struct Section *newSection) {
    if (sectionHead == NULL) {
        sectionHead = newSection;
    } else {
        struct Section *current = sectionHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newSection;
    }
}
