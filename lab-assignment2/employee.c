/*C Program to read and print the n employee details using structure and dynamic memory allocation*/
#include <stdio.h>
#include <stdlib.h>
/*structure to hold the details of an employee*/
typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;
/* Read the employee details using scanf*/
void readData(int n, employee_t* s)
{
    // Add your code here
    for (int i = 0; i < n; i++) {
        printf("Enter details for employee %d\n", i + 1);
        printf("Employee ID: ");
        scanf("%d", &s[i].empId);
        printf("Name: ");
        scanf("%s", s[i].Name);
        printf("Designation: ");
        scanf("%s", s[i].Designation);
        printf("Department: ");
        scanf("%s", s[i].Dept);
    }
}
/* Function to print the employee details*/
void display(int n, employee_t * s)
{
    // Add your code here
    for (int i = 0; i < n; i++) {
        printf("\nDetails of employee %d\n", i + 1);
        printf("Employee ID: %d\n", s[i].empId);
        printf("Name: %s\n", s[i].Name);
        printf("Designation: %s\n", s[i].Designation);
        printf("Department: %s\n", s[i].Dept);
    }
}

/*----------Main Program--------*/
int main()

{
    // Main Function to print the employee details
    // Add your code here
    int n;
    employee_t* empteam1;

    // Define the number of employees
    printf("Enter the number of employees: ");
    scanf("%d", &n);
    
    // Allocating memory with size of one employee multiply the 
    // number of employees
    empteam1 = (employee_t*)malloc(n * sizeof(employee_t));

    if (empteam1 == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit the program if memory allocation fails
    }
    
    readData(n, empteam1);

    
    display(n, empteam1);
    
    free(empteam1);

    return 0;
}

