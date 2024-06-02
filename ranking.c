#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME];
    float score;
} Student;

//function to compare two students based on their scores
int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    if (studentB->score > studentA->score) return 1;
    if (studentB->score < studentA->score) return -1;
    return 0;
}

int main() {
    Student students[MAX_STUDENTS];
    int n;

    printf("Enter the number of students: ");
    scanf("%d", &n);
    getchar(); 

    for (int i = 0; i < n; i++) {
        printf("Enter name of student %d: ", i + 1);
        fgets(students[i].name, MAX_NAME, stdin);
        // Remove newline character from the string
        students[i].name[strcspn(students[i].name, "\n")] = 0;

        printf("Enter score of student %d: ", i + 1);
        scanf("%f", &students[i].score);
        getchar(); 
    }

    //sort students based on their scores
    qsort(students, n, sizeof(Student), compare);

    // Print the ranked list in a table format
    printf("\nRanked list of students:\n");
    printf("+-------+----------------------------------+--------+\n");
    printf("| Rank  | Name                             | Score  |\n");
    printf("+-------+----------------------------------+--------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-5d | %-32s | %-6.2f |\n", i + 1, students[i].name, students[i].score);
    }
    printf("+-------+----------------------------------+--------+\n");

    return 0;
}
