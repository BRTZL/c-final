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
complex exp_calc(char str[MAXLINE], complex number);
complex norm_calc(char str[MAXLINE], complex number);

int matrix();
int expression();
void print_array(char str[]);
complex euler(char str[MAXLINE]);
void strConversion(char str[MAXLINE][MAXLINE], int term);

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
    complex number;
    number.real = 0;
    number.imag = 0;

    printf("\nArray -> \n");
    for (int i = 0; i < term; i++)
    {
        int len = strlen(str[i]);
        for (int j = 0; j < len; j++) //removing unnecessary spaces
        {
            if (str[i][j] == ' ')
            {
                for (int z = j; z < len; z++)
                {
                    str[i][z] = str[i][z + 1];
                }
                len--;
            }
        }

        printf("\n\t\'%s\'", str[i]);

        if (str[i][len - 1] == 'j' || str[i][len - 2] == 'j')
            number = exp_calc(str[i], number);
        else
            number = norm_calc(str[i], number);
        printf("\n\treal: %.3f imag: %.3f\n", number.real, number.imag);
    }

    //printf("\n\n\treal: %.3f imag: %.3f", number.real, number.imag);
}
/*
1+2j+6exp(-0.3pij)+6j+9+0.23exp(-0.4j)+12j
*/
complex norm_calc(char str[MAXLINE], complex number)
{
    complex temp;
    printf("\n\t\'%.2f\'", atof(str));
    temp.real = atof(str);
    temp.imag = 0;

    temp = add(temp, number);
    return temp;
}

complex exp_calc(char str[MAXLINE], complex number)
{
    //eular calculation
    complex temp;

    printf("\n\t\'%.2fj\'", atof(str));
    if (str[strlen(str) - 1] == 'e')
    {
        temp = euler(str);
    }
    else
    {
        temp.imag = atof(str);
        temp.real = 0;
    }

    temp = add(temp, number);
    return temp;
}

complex euler(char str[MAXLINE])
{
    complex temp;
    temp.imag = 0;
    temp.real = 0;

    return temp;
}

complex add(complex n1, complex n2)
{
    complex temp;
    temp.real = n1.real + n2.real;
    temp.imag = n1.imag + n2.imag;
    return (temp);
}



    ///*
    int space = 0, func = 0, term = 0;
    char operation[MAXLINE][MAXLINE];
    char temp[MAXLINE], temp_exp[MAXLINE];
    memset(&temp[0], 0, sizeof(temp));
    memset(&operation[0][0], 0, sizeof(operation));

    for (unsigned long i = 0; i < strlen(equation); i++)
    {
        //printf("\n\nfor loop i: %d", i);
        if (equation[i] == '-' || equation[i] == '+' || (i == 0 && (equation[i] != '-' || equation[i] != '+')))
        {
            func = 0;
            i++;

            if (i == 1 && (equation[i - 1] != '-' && equation[i - 1] != '+'))
                i--;

            //memset(&temp[0], 0, sizeof(temp));

            if (equation[i - 1] != '\0')
                operation[term][0] = equation[i - 1]; //temp[0] = equation[i - 1];
            else
                operation[term][0] = '+'; //temp[0] = '+';

            while ((equation[func + i] != '-' && equation[func + i] != '+') != (equation[func + i - 1] == '('))
            {
                
                    term++;
                    space = 0;
                    int tfunc = 0;
                    func += 4;
                    //operation[term][tfunc - space] = 'e';
                    memset(&temp_exp[0], 0, sizeof(temp_exp));
                    while (equation[i + func + tfunc] != ')')
                    {
                        if (equation[i + func + tfunc] == 'p' && equation[i + func + tfunc + 1] == 'i')
                        {
                            operation[term][tfunc - space] = 'p';
                            space++;
                            tfunc += 2;
                        }
                        else
                        {
                            operation[term][tfunc - space] = equation[func + i + tfunc]; //temp_exp[tfunc] = equation[func + i + tfunc];
                            tfunc++;
                        }
                    }
                    operation[term][tfunc - space] = 'e';
                    // printf("\n\t func exp:%d", tfunc);
                    // print_array(operation[term]);
                    func += tfunc;
                }
                else if (equation[i + func + 1] == 'e' && )
                {
                }
                else
                {
                    operation[term][func + 1] = equation[func + i]; //temp[func + 1] = equation[func + i];
                    func++;
                }
            }
            //printf("\n\t func:%d", func);
            //print_array(operation[term]);
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
