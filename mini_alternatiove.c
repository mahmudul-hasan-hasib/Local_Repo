#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int roll;
    char name[100];
    float cgpa;
} Student;

void displayStudentInfo(Student student) {
    printf("Name: %s\n", student.name);
    printf("Roll Number: %d\n", student.roll);
    printf("CGPA: %.2f\n\n", student.cgpa);
}

int getInputInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (1) {
        if (scanf("%d", &value) == 1 && value > 0) {
            return value;
        } else {
            printf("Invalid input. Please enter a positive integer: ");
            while (getchar() != '\n');
        }
    }
}

float getInputFloat(const char *prompt, float min, float max) {
    float value;
    printf("%s", prompt);
    while (1) {
        if (scanf("%f", &value) == 1 && value >= min && value <= max) {
            return value;
        } else {
            printf("Invalid input. Please enter a number between %.2f and %.2f: ", min, max);
            while (getchar() != '\n');
        }
    }
}

void sortStudentsByCGPA(Student *students, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].cgpa > students[j + 1].cgpa) {
                // Swap students[j] and students[j+1]
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void writeStudentsToFile(FILE *file, Student *students, int n, float threshold) {
    for (int i = 0; i < n; i++) {
        if (students[i].cgpa >= threshold) {
            fprintf(file, "Student %d Information:\n", i + 1);
            fprintf(file, "Roll Number: %d\n", students[i].roll);
            fprintf(file, "Name: %s\n", students[i].name);
            fprintf(file, "CGPA: %.2f\n\n", students[i].cgpa);
        }
    }
}

void readFileContents(const char *fileName) {
    FILE *fileToRead = fopen(fileName, "r");
    if (fileToRead == NULL) {
        printf("Error opening file: %s\n", fileName);
        return;
    }

    int c;
    while ((c = getc(fileToRead)) != EOF) {
        putchar(c);
    }

    fclose(fileToRead);
}

int main() {
    int n = getInputInt("Enter the number of students: ");

    if (n <= 0 || n > 100) {
        printf("Invalid number of students. Exiting.\n");
        return 1;
    }

    Student *students = (Student *)malloc(n * sizeof(Student));

    if (students == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter information for Student %d:\n", i + 1);

        printf("Enter name: ");
        scanf("%s", students[i].name);
        students[i].roll = getInputInt("Enter roll number: ");

        students[i].cgpa = getInputFloat("Enter CGPA: ", 0.0, 4.0);
    }

    sortStudentsByCGPA(students, n);

    printf("Sorted student information based on CGPA\n");
    for (int i = 0; i < n; i++) {
        printf("Student %d Information:\n", i + 1);
        displayStudentInfo(students[i]);
    }

    FILE *bonusFile = fopen("Bonus.txt", "w");
    FILE *normalFile = fopen("Normal.txt", "w");

    writeStudentsToFile(bonusFile, students, n, 3.80);
    writeStudentsToFile(normalFile, students, n, 0.0);

    fclose(bonusFile);
    fclose(normalFile);

    printf("Data saved to two files named 'Bonus.txt' and 'Normal.txt'.\n");

    int e;
    do {

        printf("(1) For 'Bonus.txt'\n (2) For 'Normal.txt'\n(3) To Exit\n");
        scanf("%d", &e);

        if (e == 1) {
            printf("--------------------Bonus Student file------------------------\n");
            readFileContents("Bonus.txt");
        } else if (e == 2) {
            printf("--------------------Normal Student file------------------------\n");
            readFileContents("Normal.txt");
        } else if (e != 3) {
            printf("Invalid choice. Please enter 1, 2, or 3 to exit.\n");
        }
    } while (e != 3);

    free(students);

    return 0;
}

