// Haoyang (Hendrick) Chen
// chen.haoyang4@northeastern.edu
#include<stdio.h>
int main()
{
    int a,b,c, choice;
    
    printf("Enter your choice\n");
    printf(" 1. Addition\n 2. Subtraction\n 3. Multiplication\n 4. Division\n");
    scanf("%d",&choice);
    
    printf("Enter a and b values");
    scanf("%d %d", &a, &b);
    
    // Add your code here using switch
    switch (choice) {
        case 1: // numbers need no '' or ""
        printf("%d + %d = %d\n", a, b, a + b);
        break;
        case 2:
        printf("%d - %d = %d\n", a, b, a - b);
        break;
        case 3:
        printf("%d * %d = %d\n", a, b, a * b);
        break;
        case 4:
        if (b != 0.0)
            printf("%d / %d = %d\n", a, b, a / b);
        else
            printf("Division by Zero Error! \n");
        break;
    default:
        printf("Choose a valid option! \n");
        break;
    }
           
    return 0;
}
