#include <stdio.h>
#include <ctype.h>

struct Student {
    int roll;
    char name[1000];
    float cgpa;
};

int isAlpha(char *str) {
    while (*str != '\0') {
        if (!isalpha((unsigned char)*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}


int main() {
    int n;
    printf("Enter the number of students in your class: ");

    int retries =5;
    while(scanf("%d", &n) != 1 || n <= 0){
            printf("Enter right input : ");
            retries--;
    if(retries==0){
        printf("You have given  wrong input for too many time. So exit.\n");
        return 1;
    }
     while (getchar() != '\n');
    }

    struct Student s[n];


    for (int i = 0; i < n; i++) {
        int retries = 5;

        do {
            printf("Enter roll number for student %d: ", i + 1);
            if (scanf("%d", &s[i].roll) != 1 || s[i].roll <= 0) {
                printf("Please enter a valid  roll number of student %d.\n", i + 1);
                retries--;
                if (retries == 0) {
                    printf("Too many invalid attempts. Exiting.\n");
                    return 1;
                }

                while (getchar() != '\n');
            }

        } while (s[i].roll <= 0);

        retries = 5;

        do {
            printf("Enter name for student %d: ", i + 1);
            if (scanf("%99s", s[i].name) != 1 || !isAlpha(s[i].name)) {
                printf("Please enter nick name for student %d.\n", i + 1);
                retries--;
                if (retries == 0) {
                    printf("Too many invalid attempts. Exiting.\n");
                    return 1;
                }

                while (getchar() != '\n');
            }

        } while (!isAlpha(s[i].name));

        retries = 5;
        do {
            printf("Enter CGPA for student %d: ", i + 1);
            if (scanf("%f", &s[i].cgpa) != 1 || s[i].cgpa < 0.0 || s[i].cgpa > 4.0) {
                printf("Please enter a valid CGPA for student %d.\n", i + 1);
                retries--;
                if (retries == 0) {
                    printf("Too many invalid attempts. Exiting.\n");
                    return 1;
                }

                while (getchar() != '\n');
            }

        } while (s[i].cgpa < 0.0 || s[i].cgpa > 4.0);
    }
    printf("\n\n");
    printf("------------------Unsorted student information---------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("\t\tStudent %d:\n", i + 1);
        printf("Roll Number: %d\n", s[i].roll);
        printf("Name: %s\n", s[i].name);
        printf("CGPA: %.2f\n", s[i].cgpa);
    }

    for(int i =0;i<n-1;i++){
        for(int j = 0; j<n-i-1;j++){
            if(s[j].cgpa>s[j+1].cgpa){
                struct Student temp = s[j];
                s[j]=s[j+1];
                s[j+1]= temp;
            }
        }
    }

    printf("\n\n");

    printf("-------------------------After sorting based on CGPA-------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("\t\tStudent %d:\n", i + 1);
        printf("Roll Number: %d\n", s[i].roll);
        printf("Name: %s\n", s[i].name);
        printf("CGPA: %.2f\n", s[i].cgpa);
    }

    FILE *f1 , *f2;
    char ch;
    char line[1000];
    f1=fopen("Bonus.txt","a");
    f2=fopen("Normal.txt","a");
    for(int i =0;i<n;i++){
        if(s[i].cgpa >=3.80){
            fprintf(f1, "Student %d:\n", i + 1);
            fprintf(f1, "Roll Number: %d\n", s[i].roll);
            fprintf(f1, "Name: %s\n", s[i].name);
            fprintf(f1, "CGPA: %.2f\n\n", s[i].cgpa);
        }else{
            fprintf(f2, "Student %d:\n", i + 1);
            fprintf(f2, "Roll Number: %d\n", s[i].roll);
            fprintf(f2, "Name: %s\n", s[i].name);
            fprintf(f2, "CGPA: %.2f\n\n", s[i].cgpa);

        }
    }
     fclose(f1);
     fclose(f2);
    int e;
    printf("Data saved to two files named 'Bonus.txt' and 'Normal.txt'.\n");
    printf("If you want to read file data,\n (a)For read file: Press 1 (b)For Exit: press 2   ");
    scanf("%d", &e);

    while (e == 1) {
        printf("Enter 1 for Bonus file or 2 for Normal file: ");
        int user_choice;
        scanf("%d", &user_choice);

        if (user_choice == 1) {
            f1 = fopen("Bonus.txt", "r");
            while (fgets(line, sizeof(line), f1) != NULL) {
                printf("%s", line);
            }
            fclose(f1);
        } else if (user_choice == 2) {
            f2 = fopen("Normal.txt", "r");
            while (fgets(line, sizeof(line), f2) != NULL) {
                printf("%s", line);
            }
            fclose(f2);
        } else {
            printf("Invalid input. Please enter 1 or 2 to read a file or press any other key to exit.\n");
        }


        printf("Do you want to read another file (1) or exit (2)? ");
        scanf("%d", &e);

        if (e != 1) {
            printf("Exiting.\n");
            break;
        }
    }

    return 0;
}
