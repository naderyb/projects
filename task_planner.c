#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
//----------------------------------------------------------------
#define MAX_TASKS 100
#define MAX_NAME_LENGTH 100
//----------------------------------------------------------------
typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_NAME_LENGTH];
    struct tm due_date;
    int is_completed;
} Task;
//----------------------------------------------------------------
Task tasks[MAX_TASKS];
int task_count = 0;
//----------------------------------------------------------------
void set_console_color(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
//----------------------------------------------------------------
void clear_screen()
{
    system("cls");
}
//----------------------------------------------------------------
void progress_bar()
{
    printf("[");
    for (int i = 0; i < 40; i++)
    {
        printf("#");    //character can be changed
        fflush(stdout); //immediately display the character
        Sleep(100);     //sleep for 100 milliseconds (0.1 seconds)
    }
    printf("]\nDone\n");
}
//----------------------------------------------------------------
void display_tasks()
{
    clear_screen();
    printf("Task Planner\n");
    printf("============\n");
    printf("%-5s %-20s %-15s %-10s\n", "No.", "Name", "Due Date", "Status");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < task_count; i++)
    {
        Task t = tasks[i];
        char due_date[11];
        strftime(due_date, 11, "%Y-%m-%d", &t.due_date);
        if (t.is_completed)
        {
            set_console_color(FOREGROUND_GREEN);
            printf("%-5d %-20s %-15s %-10s\n", i + 1, t.name, due_date, "Completed");
        }
        else
        {
            set_console_color(FOREGROUND_RED);
            printf("%-5d %-20s %-15s %-10s\n", i + 1, t.name, due_date, "Pending");
        }
    }
    set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //reset to default color
    printf("\npress any key to continue...");
    _getch(); //wait for a key press
}
//----------------------------------------------------------------
int validate_date(int year, int month, int day); 

