/*to access admin menu --> username & password: admin*/
/*to access teacher menu --> username & password: teacher*/
/*to access student menu --> username & password: student*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
//----------------------------------------------------
#define MAX_STUDENTS 4000
#define MAX_TEACHERS 100
#define MAX_USERS 4200
#define MAX_CLASSES 400
#define MAX_GRADES 400
#define MAX_ATTENDANCE 100
//i used maximal number for an optimal experience
//-----------------------------------------------------
// user record structure
typedef struct User
{
    int id;
    char username[50];
    char password[50];
    char role[10]; // admin, teacher, student
} User;
//-------------------------------------------------------------------
//student record structure
typedef struct Student
{
    int id;
    char name[100];
    char class[10];
    int age;
    char address[200];
} Student;
//-------------------------------------------------------------------
//teacher record structure
typedef struct Teacher
{
    int id;
    char name[100];
    char subject[50];
    int age;
    char address[200];
} Teacher;
//-------------------------------------------------------------------
//class record structure
typedef struct Class
{
    int id;
    char name[50];
    char teacher[100];
    char schedule[100]; //for exemple mon-wed-sat 10:00-11:00
    int enrolled_students[30]; //list of student IDs
} Class;
//-------------------------------------------------------------------
//grade record structure
typedef struct Grade
{
    int student_id;
    int class_id;
    char grade[5]; //for exemple 20, 5, 16.5
} Grade;
//-------------------------------------------------------------------
//attendance record structure
typedef struct Attendance
{
    int student_id;
    int class_id;
    char date[20];   //for exemple 2024-06-13
    char status[10]; //present, absent
} Attendance;
//----------------------------------------------------------------
//arrays to store data
User users[MAX_USERS];
Student students[MAX_STUDENTS];
Teacher teachers[MAX_TEACHERS];
Class classes[MAX_CLASSES];
Grade grades[MAX_GRADES];
Attendance attendance[MAX_ATTENDANCE];
//-------------------------------------------------------------------
//counters for arrays
int user_count = 0;
int student_count = 0;
int teacher_count = 0;
int class_count = 0;
int grade_count = 0;
int attendance_count = 0;
//----------------------------------------------------------------
//function prototypes
char *ReadPassword();
void progress_bar();
void clear_screen();
int login(char *username, char *password);
void admin_menu();
void teacher_menu();
void student_menu();
void add_student();
void view_students();
void view_student_profile(char *name);
void add_teacher();
void view_teachers();
void add_class();
void view_classes();
void enroll_student();
void view_enrollment();
void add_grade();
void view_grades();
void mark_attendance();
void view_attendance();
void generate_report();
int generate_random_id();
void print_line(char ch, int length);
float calculate_final_score(int student_id);
float calculate_attendance_percentage(int student_id);
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
//-------------------------------------------------------------------
char *ReadPassword()
{
    char Key;
    char *Password = malloc(50 * sizeof(char)); //allocate memory for password
    if (Password == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    Password[0] = '\0'; //initialize password as an empty string
    do
    {
        Key = getch(); //read a key without echoing it to the console
        if (Key != '\r' && Key != '\b') //if the key is not Enter or Backspace
        { 
            printf("*");
            strncat(Password, &Key, 1); //concatenate the key to the password
        }
        else if (Key == '\b' && strlen(Password) > 0) //if the key is Backspace and the password is not empty
        {                                          
            Password[strlen(Password) - 1] = '\0'; //remove the last character from the password
            printf("\b \b");                       //erase the character from the console
        }
    } while (Key != '\r'); //repeat until Enter is pressed
    printf("\n");
    return Password;
}
//-------------------------------------------------------------------
void print_line(char ch, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%c", ch);
    }
    printf("\n");
}
//-------------------------------------------------------------------
//generate a random ID
int generate_random_id()
{
    return rand() % 10000 + 1; //generates a random number between 1 and 10000
}
//-------------------------------------------------------------------
//calculate the final score for a student
float calculate_final_score(int student_id)
{
    int total = 0, count = 0;
    for (int i = 0; i < grade_count; i++)
    {
        if (grades[i].student_id == student_id)
        {
            total += atoi(grades[i].grade); //assuming grades are integer values
            count++;
        }
    }
    return count == 0 ? 0 : (float)total / count;
}
//-------------------------------------------------------------------
//calculate attendance percentage for a student
float calculate_attendance_percentage(int student_id)
{
    int present = 0, total = 0;
    for (int i = 0; i < attendance_count; i++)
    {
        if (attendance[i].student_id == student_id)
        {
            total++;
            if (strcmp(attendance[i].status, "present") == 0)
            {
                present++;
            }
        }
    }
    return total == 0 ? 0 : ((float)present / total) * 100;
}
//-------------------------------------------------------------------
//add a new student
void add_student()
{
    Student new_student;
    new_student.id = generate_random_id();
    printf("Enter student name: ");
    scanf(" %[^\n]", new_student.name);
    printf("Enter class: ");
    scanf(" %[^\n]", new_student.class);
    printf("Enter age: ");
    scanf("%d", &new_student.age);
    printf("Enter address: ");
    scanf(" %[^\n]", new_student.address);
    students[student_count++] = new_student;
    printf("Student added successfully with ID: %d\n", new_student.id);
}
//-------------------------------------------------------------------
//view all students
void view_students()
{
    printf("ID    | Name                      | Class | Age | Address\n");
    print_line('-', 60);
    for (int i = 0; i < student_count; i++)
    {
        printf("%-5d | %-25s | %-5s | %-3d | %-30s\n", students[i].id, students[i].name, students[i].class, students[i].age, students[i].address);
    }
}

//view a student's profile by name
void view_student_profile(char *name)
{
    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            printf("ID    : %d\n", students[i].id);
            printf("Name  : %s\n", students[i].name);
            printf("Class : %s\n", students[i].class);
            printf("Age   : %d\n", students[i].age);
            printf("Address: %s\n", students[i].address);
            printf("Attendance Percentage: %.2f%%\n", calculate_attendance_percentage(students[i].id));
            printf("Final Score: %.2f\n", calculate_final_score(students[i].id));
            return;
        }
    }
    printf("Student with name %s not found.\n", name);
}
//-------------------------------------------------------------------
//add a new teacher
void add_teacher()
{
    Teacher new_teacher;
    new_teacher.id = generate_random_id();
    printf("Enter teacher name: ");
    scanf(" %[^\n]", new_teacher.name);
    printf("Enter subject: ");
    scanf(" %[^\n]", new_teacher.subject);
    printf("Enter age: ");
    scanf("%d", &new_teacher.age);
    printf("Enter address: ");
    scanf(" %[^\n]", new_teacher.address);
    teachers[teacher_count++] = new_teacher;
    printf("Teacher added successfully with ID: %d\n", new_teacher.id);
}
//-------------------------------------------------------------------
//view all teachers
void view_teachers()
{
    printf("ID    | Name                      | Subject                  | Age | Address\n");
    print_line('-', 70);
    for (int i = 0; i < teacher_count; i++)
    {
        printf("%-5d | %-25s | %-25s | %-3d | %-30s\n", teachers[i].id, teachers[i].name, teachers[i].subject, teachers[i].age, teachers[i].address);
    }
}
//-------------------------------------------------------------------
//add a new class
void add_class()
{
    Class new_class;
    new_class.id = generate_random_id();
    printf("Enter class name: ");
    scanf(" %[^\n]", new_class.name);
    printf("Enter teacher name: ");
    scanf(" %[^\n]", new_class.teacher);
    printf("Enter schedule: ");
    scanf(" %[^\n]", new_class.schedule);
    for (int i = 0; i < 30; i++) //initialize the list of enrolled students to -1
    {
        new_class.enrolled_students[i] = -1;
    }
    classes[class_count++] = new_class;
    printf("Class added successfully with ID: %d\n", new_class.id);
}
//-------------------------------------------------------------------
//view all classes
void view_classes()
{
    printf("ID    | Name                      | Teacher                  | Schedule\n");
    print_line('-', 70);
    for (int i = 0; i < class_count; i++)
    {
        printf("%-5d | %-25s | %-25s | %-30s\n", classes[i].id, classes[i].name, classes[i].teacher, classes[i].schedule);
    }
}
//-------------------------------------------------------------------
//enroll a student in a class
void enroll_student()
{
    int student_id, class_id;
    printf("Enter student ID: ");
    scanf("%d", &student_id);
    printf("Enter class ID: ");
    scanf("%d", &class_id);
    for (int i = 0; i < class_count; i++) //find the class
    {
        if (classes[i].id == class_id)
        {
            for (int j = 0; j < 30; j++)//find an empty spot in enrolled_students
            {
                if (classes[i].enrolled_students[j] == -1)
                {
                    classes[i].enrolled_students[j] = student_id;
                    printf("Student ID %d enrolled in class ID %d successfully.\n", student_id, class_id);
                    return;
                }
            }
            printf("Class is full. Cannot enroll more students.\n");
            return;
        }
    }
    printf("Class with ID %d not found.\n", class_id);
}
//-------------------------------------------------------------------
//view enrollment for all classes
void view_enrollment()
{
    for (int i = 0; i < class_count; i++)
    {
        printf("Class ID: %d, Class Name: %s\n", classes[i].id, classes[i].name);
        printf("Enrolled Students: ");
        for (int j = 0; j < 30; j++)
        {
            if (classes[i].enrolled_students[j] != -1)
            {
                printf("%d ", classes[i].enrolled_students[j]);
            }
        }
        printf("\n");
    }
}
//-------------------------------------------------------------------
//add a grade for a student in a class
void add_grade()
{
    Grade new_grade;
    printf("Enter student ID: ");
    scanf("%d", &new_grade.student_id);
    printf("Enter class ID: ");
    scanf("%d", &new_grade.class_id);
    printf("Enter grade: ");
    scanf(" %[^\n]", new_grade.grade);
    grades[grade_count++] = new_grade;
    printf("Grade added successfully for student ID: %d in class ID: %d\n", new_grade.student_id, new_grade.class_id);
}
//-------------------------------------------------------------------
//view all grades
void view_grades()
{
    printf("Student ID | Class ID | Grade\n");
    print_line('-', 30);
    for (int i = 0; i < grade_count; i++)
    {
        printf("%-10d | %-8d | %-5s\n", grades[i].student_id, grades[i].class_id, grades[i].grade);
    }
}
//-------------------------------------------------------------------
//mark attendance for a student in a class
void mark_attendance()
{
    Attendance new_attendance;
    printf("Enter student ID: ");
    scanf("%d", &new_attendance.student_id);
    printf("Enter class ID: ");
    scanf("%d", &new_attendance.class_id);
    printf("Enter date (YYYY-MM-DD): ");
    scanf(" %[^\n]", new_attendance.date);
    printf("Enter status (present/absent): ");
    scanf(" %[^\n]", new_attendance.status);
    attendance[attendance_count++] = new_attendance;
    printf("Attendance marked successfully for student ID: %d in class ID: %d\n", new_attendance.student_id, new_attendance.class_id);
}
//-------------------------------------------------------------------
//view attendance for all students
void view_attendance()
{
    printf("Student ID | Class ID | Date       | Status\n");
    print_line('-', 40);
    for (int i = 0; i < attendance_count; i++)
    {
        printf("%-10d | %-8d | %-10s | %-7s\n", attendance[i].student_id, attendance[i].class_id, attendance[i].date, attendance[i].status);
    }
}
//-------------------------------------------------------------------
//generate a report for all students
void generate_report()
{
    for (int i = 0; i < student_count; i++)
    {
        printf("\nStudent ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Class: %s\n", students[i].class);
        printf("Final Score: %.2f\n", calculate_final_score(students[i].id));
        printf("Attendance Percentage: %.2f%%\n", calculate_attendance_percentage(students[i].id));
        print_line('-', 30);
    }
}
//-------------------------------------------------------------------
//admin menu
void admin_menu()
{
    int choice;
    char name[100];
    while (1)
    {
        printf("\nAdmin Menu:\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. View Student Profile\n");
        printf("4. Add Teacher\n");
        printf("5. View Teachers\n");
        printf("6. Add Class\n");
        printf("7. View Classes\n");
        printf("8. Enroll Student\n");
        printf("9. View Enrollment\n");
        printf("10. Add Grade\n");
        printf("11. View Grades\n");
        printf("12. Mark Attendance\n");
        printf("13. View Attendance\n");
        printf("14. Generate Report\n");
        printf("15. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_student();
            break;
        case 2:
            view_students();
            break;
        case 3:
            printf("Enter student name: ");
            scanf(" %[^\n]", name);
            view_student_profile(name);
            break;
        case 4:
            add_teacher();
            break;
        case 5:
            view_teachers();
            break;
        case 6:
            add_class();
            break;
        case 7:
            view_classes();
            break;
        case 8:
            enroll_student();
            break;
        case 9:
            view_enrollment();
            break;
        case 10:
            add_grade();
            break;
        case 11:
            view_grades();
            break;
        case 12:
            mark_attendance();
            break;
        case 13:
            view_attendance();
            break;
        case 14:
            generate_report();
            break;
        case 15:
            return;
        default:
            clear_screen();
            printf("Invalid choice. Please try again.\n");
        }
    }
}
//-------------------------------------------------------------------
//teacher menu
void teacher_menu()
{
    int choice;
    char name[100];
    while (1)
    {
        printf("\nTeacher Menu:\n");
        printf("1. View Students\n");
        printf("2. View Student Profile\n");
        printf("3. Add Grade\n");
        printf("4. View Grades\n");
        printf("5. Mark Attendance\n");
        printf("6. View Attendance\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            view_students();
            break;
        case 2:
            printf("Enter student name: ");
            scanf(" %[^\n]", name);
            view_student_profile(name);
            break;
        case 3:
            add_grade();
            break;
        case 4:
            view_grades();
            break;
        case 5:
            mark_attendance();
            break;
        case 6:
            view_attendance();
            break;
        case 7:
            return;
        default:
            clear_screen();
            printf("Invalid choice. Please try again.\n");
        }
    }
}
//-------------------------------------------------------------------
//student menu
void student_menu()
{
    int choice;
    char name[100];
    while (1)
    {
        printf("\nStudent Menu:\n");
        printf("1. View Grades\n");
        printf("2. View Attendance\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter your name: ");
            scanf(" %[^\n]", name);
            view_student_profile(name);
            break;
        case 2:
            printf("Enter your name: ");
            scanf(" %[^\n]", name);
            view_student_profile(name);
            break;
        case 3:
            return;
        default:
            clear_screen();
            printf("Invalid choice. Please try again.\n");
        }
    }
}
//-------------------------------------------------------------------
//login function
int login(char *username, char *password)
{
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return i;
        }
    }
    return -1;
}
//-------------------------------------------------------------------
//main function
int main()
{
    char username[50], password[50];
    int role;
    srand(time(NULL)); //random ID generation
    //prepopulate some users for testing
    users[user_count++] = (User){1, "admin", "admin", "admin"};
    users[user_count++] = (User){2, "teacher", "teacher", "teacher"};
    users[user_count++] = (User){3, "student", "student", "student"};
    printf("Welcome to the School Management System\n");
    while (1)
    {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        strcpy(password, ReadPassword());
        int user_id = login(username, password);
        if (user_id == -1)
        {
            printf("Invalid login. Please try again.\n");
        }
        else
        {
            if (strcmp(users[user_id].role, "admin") == 0)
            {
                clear_screen();
                admin_menu();
            }
            else if (strcmp(users[user_id].role, "teacher") == 0)
            {
                clear_screen();
                teacher_menu();
            }
            else if (strcmp(users[user_id].role, "student") == 0)
            {
                clear_screen();
                student_menu();
            }
        }
    }
    return 0;
}