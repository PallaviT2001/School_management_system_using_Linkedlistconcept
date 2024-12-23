#include "fileoperation.h"
#include "student.h"
#include "faculty.h"
#include "fees.h"
#include "section.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveAllDataToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for saving all data!");
        return;
    }

    fprintf(file, "STUDENTS\n");
    struct Student *student = studentHead;
    int studentCount = getTotalStudentCount();
    fprintf(file, "%d\n", studentCount);

    while (student != NULL) {
        fprintf(file, "%d %s %d %s\n", student->id, student->name, student->age, student->contactNumber);
        student = student->next;
    }

    fprintf(file, "FACULTIES\n");
    struct Faculty *faculty = facultyHead;
    int facultyCount = 0;
    while (faculty != NULL) {
        facultyCount++;
        faculty = faculty->next;
    }
    fprintf(file, "%d\n", facultyCount);

    faculty = facultyHead;
    while (faculty != NULL) {
        fprintf(file, "%d %s %s %d %s\n", faculty->id, faculty->name, faculty->department, faculty->age, faculty->qualification);
        faculty = faculty->next;
    }

    fprintf(file, "FEES\n");
    struct Fees *fees = feesHead;
    int feesCount = 0;
    while (fees != NULL) {
        feesCount++;
        fees = fees->next;
    }
    fprintf(file, "%d\n", feesCount);

    fees = feesHead;
    while (fees != NULL) {
        fprintf(file, "%d %f %d %s %d %s\n", fees->receipt_number, fees->paid_amount,
                fees->studentDetails->id, fees->studentDetails->name,
                fees->studentDetails->age, fees->studentDetails->contactNumber);
        fees = fees->next;
    }

    fprintf(file, "SECTIONS\n");
    struct Section *section = sectionHead;
    int sectionCount = 0;
    while (section != NULL) {
        sectionCount++;
        section = section->next;
    }
    fprintf(file, "%d\n", sectionCount);

    section = sectionHead;
    while (section != NULL) {
        fprintf(file, "%d %s %d %s %d %s\n", section->section_id, section->section_name,
                section->studentDetails->id, section->studentDetails->name,
                section->studentDetails->age, section->studentDetails->contactNumber);
        section = section->next;
    }

    fclose(file);
    printf("All data saved successfully to %s.\n", filename);
}

void loadAllDataFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    //return;
    if (file == NULL) {
        perror("No data found.");
        return;
    }

    char sectionHeader[20];
    int count;

    fscanf(file, "%s", sectionHeader);
    if (strcmp(sectionHeader, "STUDENTS") == 0) {
        fscanf(file, "%d", &count);
        for (int i = 0; i < count; i++) {
            struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
            if (newStudent == NULL) {
                perror("Memory allocation failed for a student!");
                fclose(file);
                exit(1);
            }
            fscanf(file, "%d %s %d %s", &newStudent->id, newStudent->name, &newStudent->age, newStudent->contactNumber);
            newStudent->next = NULL;
            addStudentToList(newStudent);
        }
    }

    fscanf(file, "%s", sectionHeader);
    if (strcmp(sectionHeader, "FACULTIES") == 0) {
        fscanf(file, "%d", &count);
        for (int i = 0; i < count; i++) {
            struct Faculty *newFaculty = (struct Faculty *)malloc(sizeof(struct Faculty));
            if (newFaculty == NULL) {
                perror("Memory allocation failed for a faculty!");
                fclose(file);
                exit(1);
            }
            fscanf(file, "%d %s %s %d %s", &newFaculty->id, newFaculty->name, newFaculty->department, &newFaculty->age, newFaculty->qualification);
            newFaculty->next = NULL;
            addFacultyToList(newFaculty);
        }
    }

    fscanf(file, "%s", sectionHeader);
    if (strcmp(sectionHeader, "FEES") == 0) {
        fscanf(file, "%d", &count);
        for (int i = 0; i < count; i++) {
            struct Fees *newFees = (struct Fees *)malloc(sizeof(struct Fees));
            newFees->studentDetails = (struct Student *)malloc(sizeof(struct Student));
            if (newFees == NULL || newFees->studentDetails == NULL) {
                perror("Memory allocation failed for a fees record!");
                fclose(file);
                exit(1);
            }
            fscanf(file, "%d %f %d %s %d %s", &newFees->receipt_number, &newFees->paid_amount,
                   &newFees->studentDetails->id, newFees->studentDetails->name,
                   &newFees->studentDetails->age, newFees->studentDetails->contactNumber);
            newFees->next = NULL;
            addFeesToList(newFees);
        }
    }

    fscanf(file, "%s", sectionHeader);
    if (strcmp(sectionHeader, "SECTIONS") == 0) {
        fscanf(file, "%d", &count);
        for (int i = 0; i < count; i++) {
            struct Section *newSection = (struct Section *)malloc(sizeof(struct Section));
            newSection->studentDetails = (struct Student *)malloc(sizeof(struct Student));
            if (newSection == NULL || newSection->studentDetails == NULL) {
                perror("Memory allocation failed for a section!");
                fclose(file);
                exit(1);
            }
            fscanf(file, "%d %s %d %s %d %s", &newSection->section_id, newSection->section_name,
                   &newSection->studentDetails->id, newSection->studentDetails->name,
                   &newSection->studentDetails->age, newSection->studentDetails->contactNumber);
            newSection->next = NULL;
            addSectionToList(newSection);
        }
    }

    fclose(file);
    printf("All data loaded successfully from %s.\n", filename);
}
