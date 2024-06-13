#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
//------------------------------------------------------------------------------
#define MAX_NAME 100
#define MAX_STUDENTS 100
//------------------------------------------------------------------------------
typedef struct
{
    char name[MAX_NAME];
    float score;
} Student;
//------------------------------------------------------------------------------
int compare(const void *a, const void *b)
{
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    if (studentB->score > studentA->score)
        return 1;
    if (studentB->score < studentA->score)
        return -1;
    return 0;
}
//------------------------------------------------------------------------------
//procedure to capitalize the first letter of a name
void capitalizeName(char *name)
{
    if (name[0] != '\0')
    {
        name[0] = toupper(name[0]);
    }
}
//------------------------------------------------------------------------------
int main()
{
    Student students[MAX_STUDENTS];
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        printf("Enter name of student %d: ", i + 1);
        fgets(students[i].name, MAX_NAME, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0;
        capitalizeName(students[i].name); //capitalize the first letter
        printf("Enter score of student %d: ", i + 1);
        scanf("%f", &students[i].score);
        getchar();
    }
    qsort(students, n, sizeof(Student), compare);
    system("cls");
    printf("\nRanked list of students:\n");
    printf("+-------+----------------------------------+--------+----------+\n");
    printf("| Rank  | Name                             | Score  | Status   |\n");
    printf("+-------+----------------------------------+--------+----------+\n");
    for (int i = 0; i < n; i++)
    {
        char colorName[10] = "";
        char colorScore[10] = "";
        char colorStatus[10] = "";
        char reset[] = "\033[0m";
        if (students[i].score < 10)
        {
            strcpy(colorScore, "\033[31m");  //red for score < 10
            strcpy(colorStatus, "\033[31m"); //red for "Failed"
        }
        else
        {
            strcpy(colorScore, "\033[32m");  //green for score >= 10
            strcpy(colorStatus, "\033[32m"); //green for "Passed"
        }
        printf("| %-5d | %s%-32s%s | %s%-6.2f%s | %s%-8s%s |\n", i + 1, colorName, students[i].name, reset, colorScore, students[i].score, reset, colorStatus, (students[i].score >= 10) ? "Passed" : "Failed", reset);
    }
    printf("+-------+----------------------------------+--------+----------+\n");
    return 0;
}
