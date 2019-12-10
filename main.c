#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 100

int expression();
int matrix();
int exp_calc(char str[MAXLINE]);
void print_array(char str[]);
void strConversion(char str[MAXLINE][MAXLINE], int term);

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
    for (unsigned long i = 0; i < strlen(str); i++)
    {
        printf("%c", str[i]);
    }
    printf("\'");
}

void strConversion(char str[MAXLINE][MAXLINE], int term)
{
    printf("\n\t array -> \n");
    for (int i = 0; i < term; i++)
    {
        printf("\t\'");
        for (unsigned long j = 0; j < strlen(str[i]); j++)
        {
            printf("%c", str[i][j]);
        }
        printf("\'\n");
    }
}

int exp_calc(char str[MAXLINE])
{
    //eular calculation
    return 0;
}

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
        gets(equation);

        for (int i = 0; i < strlen(equation); i++)
        {
            if ((equation[i] == '-' && equation[i + 1] == '-') || (equation[i] == '+' && equation[i + 1] == '+'))
            {
                printf("\nYou entered two operator in a row -> %c%c", equation[i], equation[i + 1]);
                printf("\n                            index no ^^");
                printf("\n                                     %d%d", i / 10, (i + 1) / 10);
                printf("\n                                     %d%d\n", i % 10, (i + 1) % 10);
                approval = 0;
                break;
            }
            else if (strchr(approved, equation[i]) == NULL)
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

    ///*
    int space = 0, func = 0, term = 0;
    char operation[MAXLINE][MAXLINE];
    char temp[MAXLINE], temp_exp[MAXLINE];
    memset(&temp[0], 0, sizeof(temp));
    memset(&operation[0][0], 0, sizeof(operation));

    for (int i = 0; i < strlen(equation); i++)
    {
        printf("\nfor loop i: %d", i);
        if (equation[i] == '-' || equation[i] == '+' || (i == 0 && (equation[i] != '-' || equation[i] != '+')))
        {
            func = 0;
            i++;

            if (i == 1 && (equation[i - 1] != '-' && equation[i - 1] != '+'))
                i--;

            //memset(&temp[0], 0, sizeof(temp));

            if (equation[i - 1] != NULL)
                operation[term][0] = equation[i - 1]; //temp[0] = equation[i - 1];
            else
                operation[term][0] = '+'; //temp[0] = '+';

            while ((equation[func + i] != '-' && equation[func + i] != '+') != (equation[func + i - 1] == '('))
            {
                if (equation[i + func] == 'e' && equation[i + 1 + func] == 'x' && equation[i + 2 + func] == 'p' && equation[i + 3 + func] == '(')
                {
                    term++;
                    int tfunc = 0;
                    func += 4;
                    memset(&temp_exp[0], 0, sizeof(temp_exp));
                    while (equation[func + i + tfunc] != ')')
                    {
                        operation[term][tfunc] = equation[func + i + tfunc]; //temp_exp[tfunc] = equation[func + i + tfunc];
                        tfunc++;
                    }

                    printf("\n\t func exp:%d", tfunc);
                    print_array(operation[term]);
                    func += tfunc;
                }
                operation[term][func + 1] = equation[func + i]; //temp[func + 1] = equation[func + i];
                func++;
            }
            printf("\n\t func:%d", func);
            print_array(operation[term - 1]);
            i += func - 1;
            term++;
        }
    }

    strConversion(operation, term);

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
