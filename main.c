#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 100
#define MAX 5

//FOR EXPRESSION MODE --------------------------------------------------------------------
typedef struct complex_number
{
    double real;
    double imag;
} complex;

complex add(complex n1, complex n2);
complex calculate(double arr[]);

void print_array(char str_chr[]);
void print_int(double str_int[]);
char *ready_to_compile(char str[]);
double *compile(char str[], int temp_index);
int get_index(char str[], int space);
//FOR EXPRESSION MODE --------------------------------------------------------------------

//FOR MATRIX MODE --------------------------------------------------------------------
double arraytofloat(char string[], int i, double n);
void add_arr(double firstMatrix[][MAX], double secondMatrix[][MAX], double sum[][MAX], int row, int col);
void multiplyMatrices(double firstMatrix[][MAX], double secondMatrix[][MAX], double mult[][MAX], int rowFirst, int columnFirst, int rowSecond, int columnSecond);
void transpose(double num[][MAX], double fac[][MAX], float r, double inverse[][MAX]);
void cofactor(double num[][MAX], float f, double inverse[][MAX]);
double determinant(double a[][MAX], float k);
void transpose_matrix(double matrix[][MAX], int row, double inverse[][MAX]);
int ruleschecker(int proper, int row1, int row2, int row3, int row4, int row5, int row6, int col1, int col2, int col3, int col4, int col5, int col6);
void printarray(double Matrix[][MAX], int row, int column);

//FOR MATRIX MODE --------------------------------------------------------------------