void add_task()
{
    if (task_count >= MAX_TASKS)
    {
        printf("Task limit reached.\n");
        return;
    }
    Task new_task;
    printf("Enter task name: ");
    scanf(" %[^\n]", new_task.name);
    printf("Enter task description: ");
    scanf(" %[^\n]", new_task.description);
    int year, month, day;
    do
    {
        printf("Enter due date (YYYY/MM/DD): ");
        scanf("%d/%d/%d", &year, &month, &day);
    } while (!validate_date(year, month, day));
    new_task.due_date.tm_year = year - 1900;
    new_task.due_date.tm_mon = month - 1;
    new_task.due_date.tm_mday = day;
    new_task.due_date.tm_hour = 0;
    new_task.due_date.tm_min = 0;
    new_task.due_date.tm_sec = 0;
    new_task.due_date.tm_isdst = -1;
    mktime(&new_task.due_date);
    new_task.is_completed = 0;
    tasks[task_count++] = new_task;
    progress_bar();
    printf("Task added successfully.\n");
    printf("press any key to continue ...");
    _getch(); //wait for a key press
}
//----------------------------------------------------------------
int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
//----------------------------------------------------------------
int validate_date(int year, int month, int day)
{
    if (month < 1 || month > 12 || day < 1)
        return 0;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap_year(year))
        days_in_month[1] = 29;
    return day <= days_in_month[month - 1];
}
//----------------------------------------------------------------
void display_task_table()
{
    clear_screen();
    printf("Task List\n");
    printf("=========\n");
    printf("%-5s %-20s %-15s %-10s\n", "No.", "Name", "Due Date", "Status");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < task_count; i++)
    {
        Task t = tasks[i];
        char due_date[11];
        strftime(due_date, 11, "%Y-%m-%d", &t.due_date);
        if (t.is_completed)
        {
            set_console_color(FOREGROUND_GREEN);
            printf("%-5d %-20s %-15s %-10s\n", i + 1, t.name, due_date, "Completed");
        }
        else
        {
            set_console_color(FOREGROUND_RED);
            printf("%-5d %-20s %-15s %-10s\n", i + 1, t.name, due_date, "Pending");
        }
    }
    set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //reset to default color
}
//----------------------------------------------------------------
void delete_task()
{
    display_task_table();
    int task_num;
    printf("\nEnter task number to delete: ");
    scanf("%d", &task_num);
    if (task_num < 1 || task_num > task_count)
    {
        printf("Invalid task number.\n");
        printf("press any key to continue...");
        _getch(); //wait for a key press
        return;
    }
    for (int i = task_num - 1; i < task_count - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }
    task_count--;
    progress_bar();
    printf("Task deleted successfully.\n");
    printf("press any key to continue...");
    _getch(); //wait for a key press
}
//----------------------------------------------------------------
void mark_task_complete()
{
    display_task_table();
    int task_num;
    printf("\nEnter task number to mark as completed: ");
    scanf("%d", &task_num);
    if (task_num < 1 || task_num > task_count)
    {
        progress_bar();
        printf("Invalid task number.\n");
        printf("press any key to continue...");
        _getch(); //wait for a key press
        return;
    }
    tasks[task_num - 1].is_completed = 1;
    progress_bar();
    printf("Task marked as completed.\n");
    printf("press any key to continue...");
    _getch(); //wait for a key press
}
//----------------------------------------------------------------
void save_tasks_to_file()
{
    FILE *file = fopen("tasks.txt", "w");
    if (!file)
    {
        progress_bar();
        printf("Error opening file for writing.\n");
        printf("press any key to continue...");
        _getch(); //wait for a key press
        return;
    }
    for (int i = 0; i < task_count; i++)
    {
        Task t = tasks[i];
        fprintf(file, "%s;%s;%ld;%d\n", t.name, t.description, mktime(&t.due_date), t.is_completed);
    }
    fclose(file);
    progress_bar();
    printf("Tasks saved to file successfully.\n");
    printf("press any key to continue...");
    _getch(); //wait for a key press
}
//----------------------------------------------------------------
void load_tasks_from_file()
{
    FILE *file = fopen("tasks.txt", "r");
    if (!file)
    {
        progress_bar();
        printf("Error opening file for reading.\n");
        printf("press any key to continue...");
        _getch(); //wait for a key press
        return;
    }
    task_count = 0;
    while (fscanf(file, "%[^;];%[^;];%ld;%d\n", tasks[task_count].name, tasks[task_count].description, &tasks[task_count].due_date, &tasks[task_count].is_completed) == 4)
    {
        tasks[task_count].due_date.tm_isdst = -1; //set isdst to -1 for mktime to calculate correctly
        mktime(&tasks[task_count].due_date);      //recalculate the time structure
        task_count++;
    }
    fclose(file);
    progress_bar();
    printf("Tasks loaded from file successfully.\n");
    printf("press any key to continue...");
    _getch(); //wait for a key press
}
//----------------------------------------------------------------
void display_menu(int highlight)
{
    char *choices[] = {
        "1. Add task",
        "2. List tasks",
        "3. Delete task",
        "4. Mark task as completed",
        "5. Save tasks to file",
        "6. Load tasks from file",
        "7. Exit"};
    int n_choices = sizeof(choices) / sizeof(char *);
    clear_screen();
    for (int i = 0; i < n_choices; ++i)
    {
        if (highlight == i + 1)
        {
            set_console_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("--> %s\n", choices[i]);
            set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else
        {
            printf("    %s\n", choices[i]);
        }
    }
}
//----------------------------------------------------------------
int main()
{
    int choice = 0;
    int highlight = 1;
    int c;
    load_tasks_from_file();
    while (1)
    {
        display_menu(highlight);
        c = _getch();
        switch (c)
        {
        case 72: //up arrow key
            if (highlight == 1)
                highlight = 7;
            else
                --highlight;
            break;
        case 80: //down arrow key
            if (highlight == 7)
                highlight = 1;
            else
                ++highlight;
            break;
        case 13: //enter key
            choice = highlight;
            break;
        default:
            break;
        }
        if (choice)
        {
            switch (choice)
            {
            case 1:
                clear_screen();
                add_task();
                break;
            case 2:
                display_tasks();
                break;
            case 3:
                clear_screen();
                delete_task();
                break;
            case 4:
                clear_screen();
                mark_task_complete();
                break;
            case 5:
                clear_screen();
                save_tasks_to_file();
                break;
            case 6:
                clear_screen();
                load_tasks_from_file();
                break;
            case 7:
                clear_screen();
                save_tasks_to_file();
                printf("\nGoodbye!\n");
                exit(0);
            default:
                break;
            }
            choice = 0;
        }
    }
    return 0;
}