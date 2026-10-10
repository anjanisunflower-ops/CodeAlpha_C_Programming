 //Basic – Calculator Programme//
#include <stdio.h>

int main(void)
 {
    char op;
    double a, b;
    char again;

    do {
        printf("\n===== BASIC CALCULATOR =====\n");
        printf("Enter first number: ");
        if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); return 1; 
		}
        printf("Enter operator (+, -, *, /): ");
        scanf(" %c", &op);
        printf("Enter second number: ");
        if (scanf("%lf", &b) != 1) { printf("Invalid input.\n"); return 1; 
		}

        switch (op)
		 {
            case '+':
                printf("Result: %.2f + %.2f = %.2f\n", a, b, a + b);
                break;
            case '-':
                printf("Result: %.2f - %.2f = %.2f\n", a, b, a - b);
                break;
            case '*':
                printf("Result: %.2f * %.2f = %.2f\n", a, b, a * b);
                break;
            case '/':
                if (b == 0)
                    printf("Error: division by zero is not allowed.\n");
                else
                    printf("Result: %.2f / %.2f = %.2f\n", a, b, a / b);
                break;
            default:
                printf("Invalid operator!\n");
        }

        printf("Calculate again? (y/n): ");
        scanf(" %c", &again);
    } while (again == 'y' || again == 'Y');

    printf("Thank you for using the calculator.\n");
    return 0;
}
