#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

int expression();
int matrix();

int main()
{
    int operation[MAXLINE][MAXLINE];
    int option = 0, approval = 0, space = 0, func = 0;
    char equation[MAXLINE];
    char approved[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '+', '-', '(', ')', ' ', 'e', 'x', 'p', 'j', 'i'};

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
            if (strchr(approved, equation[i])[0] != equation[i])
            {
                printf("\nYou entered unapproved character\n");
                approval = 0;
            }
            else
                approval = 1;
        }
    }

    printf("\n..");

    for (int i = 0; i < strlen(equation); i++)
    {
        if (equation[i] == 'e' && equation[i + 1] == 'x' && equation[i + 2] == 'p' && equation[i + 3] == '(')
        {
            func = i + 4;
            while (equation[func] != ')')
            {

                func++;
            }
            space += func + 1;
        }
        else
        {
            if (equation[i] <= '9' && equation[i] >= '0')
                operation[i - space][0] = equation[i] - '0';
            else if (equation[i] == '+')
                operation[i - space][1] = 1;
            else if (equation[i] == '-')
                operation[i - space][1] = 0;
            else if (equation[i] == '*')
                operation[i - space][1] = 2;
            else if (equation[i] == ' ')
                space++;
        }
    }

    printf("\n...");

    for (int i = 0; i < MAXLINE; i++)
    {
        for (int j = 0; j < 2; i++)
        {
            printf(" %d ", operation[i][j]);
        }
    }

    if (option == 1)
        expression();
    else
        matrix();

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
