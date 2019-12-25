#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 100

typedef struct complex_number
{
    double real;
    double imag;
} complex;

complex add(complex n1, complex n2);

void print_array(char str_chr[]);
void print_int(double str_int[]);
char *ready_to_compile(char str[]);
double *compile(char str[], int temp_index);
int get_index(char str[], int space);

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
            if (index2 == 0)
                operation[index1][index2] = (i != 0) ? ((equation[i - 1] == '-') ? '-' : '+') : '+';

            operation[index1][index2 + 1] = equation[i];
            index2++;
        }
    }

    printf("\n..");
    //fflush(stdout);
    double *result[MAXLINE][2];
    memset(&result[0], '\0', sizeof(result));
    char *compiled[index1];
    int temp_index;

    for (int i = 0; i <= index1; i++)
    {
        compiled[i] = ready_to_compile(operation[i]);
        temp_index = get_index(operation[i], 0);
        result[i][temp_index] = compile(compiled[i], temp_index);
        print_int(result[i][temp_index]);
    }

    printf("\n...");

    printf("\n\nquiting!");
    return 0;
}

/*
    1+2j+6exp(-0.3pij)+6j+9+0.23exp(-0.4j)+12j
*/

char *ready_to_compile(char str[])
{
    int index = 0;
    int len = strlen(str);
    for (int i = 0; i < len - index; i++)
    {
        if (str[i] == 'e' && str[i + 1] == 'x' && str[i + 2] == 'p')
        {
            index += 2;
            str[i] = '*';
        }
        else
        {
            str[i] = str[i + index];
        }
    }
    for (int i = len - index; i < len; i++)
        str[i] = '\0';

    len -= index;

    return str;
}

/*
    1+2j+6exp(-0.3pij)+6j+9+0.23exp(-0.4j)+12j
*/

double *compile(char str[], int temp_index)
{
    double op[MAXLINE];
    memset(&op[0], '\0', sizeof(op));

    if (temp_index == 0 || temp_index == 1)
    {
        op[0] = temp_index;
        op[1] = atof(str);
    }
    else if (temp_index == 2)
    {
        op[0] = temp_index;
        op[1] = atof(str);

        char *ptr = strtok(str, "*");
        ptr = strtok(NULL, "*");
        op[2] = atof(ptr);
        printf("\n%s\n", ptr);
        ptr = strtok(NULL, "p");
        printf("\n%s\n", ptr);
    }

    return op;
}

/*
    * 0 real NUMBER
    * 1 coplex NUMBER
    * 2 exp function
*/

int get_index(char str[], int space)
{
    int state = 0;

    for (unsigned long i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'j')
            state = 1;
        else if (str[i] == '*')
            state = 2;
        else
            state = 0;

        if (state != 0)
            break;
    }
    return state;
}

void print_array(char str_chr[])
{
    printf("\n\t array -> \'");
    for (unsigned long i = 0; i < strlen(str_chr); i++)
    {
        printf("%c", str_chr[i]);
    }
    printf("\'");
}

void print_int(double str_int[])
{
    printf("\n\t array -> \'");
    for (unsigned long i = 0; i < sizeof(str_int); i++)
        if ((str_int[i] != 0) || ((str_int[i] != 0) != (i == 0)))
            printf("[%.2f]", str_int[i]);

    printf("\'");
}

complex add(complex n1, complex n2)
{
    complex temp;
    temp.real = n1.real + n2.real;
    temp.imag = n1.imag + n2.imag;
    return temp;
}