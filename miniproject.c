#include<stdio.h >
#include<stdlib.h >
#include<string.h>

FILE *ptr = NULL, *temp = NULL;
int countRecord = 0;
struct stuInfo
{
    int idNumber;
    char name[30];
    int class;
    int age;
    char gender[10];
    char admissionDate[12];
}student;
void addStudentRecord()
{
    printf("\nWELCOME TO S.G.M PUBLIC SCHOOL\n\n");
    student.idNumber=100;
    ptr = fopen("schoolRecord.txt", "rb");
    while (fread(&student, sizeof(student), 1, ptr)>0)
    { 
        student.idNumber+=1;       
        countRecord++;
    }               
    fclose(ptr);
    printf("Enter Student Name : ");
    fflush(stdin);
    gets(student.name);
    printf("Enter Student Class:");
    scanf("%d", &student.class);
    printf("Enter Student Age:");
    scanf("%d", &student.age);
    printf("Enter Student Gender:");
    fflush(stdin);
    gets(student.gender);
    printf("Enter Admission Date:");
    fflush(stdin);
    gets(student.admissionDate);
    ptr = fopen("schoolRecord.txt", "ab");
    if (ptr == NULL)
    {
        printf("File is not open\n");
        exit(0);
    }
    fwrite(&student, sizeof(student), 1, ptr);
    countRecord++;
    printf("\nStudent record is successfully added\n");
    fclose(ptr);
}
void searchStudentRecord()
{
    int studentID, check = 0;
    if (countRecord==0)
    {
        printf("\nSchool Record is empty");
        goto goToEnd;
    }
    printf("\nWELCOME TO S.G.M PUBLIC SCHOOL\n\n");
    printf("Enter student ID No. : ");
    scanf("%d", &studentID);
    ptr = fopen("schoolRecord.txt", "rb");
    if (ptr == NULL)
    {
        printf("File is not open.\n");
        exit(0);
    }
    while (fread(&student, sizeof(student), 1, ptr) > 0 && check == 0)
    {
        if (studentID == student.idNumber)
        {
            printf("\nStudent ID No       : %d\n", student.idNumber);
            printf("Student Name          : %s\n", student.name);
            printf("Student Class         : %d\n", student.class);
            printf("Student Age           : %d\n", student.age);
            printf("Student Gender        : %s\n", student.gender);
            printf("Student Admission Date: %s\n\n", student.admissionDate);
            check = 1;
        }
    }
    if (check == 0)
    {
        printf("\nSorry! Record is not found\n");
    }
    fclose(ptr);
    goToEnd:
    printf("");
}
void deleteStudentRecord()
{
    int stuID, check = 0;
    if (countRecord==0)
    {
        printf("\nSchool Record is empty");
        goto goToEnd;
    }
    printf("Enter student ID number :");
    scanf("%d", &stuID);
    ptr = fopen("schoolRecord.txt", "rb");
    temp = fopen("tempfile.txt", "wb");
    if (ptr == NULL || temp == NULL)
    {
        printf("File is not open.\n");
        exit(0);
    }
    while (fread(&student, sizeof(student), 1, ptr) > 0)
    {
        if (student.idNumber != stuID)
        {
            fwrite(&student, sizeof(student), 1, temp);
            check = 1;
        }
        else
        {
            if (countRecord == 1)
            {
                check = 2;
            }
        }
    }
    fclose(ptr);
    fclose(temp);
    if (check == 1)
    {
        remove("SchoolRecord.txt");
        rename("tempfile.txt", "schoolRecord.txt");
        countRecord--;
        printf("\nThe Student record is successfully deleted\n");
    }
    else if (check == 2)
    {
        remove("schoolRecord.txt");
        rename("tempfile.txt", "schoolRecord.txt");
        countRecord--;
        printf("\nThe Student record is successfully deleted\n");
    }
    else
    {
        printf("\nSorry! Record is not found\n");
    }
goToEnd:
printf("");
}
void updateStudentRecord()
{
    int stuID, choose, check = 0;
    char name[30];
    int class;
    int age;
    char gender[10];
    if (countRecord == 0)
    {        
        printf("\nSchool Record is empty");
        goto goToEnd;
    }
    printf("Enter student ID :");
    scanf("%d", &stuID);
    printf("\nYou can not change your ID number\n");
    printf("What do you want to update\n");
    printf("press 1 for Student Name\n");
    printf("press 2 for Student Class\n");
    printf("press 3 for Student Age\n");
again:
    printf("Choose any menu :");
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        printf("Enter new Name :");
        fflush(stdin);
        gets(name);
        ptr = fopen("schoolRecord.txt", "rb");
        temp = fopen("tempRecord.txt", "wb");
        if (ptr == NULL || temp == NULL)
        {
            printf("File is not open\n");
            exit(0);
        }
        while (fread(&student, sizeof(student), 1, ptr) > 0)
        {
            if (student.idNumber == stuID)
            {
                strcpy(student.name, name);
                fwrite(&student, sizeof(student), 1, temp);
                check = 1;
            }
            else
            {
                fwrite(&student, sizeof(student), 1, temp);
            }
        }
        fclose(ptr);
        fclose(temp);
        if (check == 1)
        {
            remove("schoolRecord.txt");
            rename("tempRecord.txt", "schoolRecord.txt");
            printf("\nThe student record is successfully updated\n");
        }
        else
        {
            printf("\nStudent record is not found\n");
        }
        break;
    case 2:
        printf("Enter new Class :");
        scanf("%d", &class);
        ptr = fopen("schoolRecord.txt", "rb");
        temp = fopen("tempRecord.txt", "wb");
        if (ptr == NULL || temp == NULL)
        {
            printf("File is not open\n");
            exit(0);
        }
        while (fread(&student, sizeof(student), 1, ptr) > 0)
        {
            if (student.idNumber == stuID)
            {
                student.class = class;
                fwrite(&student, sizeof(student), 1, temp);
                check = 1;
            }
            else
            {
                fwrite(&student, sizeof(student), 1, temp);
            }
        }
        fclose(ptr);
        fclose(temp);
        if (check == 1)
        {
            remove("schoolRecord.txt");
            rename("tempRecord.txt", "schoolRecord.txt");
            printf("\nThe student record is successfully updated\n");
        }
        else
        {
            printf("\nStudent record is not found\n");
        }
        break;
    case 3:
        printf("Enter new Age :");
        scanf("%d", &age);
        ptr = fopen("schoolRecord.txt", "rb");
        temp = fopen("tempRecord.txt", "wb");
        if (ptr == NULL || temp == NULL)
        {
            printf("File is not open\n");
            exit(0);
        }
        while (fread(&student, sizeof(student), 1, ptr) > 0)
        {
            if (student.idNumber == stuID)
            {
                student.age = age;
                fwrite(&student, sizeof(student), 1, temp);
                check = 1;
            }
            else
            {
                fwrite(&student, sizeof(student), 1, temp);
            }
        }
        fclose(ptr);
        fclose(temp);
        if (check == 1)
        {
            remove("schoolRecord.txt");
            rename("tempRecord.txt", "schoolRecord.txt");
            printf("\nThe student record is successfully updated\n");
        }
        else
        {
            printf("\nStudent record is not found\n");
        }
        break;
    default:
        printf("Invalid press try again\n");
        goto again;
    }
