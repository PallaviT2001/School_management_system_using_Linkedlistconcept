#include "fees.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>

struct Fees *feesHead = NULL;

void addFeesToList(struct Fees *newFees) {
    if (feesHead == NULL) {
        feesHead = newFees;
    } else {
        struct Fees *current = feesHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newFees;
    }
}


void insertFees(int studentID, int receipt_number, float paid_amount) {
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
    struct Fees *newFees = (struct Fees *)malloc(sizeof(struct Fees));
    if (!newFees) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    newFees->studentDetails = student;
    newFees->receipt_number = receipt_number;
    newFees->paid_amount = paid_amount;
    newFees->next = NULL;

    addFeesToList(newFees);

    printf("Fees record for student ID %d added successfully!\n", studentID);
}

void displayFeesDetails() {
    if (feesHead == NULL) {
        printf("No fees records available.\n");
        return;
    }

    printf("\nFees Details:\n");
    struct Fees *current = feesHead;
    while (current != NULL) {
        printf("Receipt Number: %d, Paid Amount: %.2f\n",
               current->receipt_number, current->paid_amount);

        if (current->studentDetails != NULL) {
            struct Student *student = current->studentDetails;

            printf("Student ID: %d, Name: %s, Age: %d, Contact Number: %s\n",
                   student->id,
                   student->name,
                   student->age,
                   student->contactNumber);
        } else {
            printf("No student details available.\n");
        }

        current = current->next;
    }
}
