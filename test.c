#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 100

void print_array(char str[]);
void compile_text(char str[]);

int main()
{
    int option = 0, approval = 0;
    int debug = 1;
    char equation[MAXLINE];

    char approved[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '.', '0', '+', '-', '(', ')', ' ', 'e', 'x', 'p', 'j', 'i'};

    printf("Welcome to our COPMLEX NUMBER CALCULATOR");
    printf("\nby ....");
    printf("\n\nBefore continue please enter which mode you want to use: ");
    printf("\n\t1. Expression mode (default)");
    printf("\n\t2. Matrix mode\n : ");
    if (!debug)
        scanf("%d", &option);

    if (debug)
        option = 1;

    while (option != 1 && option != 2)
    {
        fflush(stdin);
        printf("\nYou entered invalid choose");
        printf("\n\nBefore continue please enter which mode you want to use: ");
        printf("\n\t1. Expression mode (default)");
        printf("\n\t2. Matrix mode\n : ");
        scanf("%d", &option);
    }

    while (approval == 0)
    {
        fflush(stdin);
        printf("Please type your equation: ");
        fflush(stdin);
        memset(&equation[0], 0, sizeof(equation));
        gets(equation);

        for (unsigned long i = 0; i < strlen(equation); i++)
        {
            if ((equation[i] == '-' && equation[i + 1] == '-') || (equation[i] == '+' && equation[i + 1] == '+'))
            {
                printf("\nYou entered two operator in a row -> %c%c", equation[i], equation[i + 1]);
                printf("\n                            index no ^^");
                printf("\n                                     %lu%lu", i / 10, (i + 1) / 10);
                printf("\n                                     %lu%lu\n", i % 10, (i + 1) % 10);
                approval = 0;
                break;
            }
            else if (strchr(approved, equation[i]) == NULL)
            {
                printf("\nYou entered unapproved character -> %c", equation[i]);
                printf("\n                           index no ^");
                printf("\n                                    %lu", i / 10);
                printf("\n                                    %lu\n", i % 10);
                approval = 0;
                break;
            }
            else
                approval = 1;
        }
    }

    printf("\n.");

    //Analyze equation and store its compenents in operation list

    /*
    1+2j+6exp(-0.3pij)+6j+9+0.23exp(-0.4j)+12j
    */

    char operation[MAXLINE][MAXLINE];
    int index1 = 0, index2 = 0, inside = 0;
    memset(&operation[0], '\0', sizeof(operation));

    for (unsigned long i = 0; i < strlen(equation); i++)
    {
        if (equation[i] == '(')
        {
            inside = 1;
        }
        else if (equation[i] == ')')
        {
            inside = 0;
        }
        else if ((equation[i] == '-' || equation[i] == '+') && inside == 0)
        {
            index1++;
            index2 = 0;
        }
        else
        {
            operation[index1][index2] = equation[i];
            index2++;
        }
    }

    for (int i = 0; i <= index1; i++)
    {

        print_array(operation[i]);
    }
}

void compile_text(char str[])
{
    for (unsigned long i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'e' && str[i + 1] == 'x' && str[i + 2] == 'p')
        {
            ;
        }
    }
}

void print_array(char str[])
{
    printf("\n\t array -> \'");
    for (unsigned long i = 0; i < strlen(str); i++)
    {
        printf("%c", str[i]);
    }
    printf("\'");
}