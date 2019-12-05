#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 100

int expression();
int matrix();
int exp_calc(char str[MAXLINE]);
void print_array(char str[]);

typedef struct complex
{
    float real;
    float imag;
}

complex;
complex add(complex n1, complex n2);

complex add(complex n1, complex n2)
{
    complex temp;
    temp.real = n1.real + n2.real;
    temp.imag = n1.imag + n2.imag;
    return (temp);
}

/*

equation  1. layer --> 
                        0 : number
                        1 : complex number
                        2 : notation 

-         2. layer -->  

*/

void print_array(char str[])
{
    printf("\n\t array -> \'");
    for (int i = 0; i < strlen(str); i++)
    {
        printf("%c", str[i]);
    }
    printf("\'");
}

int exp_calc(char str[MAXLINE])
{
    return 0;
}

int main()
{
    int option = 0, approval = 0;
    char equation[MAXLINE];

    char approved[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '.', '0', '+', '-', '(', ')', ' ', 'e', 'x', 'p', 'j', 'i'};

    printf("Welcome to our COPMLEX NUMBER CALCULATOR");
    printf("\nby ....");
    printf("\n\nBefore continue please enter which mode you want to use: ");
    printf("\n\t1. Expression mode (default)");
    printf("\n\t2. Matrix mode\n : ");
    scanf("%d", &option);

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
        gets(equation);

        for (int i = 0; i < strlen(equation); i++)
        {
            if (strchr(approved, equation[i]) == NULL)
            {
                printf("\nYou entered unapproved character -- %c\n", equation[i]);
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
    real 
    1+2j+6exp(-0.3pij)+6j+9+0.23exp(-0.4j)+12j
    000000000011111111112222222222333333333344
    012345678901234567890123456789012345678901

    test for only numbers
    1+2j+6-6j-9+12j
    000000000011111
    012345678901234
    */

    ///*
    int space = 0, func = 0, factor = 1;
    float tempNumber = 0;
    char operation[MAXLINE][MAXLINE];
    char temp[MAXLINE];
    memset(&temp[0], 0, sizeof(temp));

    for (int i = 0; i < strlen(equation); i++)
    {
        printf("\nfor loop i: %d", i);
        if (equation[i] == 'e' && equation[i + 1] == 'x' && equation[i + 2] == 'p' && equation[i + 3] == '(')
        {
            func = 0;
            i += 4;
            memset(&temp[0], 0, sizeof(temp));
            while (equation[func + i] != ')')
            {
                temp[func] = equation[func + i];
                func++;
            }
            exp_calc(temp);
            printf("\n\t func:%d", func);
            print_array(temp);
            i += func;
        }
        else if (equation[i] == '-' || equation[i] == '+' || (i == 0 != (equation[i] == '-' || equation[i] == '+')))
        {
            func = 0;
            i++;
            if (i == 1)
                i--;
            memset(&temp[0], 0, sizeof(temp));
            while (equation[func + i] != '-' && equation[func + i] != '+')
            {
                temp[func] = equation[func + i];
                func++;
            }
            printf("\n\t func:%d", func);
            if (temp[strlen(temp) - 1] == 'j')
                operation[i][2] = temp;
            else
                operation[i][1] = temp;
            print_array(temp);
            i += func - 1;
        }
    }

    //*/

    printf("\n\nspaces: %d", space);
    printf("\n..");

    /*
    for (int i = 0; i < MAXLINE; i++)
    {
        for (int j = 0; j < 2; i++)
        {
            printf(" %d ", operation[i][j]);
        }
    }
    */
    if (option == 1)
        expression();
    else
        matrix();
    printf("\n...");
    return 0;
}

int expression()
{

    return 0;
}

int matrix()
{

    return 0;
}