goToEnd:
printf("");
}
void showAllStudentRecord()
{
    char check;
    int class;
    if (countRecord == 0)
    {
        printf("\nSchool Record is empty");
        goto goToEnd;
    }
    ptr = fopen("schoolRecord.txt", "rb");
    if (ptr == NULL)
    {
        printf("File is not open\n");
        exit(0);
    }
again:
    printf("If you want show all classes student record then press 'Y'\n");
    printf("If you want to show a specific class student record then press 'N'\n");
    fflush(stdin);
    scanf("%c", &check);
    if (check == 'Y' || check == 'y')
    {
        while (fread(&student, sizeof(student), 1, ptr) > 0)
        {
        	printf("------------------------------------------------------------------------------------");
            printf("\n%d\t\t %s\t\t %d\t\t ", student.idNumber, student.name, student.class);
            printf("%d\t\t %s\t\t %s\n", student.age, student.gender, student.admissionDate);
        }
    }
    else if (check == 'N' || check == 'n')
    {
    again1:
        printf("Enter class :");
        scanf("%d", &class);
        if (class >= 1 && class <= 12)
        {
            while (fread(&student, sizeof(student), 1, ptr) > 0)
            {
                if (student.class == class)
                {
                	printf("-------------------------------------------------------------");
                    printf("\n%d\t\t %s\t\t %d\t\t ", student.idNumber, student.name, student.class);
                    printf("%d\t\t %s\t\t %s\n", student.age, student.gender, student.admissionDate);
                }
            }
        }
        else
        {
            printf("Invalid class try again\n");
            goto again1;
        }
    }
    else
    {
        printf("Invalid press try again\n");
        goto again;
    }
    fclose(ptr);
goToEnd:
printf("");
}
void main()
{
    int choose;
    while (1)
    {
    again:
        printf("\nPress 1 for Add student record\n");
        printf("Press 2 for Search student record\n");
        printf("Press 3 for Delete student record\n");
        printf("Press 4 for Update student record\n");
        printf("Press 5 for Show all student record\n");
        printf("Press 6 for Exitt\n");
        printf("Please choose any menu:");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            addStudentRecord();
            break;
        case 2:
            searchStudentRecord();
            break;
        case 3:
            deleteStudentRecord();
            break;
        case 4:
            updateStudentRecord();
            break;
        case 5:
            showAllStudentRecord();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid Press try again\n");
            goto again;
        }
    }
}