int main()
{
    printf("\e[1;1H\e[2J");
    int option = 0, approval = 0;
    int debug = 0;
    char equation[MAXLINE];

    char approved[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '.', '0', '+', '-', '(', ')', ' ', 'e', 'x', 'p', 'j', 'i', '\n'};

    printf("Welcome to our COMPLEX NUMBER CALCULATOR");
    printf("\nby ....");
    printf("\n\nBefore continue please enter which mode you want to use: ");
    printf("\n\t1. Expression mode (default)");
    printf("\n\t2. Matrix mode\n : ");
    char ch;
    if (!debug)
        ch = fgetc(stdin);

    if (ch == '\n' || ch == '1')
        option = 1;
    else if (ch == '2')
        option = 2;

    if (debug)
        option = 1;

    while (option != 1 && option != 2)
    {
        fflush(stdin);
        printf("\nYou entered invalid choose");
        printf("\n\nBefore continue please enter which mode you want to use: ");
        printf("\n\t1. Expression mode");
        printf("\n\t2. Matrix mode\n : ");
        scanf("%d", &option);
    }

    if (option == 1)
    {

        while (approval == 0)
        {
            fflush(stdin);
            printf("Please type your equation: ");
            fflush(stdin);
            memset(&equation[0], 0, sizeof(equation));
            fgets(equation, MAXLINE, stdin);

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

        char operation[MAXLINE][MAXLINE];
        double *result[MAXLINE];
        int index1 = 0, index2 = 0, inside = 0;
        memset(&operation[0], '\0', sizeof(operation));
        memset(&result[0], '\0', sizeof(result));

        for (unsigned long i = 0; i < strlen(equation); i++)
        {
            if (equation[i] == '(')
                inside = 1;
            else if (equation[i] == ')')
                inside = 0;
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

        char *compiled[index1];
        int temp_index;
        complex res;
        res.imag = 0;
        res.real = 0;

        for (int i = 0; i <= index1; i++)
        {
            compiled[i] = ready_to_compile(operation[i]);
            temp_index = get_index(operation[i], 0);
            result[i] = compile(compiled[i], temp_index);
            //print_int(result[i]);
            res = add(calculate(result[i]), res);
        }

        printf("\n\treal : %f, imag : %f", res.real, res.imag);
    }
    else if (option == 2)
    {
        char string[MAXLINE];
        memset(&string[0], 0, sizeof(string));
        int approval;
        char approved1[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'M', '+', '-', 'i', 'n', 'v', '*', '(', ')', '\''};
        char approved2[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '.', '0'};
        int chance = 3;
        do
        {
            if (chance < 3 && chance > 1)
            {
                printf("\nYou have %d more times to try ..\n", chance);
            }
            else if (chance == 1)
            {
                printf("\nYou have %d more time to try ..\n", chance);
            }
            printf("\n***************************");
            printf("\nEnter the string..\n\t");
            gets(string);
            for (int i = 0; i < strlen(string); i++)
            {
                if (strchr(approved1, string[i]) == NULL)
                {
                    printf("\nYou entered unapproved character -> %c\n", string[i]);
                    approval = 0;
                }
                else
                {
                    approval = 1;
                }
            }
            chance--;

        } while (approval == 0 && chance > 0);

        if (approval == 1)
        {

            //detects the name of matrices
            int countM = 0;
            char MatrixName[MAXLINE][2];
            memset(&MatrixName[0], 0, sizeof(MatrixName));
            for (int i = 0; i < strlen(string); i++)
            {
                if (string[i] == 'M')
                {
                    MatrixName[countM][0] = 'M';
                }
                else if (isdigit(string[i]))
                {
                    MatrixName[countM][1] = (countM + 1);
                    countM++;
                }
            }

            char matrices[MAXLINE];
            double M1[5][5], M2[5][5], M3[5][5], M4[5][5], M5[5][5], M6[5][5];
            memset(&matrices[0], 0, sizeof(matrices)), memset(&M1[0], 0, sizeof(M1)), memset(&M2[0], 0, sizeof(M2)), memset(&M3[0], 0, sizeof(M3));
            memset(&M4[0], 0, sizeof(M4)), memset(&M5[0], 0, sizeof(M5)), memset(&M6[0], 0, sizeof(M6));
            int chance = 3;

            do
            {
                if (chance < 3 && chance > 1)
                {
                    printf("\nYou have %d more times to try ..\n", chance);
                }
                else if (chance == 1)
                {
                    printf("\nYou have %d more time to try ..\n", chance);
                }
                printf("Enter all matrices:\n\tWhen you finished entering a row enter ','\n\tWhen you finished entering a matrix enter '.'\n");
                gets(matrices);

                for (int i = 0; i < strlen(matrices); i++)
                {
                    if (strchr(approved2, matrices[i]) == NULL)
                    {
                        printf("\nYou entered unapproved character -> %c", string[i]);
                        approval = 0;
                    }
                }
                chance--;

            } while (approval == 0 && chance > 0);

            int row1 = 1, row2 = 1, row3 = 1, row4 = 1, row5 = 1, row6 = 1;
            int col1 = 0, col2 = 0, col3 = 0, col4 = 0, col5 = 0, col6 = 0;
            int row = 0, column = 0;
            int M = 1;
            for (int i = 0; i < strlen(matrices); i++)
            {
                double n = 0.0;
                if (matrices[i] != '.')
                {
                    if (M == 1)
                    {
                        if (matrices[i] != ',')
                        {
                            M1[row][column] = arraytofloat(matrices, i, n);
                            column++, col1++;
                        }
                        else if (matrices[i] == ',')
                        {
                            row++, row1++;
                            column = 0;
                        }
                    }
                    else if (M == 2)
                    {
                        if (matrices[i] != ',')
                        {
                            M2[row][column] = arraytofloat(matrices, i, n);
                            column++, col2++;
                        }
                        else if (matrices[i] == ',')
                        {
                            row++, row2++;
                            column = 0;
                        }
                    }
                    else if (M == 3)
                    {
                        if (matrices[i] != ',')
                        {
                            M3[row][column] = arraytofloat(matrices, i, n);
                            column++, col3++;
                        }
                        else if (matrices[i] == ',')
                        {
                            row++, row3++;
                            column = 0;
                        }
                    }
                    else if (M == 4)
                    {
                        if (matrices[i] != ',')
                        {
                            M4[row][column] = arraytofloat(matrices, i, n);
                            column++, col4++;
                        }
                        else if (matrices[i] == ',')
                        {
                            row++, row4++;
                            column = 0;
                        }
                    }
                    else if (M == 5)
                    {
                        if (matrices[i] != ',')
                        {
                            M5[row][column] = arraytofloat(matrices, i, n);
                            column++, col5++;
                        }
                        else if (matrices[i] == ',')
                        {
                            row++, row5++;
                            column = 0;
                        }
                    }
                    else if (M == 6)
                    {
                        if (matrices[i] != ',')
                        {
                            M6[row][column] = arraytofloat(matrices, i, n);
                            column++, col6++;
                        }
                        else if (matrices[i] == ',')
                        {
                            row++, row6++;
                            column = 0;
                        }
                    }
                }
                else if (matrices[i] == '.')
                {
                    M++;
                    row = 0;
                    column = 0;
                }
            }

            if (approval == 1)
            {

                col1 = col1 / row1, col2 = col2 / row2, col3 = col3 / row3, col4 = col4 / row4, col5 = col5 / row5, col6 = col6 / row6;
                printf("\n");
                printf("%c%d :\n", MatrixName[0][0], MatrixName[0][1]);
                printarray(M1, row1, col1);
                printf("%c%d :\n", MatrixName[1][0], MatrixName[1][1]);
                printarray(M2, row2, col2);
                printf("%c%d :\n", MatrixName[2][0], MatrixName[2][1]);
                printarray(M3, row3, col3);
                printf("%c%d :\n", MatrixName[3][0], MatrixName[3][1]);
                printarray(M4, row4, col4);
                printf("%c%d :\n", MatrixName[4][0], MatrixName[4][1]);
                printarray(M5, row5, col5);
                printf("%c%d :\n", MatrixName[5][0], MatrixName[5][1]);
                printarray(M6, row6, col6);

                int approval = 1;
                ruleschecker(approval, row1, row2, row3, row4, row5, row6, col1, col2, col3, col4, col5, col6);

                // equation 1 = M1+M2*M3-inv(M4)'*M5+M6   equation 2 = M1+M2*M3-inv(M4')*M5+M6

                int equation;
                for (int i = 0; i < strlen(string); i++)
                {
                    if (string[i] == ')' && string[i + 1] == '\'')
                    {
                        equation = 1;
                    }
                    else if (string[i] == '\'' && string[i + 1] == ')')
                    {
                        equation = 2;
                    }
                }

                float d;
                double R1[MAX][MAX], R2[MAX][MAX], R3[MAX][MAX], R4[MAX][MAX], R5[MAX][MAX], R6[MAX][MAX], R7[MAX][MAX];
                memset(&R1[0], 0, sizeof(R1)), memset(&R2[0], 0, sizeof(R2)), memset(&R3[0], 0, sizeof(R3)), memset(&R4[0], 0, sizeof(R4));
                memset(&R5[0], 0, sizeof(R5)), memset(&R6[0], 0, sizeof(R6)), memset(&R7[0], 0, sizeof(R7));

                if (equation == 1)
                {

                    d = determinant(M4, row4);
                    if (d == 0)
                    {
                        printf("\n\tInverse of Entered Matrix is not possible\n");
                        approval = 0;
                    }
                    else
                        cofactor(M4, row4, R1);

                    transpose_matrix(R1, row4, R2);
                    multiplyMatrices(R2, M5, R3, col4, row4, row5, col5);
                    multiplyMatrices(M2, M3, R4, row2, col2, row3, col3);
                    add_arr(M1, R4, R5, row1, col1);
                    add_arr(R5, R3, R6, row1, col1);
                    add_arr(R6, M6, R7, row1, col1);
                }
                else if (equation == 2)
                {

                    transpose_matrix(M4, row4, R1);
                    d = determinant(R1, row4);
                    if (d == 0)
                    {
                        printf("\n\tInverse of Entered Matrix is not possible\n");
                        approval = 0;
                    }
                    else
                        cofactor(R1, row4, R2);

                    multiplyMatrices(R2, M5, R3, col4, row4, row5, col5);
                    multiplyMatrices(M2, M3, R4, row2, col2, row3, col3);
                    add_arr(M1, R4, R5, row1, col1);
                    add_arr(R5, R3, R6, row1, col1);
                    add_arr(R6, M6, R7, row1, col1);
                }

                if (approval == 1)
                {

                    printf("Result Matrix is :\n");
                    printarray(R7, row6, col6);
                    char c;
                    printf("\tIf you want to see steps enter '*'\n\tIf you want to finished enter '.'\n");
                    scanf("%c", &c);

                    if (c == '*')
                    {
                        if (equation == 1)
                        {
                            printf("Inverse of Matrix\n");
                            printarray(R1, row4, col4);
                            printf("Transpose of Matrix:\n");
                            printarray(R2, row4, col4);
                        }
                        else if (equation == 2)
                        {
                            printf("Transpose of Matrix:\n");
                            printarray(R1, row4, col4);
                            printf("Inverse of Matrix\n");
                            printarray(R2, row4, col4);
                        }
                        printf("Multiplication of Matrices\n");
                        printarray(R3, row4, col4);
                        printf("Multiplication of Matrices\n");
                        printarray(R4, row4, col4);
                        printf("Addition of Matrices\n");
                        printarray(R5, row4, col4);
                        printf("Addition of Matrices\n");
                        printarray(R6, row4, col4);
                        printf("Addition of Matrices\n");
                        printarray(R7, row4, col4);
                    }
                    else if (c == '.')
                    {
                        printf("Mission completed..\n");
                    }
                }
            }
        }
    }
    printf("\n\nquiting !!\n");
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

double *compile(char str[], int temp_index)
{
    double op[MAXLINE];
    memset(&op[0], '\0', sizeof(op));

    if (temp_index == 0 || temp_index == 1)
    {
        op[0] = temp_index;
        op[1] = 1;
        op[2] = atof(str);
    }
    else if (temp_index == 2)
    {
        op[0] = temp_index;
        op[1] = 3;
        op[2] = atof(str);
        op[4] = 1;

        char *ptr = strtok(str, "*");
        char buffer[10];
        ptr = strtok(NULL, "*");
        op[3] = atof(ptr);
        ptr = strtok(ptr, "j");
        gcvt(op[3], 10, buffer);
        if (strcmp(ptr, buffer) != 0)
            op[4] = M_PI;
    }

    return op;
}

/*
    * 0 real 
    * 1 coplex 
    * 2 exp 
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

complex calculate(double arr[])
{
    complex temp;
    temp.imag = 0;
    temp.real = 0;

    for (int i = 0; i < (int)arr[1]; i++)
    {

        if (arr[0] == 0)
        {
            temp.imag = 0;
            temp.real = arr[2];
            return temp;
        }
        else if (arr[0] == 1)
        {
            temp.imag = arr[2];
            temp.real = 0;
            return temp;
        }
        else if (arr[0] == 2)
        {
            double degree = 180.0 * arr[3] * arr[4];
            temp.real = arr[2] * cos(degree);
            temp.imag = arr[2] * sin(degree);
            return temp;
        }
    }
}

complex add(complex n1, complex n2)
{
    complex temp;
    temp.real = n1.real + n2.real;
    temp.imag = n1.imag + n2.imag;
    return temp;
}

void printarray(double Matrix[][MAX], int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%.2f  ", Matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

double arraytofloat(char string[], int i, double n)
{
    n = (string[i] - '0');
    return n;
}

int ruleschecker(int proper, int row1, int row2, int row3, int row4, int row5, int row6, int col1, int col2, int col3, int col4, int col5, int col6)
{

    if (row2 != row3 || col2 != col3)
    {
        printf("\nThe dimensions of Matrices that you have entered M2 and M3 are not same...\n");
        proper = 0;
    }
    if (row1 != row2 || col1 != col2)
    {
        printf("\nThe dimensions of Matrices that you have entered M1 and M2are not same...\n");
        proper = 0;
    }
    if (row5 != row6 || col5 != col6)
    {
        printf("\nThe dimensions of Matrices that you have entered M5 and M6 are not same...\n");
        proper = 0;
    }
    else
    {
        proper = 1;
    }

    return proper;
}

/*For calculating Determinant of the Matrix */
double determinant(double a[][MAX], float k)
{

    double s = 1, det = 0, b[MAX][MAX];
    int i, j, m, n, c;
    if (k == 1)
    {
        return (a[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }

    return (det);
}

void cofactor(double num[][MAX], float f, double inverse[][MAX])
{

    double b[MAX][MAX], fac[MAX][MAX];
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++)
    {
        for (p = 0; p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++)
            {
                for (j = 0; j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }

    transpose(num, fac, f, inverse);
}
/*Finding transpose of matrix*/
void transpose(double num[][MAX], double fac[][MAX], float r, double inverse[][MAX])
{

    int i, j;
    double b[MAX][MAX], d;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
    }
    d = determinant(num, r);

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }
}

void transpose_matrix(double matrix[][MAX], int row, double Result[][MAX])
{

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            Result[j][i] = matrix[i][j];
        }
    }
}

void multiplyMatrices(double firstMatrix[][MAX], double secondMatrix[][MAX], double mult[][MAX], int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{

    int i, j, k;

    // Initializing elements of matrix mult to 0.
    for (i = 0; i < rowFirst; ++i)
    {
        for (j = 0; j < columnSecond; ++j)
        {
            mult[i][j] = 0;
        }
    }

    // Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
    for (i = 0; i < rowFirst; ++i)
    {
        for (j = 0; j < columnSecond; ++j)
        {
            for (k = 0; k < columnFirst; ++k)
            {
                mult[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

void add_arr(double firstMatrix[][MAX], double secondMatrix[][MAX], double sum[][MAX], int row, int col)
{

    int k = 1;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (firstMatrix[i][j] >= '0' && firstMatrix[i][j] <= '9')
            {
                firstMatrix[i][j] = k * (firstMatrix[i][j] - '0');
            }
            else if (firstMatrix[i][j] == '+')
            {
                k = 1;
            }
            else if (firstMatrix[i][j] == '-')
            {
                k = -1;
            }
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (secondMatrix[i][j] >= '0' && secondMatrix[i][j] <= '9')
            {
                secondMatrix[i][j] = k * (secondMatrix[i][j] - '0');
            }
            else if (secondMatrix[i][j] == '+')
            {
                k = 1;
            }
            else if (secondMatrix[i][j] == '-')
            {
                k = -1;
            }
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sum[i][j] = (firstMatrix[i][j] + secondMatrix[i][j]);
        }
    }
}