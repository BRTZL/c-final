#include <string.h>
#include <mouse.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>
#include <stdio.h>
#include <alloc.h>

#define pi 3.1415265

union REGS i, o;
int sr, dpf;
char *no[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "+/-"},
     *cal[] = {"+", "-", "*", "/", "=", "ã"},
     *sci[] = {"Sin", "Cos", "Tan", "Sinh", "Cosh", "Tanh", "Exp", "ln", "log", "xrty", "1/x", "x^2", "x^y", "sqrt", "fact", "Hypot", "eqn", "DEG"},
     *ms[] = {"AC", "HEX", "BIN", "OCT", "BKSP"};

long com(long, int);
long double back(long double), equ(), alg(long double, int);
double ns(long double, int);
int box(int, int, int, int, int);
char *z2;
long double *z1;
int xy1[3];

//-----DRAW THE BODY OF CALCULATOR

void draw()
{
    int gm, gd = DETECT;
    int x, y, x1, y1, i, j;

    initgraph(&gd, &gm, "c:tcbgi"); //INITIALISE GRAPHICS

    z2 = (char *)malloc(sizeof(char) * 10); /*ALLOCATE MEMORY TO z2*/

    x = getmaxx();
    y = getmaxy();

    setcolor(DARKGRAY);
    setfillstyle(1, CYAN);
    floodfill(5, 5, DARKGRAY);
    setcolor(BLACK);
    setfillstyle(1, LIGHTGRAY);
    rectangle(20, 20, x - 20, y - 20);
    floodfill(50, 50, BLACK);
    setcolor(BLACK);
    line(20, 20, x - 20, 20);
    line(20, 20, 20, y - 20);
    setcolor(BLUE);
    setfillstyle(1, BLUE);
    rectangle(21, 20, x - 21, 40);
    floodfill(25, 25, BLUE);
    setcolor(BLACK);

    outtextxy(x / 5, 8, "Scientific Calculator");

    initmouse();
    showmouse();
    setmouse(0, 0);

    setcolor(WHITE);
    setfillstyle(1, WHITE);
    rectangle(30, 55, x - 30, 70); //---white i/o box
    floodfill(32, 59, WHITE);

    outtextxy(x - 220, 27, "Press Any Key To Quit."); //---Quit
    setcolor(DARKGRAY);

    line(235, 95, 235, y - 30); //grey partition line
    setfillstyle(1, LIGHTGRAY);

    /*------------------printing nos.---------------------*/

    i = 0;
    for (x1 = 40; x1 < 150; x1 += 30)
    {
        j = 0;
        for (y1 = 100; y1 < 450; y1 += 40)
        {
            box(x1, y1, 40, WHITE, BLACK);
            setcolor(BLUE);
            if (i == 1 && j == 10)
                outtextxy(x1 + 10, y1 + 20, no[i + j]);
            else
                outtextxy(x1 + 15, y1 + 20, no[i + j]);
            y1 += 20;
            j += 2;
        }
        i++;
        x1 += 40;
    }

    /*---------------------------------------------------------------*/
    /*--------printing simple algebric functions:(+,-,*,/)----------*/

    for (x1; x1 <= 180; x1 += 40)
    {
        j = 0;
        for (y1 = 100; y1 < 450; y1 += 40) /*x1=180*/
        {
            box(x1, y1, 40, WHITE, BLACK);
            setcolor(BLUE);
            outtextxy(x1 + 15, y1 + 20, cal[j]);
            y1 += 20;
            j++;
        }
    }
    x1 += 30; /*-----------------------------------------------------------------*/
    12
        /*--------------------print scientific functions-------------------*/ i = 0;
    for (x1; x1 < 501; x1 += 30)
    {
        j = 0;
        for (y1 = 100; y1 < 450; y1 += 40)
        {
            box(x1, y1, 70, WHITE, BLACK); /*x1=220*/
            setcolor(BLUE);
            outtextxy(x1 + 15, y1 + 20, sci[i + j]);
            y1 += 20;
            j += 3;
        }
        xy1[i] = x1; /*store X coordinates*/
        i++;
        x1 += 70;
    }

    /*-----------------------------------------------------------------*/
    /*------------------print MATHEMATICAL SYSTEMS: BIN,HEX-------------*/

    for (x1; x1 <= 550; x1 += 30)
    {
        j = 0;
        for (y1 = 100; y1 < 450; y1 += 40) /*x1=550*/
        {
            if (j == 5)
                break;
            box(x1, y1, 55, WHITE, BLACK);
            setcolor(RED);
            outtextxy(x1 + 15, y1 + 20, ms[j]);
            y1 += 20;
            j++;
        }
    }
    mouse();
}
void main() //MAIN DECLARATION
{
    password();
    draw();
}

/*-----------MOUSE PROGRAMMING------------*/

mouse()
{
    int button, x, y;
    char s[13] = {" "};
    int x1, y1, i, j, flag = 1, l;
    long double n, k;
    while (!kbhit())
    {
    Again:
        getmouse(&button, &x, &y);
        while (button == 1)
        {
            getmouse(&button, &x, &y);
            sr = 1;
            13
        }
        if (sr == 1)
        {
            i = 0;
            sr = 0;
            if (x >= xy1[0] && x <= (xy1[0] + 70)) /*fourth column check*/
            {
                colm1(n, y);
                dpf = 0;
                strcpy(s, " ");
            }
            if (x >= xy1[1] && x <= (xy1[1] + 70)) /*fifth column check*/
            {
                colm2(n, y);
                dpf = 0;
                strcpy(s, " ");
            }
            if (x >= xy1[2] && x <= (xy1[2] + 70)) /*sixth column check*/
            {
                colm3(n, y);
                dpf = 0;
                strcpy(s, " ");
            }
            for (x1 = 40; x1 < 150; x1 += 30) //1st & 2nd column check
            {
                j = 0;
                setcolor(DARKGRAY);
                for (y1 = 100; y1 < 450; y1 += 40)
                {
                    if (x >= x1 && y >= y1 && x <= x1 + 40 && y <= y1 + 40)
                    {
                        box(x1, y1, 40, BLACK, WHITE);
                        delay(200);
                        box(x1, y1, 40, WHITE, BLACK);
                        if ((strcmp(no[i + j], no[11])) == 0)
                        {
                            if (flag == 1)
                            {
                                n *= -1; // +/- sign
                                s[0] = '-';
                                flag = 0;
                            }
                            else
                            {
                                n *= -1;
                                s[0] = ' ';
                                setcolor(LIGHTGRAY);
                                setfillstyle(1, WHITE);
                                floodfill(32, 59, LIGHTGRAY);
                                flag = 1;
                            }
                            goto NEXT;
                        }
                        if (strlen(s) >= 11)
                            goto Again;
                        if ((strcmp(no[i + j], no[10])) == 0)
                        {
                            if (dpf == 0)
                            {
                                14 strcat(s, no[i + j]); //save no. to string s
                                dpf = 1;
                            }
                        }
                        else
                            strcat(s, no[i + j]); //save no. to string s
                    NEXT:
                        n = _atold(s); //array to long double
                        setcolor(DARKGRAY);
                        outtextxy(30, 60, s); // display no. in i/o box
                        goto Again;
                    }
                    y1 += 20;
                    j += 2;
                }
                i++;
                x1 += 40;
            }
            if (x > 550 && x < 605 && y > 340 && y < 380) //BACKSPACE
            {
                delay(100);
                setcolor(LIGHTGRAY);
                setfillstyle(1, WHITE);
                floodfill(32, 59, LIGHTGRAY);
                l = strlen(s);
                if (s[l - 1] == '.')
                    dpf = 0;
                s[l - 1] = s[l];
                setcolor(DARKGRAY);
                outtextxy(30, 60, s);
                goto Again;
            }
            if (x > 550 && x < 605) // 7th column
            {
                setcolor(LIGHTGRAY);
                setfillstyle(1, WHITE);
                floodfill(32, 59, LIGHTGRAY);
                dpf = 0;
                ns(n, y);
                strcpy(s, " ");
                goto Again;
            }
            if (x > 180 && x < 220) // 3rd column
            {
                setcolor(LIGHTGRAY);
                setfillstyle(1, WHITE);
                floodfill(32, 59, LIGHTGRAY);
                dpf = 0;
                if (y > 400 && y < 440) // pi value
                {
                    box(180, 400, 40, BLACK, WHITE);
                    delay(200);
                    box(180, 400, 40, WHITE, BLACK);
                    15 n = pi;
                    setcolor(DARKGRAY);
                    outtextxy(30, 60, " 3.1415265");
                    goto Again;
                }
                alg(n, y);
                strcpy(s, " ");
                goto Again;
            }
        }
    }
    return;
}

/*-------perform algebric calculations---------*/

long double alg(long double n, int y)
{
    int y1;
    static int i;
    long double r;
    z1[i] = n;              //copy no. to z1
    if (y > 100 && y < 140) //--add
    {
        box(180, 100, 40, BLACK, WHITE);
        delay(200);
        box(180, 100, 40, WHITE, BLACK); // add(n);
        z2[i] = 43;
        i++;
        return 0;
    }
    if (y > 160 && y < 200) //subtract
    {
        box(180, 160, 40, BLACK, WHITE);
        delay(200);
        box(180, 160, 40, WHITE, BLACK); // sub(n);
        z2[i] = 45;
        i++;
        return 0;
    }
    if (y > 220 && y < 260) //multiply
    {
        box(180, 220, 40, BLACK, WHITE);
        delay(200);
        box(180, 220, 40, WHITE, BLACK); //mul(n);
        z2[i] = 42;
        i++;
        return 0;
    }
    if (y > 280 && y < 320) //divide
    {
        box(180, 280, 40, BLACK, WHITE);
        delay(200);
        box(180, 280, 40, WHITE, BLACK); //div(n);
        z2[i] = 47;
        i++;
        return 0;
    }
    16 if (y > 340 && y < 380) //equal
    {
        box(180, 340, 40, BLACK, WHITE);
        delay(200);
        box(180, 340, 40, WHITE, BLACK);
        z1[i + 1] = z2[i] = '0';
        equ();
        i = 0;
        return 0;
    }
    return 0;
}

/*---------solve algebric functions--------*/

long double equ()
{
    int i, j;
    char ch[50] = {" "};
    for (i = 0; z2[i] != '0';)
    {
        if (z2[i] == '/') /*------perform division------*/
        {
            z1[i] /= z1[i + 1];
            for (j = i; z2[j] != '0'; j++)
            {
                z1[j + 1] = z1[j + 2];
                z2[j] = z2[j + 1];
            }
        }
        else
            i++;
    } /*--------------*/
    for (i = 0; z2[i] != '0';)
    {
        if (z2[i] == '*') /*------perform multiplication------*/
        {
            z1[i] *= z1[i + 1];
            for (j = i; z2[j] != '0'; j++)
            {
                z1[j + 1] = z1[j + 2];
                z2[j] = (int)z2[j + 1];
            }
        }
        else
            i++; /*--------------*/
    }
    for (i = 0; z2[i] != '0';)
    {
        if (z2[i] == '+') /*------perform addition------*/
        {
            if (z2[i - 1] == '-')
                z1[i + 1] *= -1;
            z1[i] += z1[i + 1];
            17 for (j = i; z2[j] != '0'; j++)
            {
                z1[j + 1] = z1[j + 2];
                z2[j] = z2[j + 1];
            }
        }
        else
            i++; /*--------------*/
    }
    for (i = 0; z2[i] != '0';)
    {
        if (z2[i] == '-') /*------perform subtraction------*/
        {
            z1[i] -= z1[i + 1];
            for (j = i; z2[j] != '0'; j++)
            {
                z1[j + 1] = z1[j + 2];
                z2[j] = z2[j + 1];
            }
        }
        else
            i++;
    }                 /*--------------*/
    if (z2[1] == 'r') /*------find yth roots------*/
        z1[0] = pow(z1[2], 1 / z1[0]);
    if (z2[1] == 'p') /*------find yth power------*/
        z1[0] = pow(z1[2], z1[0]);
    if (z2[1] == 'h') /*------find hypotenuse------*/
        z1[0] = hypot(z1[2], z1[0]);
    gcvt(z1[0], 15, ch); /*------copy result to array----------*/
    setcolor(DARKGRAY);
    outtextxy(35, 60, ch); //display result
    press();
    return 0;
}

/*-------perform numeric system calculations--------*/

double ns(long double b, int y)
{
    int y1;
    long n;
    n = b;
    if (y > 100 && y < 140) // AC function
    {
        box(550, 100, 55, BLACK, WHITE);
        delay(200);
        box(550, 100, 55, WHITE, BLACK);
        18 return 0;
    }
    if (y > 160 && y < 200) // HEX function
    {
        box(550, 160, 55, BLACK, WHITE);
        delay(200);
        box(550, 160, 55, WHITE, BLACK);
        com(n, 16);
    }
    if (y > 220 && y < 260) // BINARY function
    {
        box(550, 220, 55, BLACK, WHITE);
        delay(200);
        box(550, 220, 55, WHITE, BLACK);
        com(n, 2);
    }
    if (y > 280 && y < 320) //OCTAL function
    {
        box(550, 280, 55, BLACK, WHITE);
        delay(200);
        box(550, 280, 55, WHITE, BLACK);
        com(n, 8);
    }
    return 0;
} /*---------common for HEX, BINARY & OCTAL-------------*/
long com(long b, int k)
{
    char *str;
    int i = 0;
    itoa(b, str, k); // integer to array
    if (k == 16)
    {
        while (str[i] != '0')
        {
            if (str[i] > 96 && str[i] < 103)
                str[i] -= 32;
            i++;
        }
    }
    setcolor(DARKGRAY);
    outtextxy(35, 60, str);
    press();
    return 0;
}

/*Program to find roots of a Quad. Eqn. */

roots()
{
    float a, b, c, disc, r1, r2, s, x, y;
    int k = 253;
    closegraph();
    19 restorecrtmode();
    printf("Input values of a, b, c in ax%c+bx+cn ", k);
    scanf("%f%f%f", &a, &b, &c);
    disc = b * b - 4 * a * c;
    if (disc < 0)
    {
        printf("n roots are IMAGINERY n");
        s = -disc;
        x = sqrt(s) / (2 * a);
        y = -b / (2 * a);
        printf("n r1=%f+i%f", y, x);
        printf("n r2=%f-i%f", y, x);
    }
    else
    {
        r1 = (-b + sqrt(disc)) / (2.0 * a);
        r2 = (-b - sqrt(disc)) / (2.0 * a);
        printf("n r1=%f n r2=%f n", r1, r2);
    }
    getch();
    return;
}

/*---------------BUTTONS------------------------*/

int box(int x1, int y1, int l, int c1, int c2)
{
    setcolor(c1);
    setfillstyle(1, LIGHTGRAY);
    rectangle(x1, y1, x1 + l, y1 + 40);
    floodfill(x1 + 3, y1 + 10, c1);
    setcolor(c2);
    line(x1 + l, y1, x1 + l, y1 + 40);
    line(x1, y1 + 40, x1 + l, y1 + 40);
    return 0;
}

/*password at start screen*/

password()
{
    int i, x = 270, gm, gd = DETECT;
    char ch, pass[10];
    initgraph(&gd, &gm, "c:tcbgi");
    rectangle(15, 15, 615, 465);
    setcolor(LIGHTBLUE);
    setfillstyle(1, LIGHTBLUE);
    floodfill(50, 50, 15);
    settextstyle(1, HORIZ_DIR, 3);
    setcolor(BLACK);
    outtextxy(200, 50, "Enter the password");
    for (i = 0; i <= 10; i++, x += 10)
    {
        ch = getch();
        if (ch == 13)
            20 break;
        outtextxy(x, 150, "*");
        sound(300);
        delay(50);
        nosound();
        pass[i] = ch;
    }
    pass[i] = '0';
    if (!strcmp(pass, "as")) //compare entered string with password
        return 0;
    else
        cleardevice();
    rectangle(15, 15, 615, 465);
    setcolor(LIGHTBLUE);
    setfillstyle(1, LIGHTBLUE);
    floodfill(50, 50, 15);
    settextstyle(1, HORIZ_DIR, 3);
    setcolor(RED);
    outtextxy(220, 50, "Wrong Password");
    outtextxy(80, 150, "This program will terminate in 5 seconds");
    for (i = 5; i >= 0; i--)
    {
        setcolor(LIGHTBLUE);
        setfillstyle(1, LIGHTBLUE);
        bar(300, 240, 330, 300);
        setcolor(RED);
        outtextxy(310, 250, itoa(i, pass, 10));
        sound(1000 * i + 500);
        delay(300);
        nosound();
        delay(700);
    }
    exit(0);
    return 0;
}

/*-----------solving scientific functions------------*/
//---the no. entered is in RADIANS
/*-----------check for first column------------------*/

colm1(long double a, int y)
{
    double cal;
    char *str;
    z1[2] = a;
    setcolor(WHITE);
    setfillstyle(1, WHITE);
    bar(30, 55, 610, 70);
    if (y >= 100 && y <= 140) // SINE of entered no.
    {
        box(xy1[0], 100, 70, BLACK, WHITE);
        delay(200);
        box(xy1[0], 100, 70, WHITE, BLACK);
        21 cal = sin(a);
    }
    if (y >= 160 && y <= 200) // HYPERBOLIC SINE of entered no.
    {
        box(xy1[0], 160, 70, BLACK, WHITE);
        delay(200);
        box(xy1[0], 160, 70, WHITE, BLACK);
        cal = sinh(a);
    }
    if (y >= 220 && y <= 260) // EXPONENTIAL of entered no.
    {
        box(xy1[0], 220, 70, BLACK, WHITE);
        delay(200);
        box(xy1[0], 220, 70, WHITE, BLACK);
        cal = exp(a);
    }
    if (y >= 280 && y <= 320) // Yth ROOT of entered no.
    {
        box(xy1[0], 280, 70, BLACK, WHITE);
        delay(200);
        box(xy1[0], 280, 70, WHITE, BLACK);
        z2[1] = 'r';
        return 0;
    }
    if (y >= 340 && y <= 380) // Yth POWER of entered no.
    {
        box(xy1[0], 340, 70, BLACK, WHITE);
        delay(200);
        box(xy1[0], 340, 70, WHITE, BLACK);
        z2[1] = 'p';
        return 0;
    }
    if (y >= 400 && y <= 440) // HYPOTENUSE of entered no.
    {
        box(xy1[0], 400, 70, BLACK, WHITE);
        delay(200);
        box(xy1[0], 400, 70, WHITE, BLACK);
        z2[1] = 'h';
        return 0;
    }
    setcolor(DARKGRAY);
    gcvt(cal, 10, str);
    outtextxy(35, 60, str);
    press();
    return (0);
}

/*-----------check for second column------------------*/

colm2(long double a, int y)
{
    double cal;
    int i;
    char *str;
    22 setcolor(WHITE);
    setfillstyle(1, WHITE);
    bar(30, 55, 610, 70);
    if (y >= 100 && y <= 140) // COSINE of entered no.
    {
        box(xy1[1], 100, 70, BLACK, WHITE);
        delay(200);
        box(xy1[1], 100, 70, WHITE, BLACK);
        cal = cos(a);
    }
    if (y >= 160 && y <= 200) // HYPERBOLIC COSINE of entered no.
    {
        box(xy1[1], 160, 70, BLACK, WHITE);
        delay(200);
        box(xy1[1], 160, 70, WHITE, BLACK);
        cal = cosh(a);
    }
    if (y >= 220 && y <= 260) // NATURAL LOG of entered no.
    {
        box(xy1[1], 220, 70, BLACK, WHITE);
        delay(200);
        box(xy1[1], 220, 70, WHITE, BLACK);
        cal = log(a);
    }
    if (y >= 280 && y <= 320) // INVERSE of entered no.
    {
        box(xy1[1], 280, 70, BLACK, WHITE);
        delay(200);
        box(xy1[1], 280, 70, WHITE, BLACK);
        cal = 1 / a;
    }
    if (y >= 340 && y <= 380) // SQRT of entered no.
    {
        box(xy1[1], 340, 70, BLACK, WHITE);
        delay(200);
        box(xy1[1], 340, 70, WHITE, BLACK);
        cal = sqrt(a);
    }
    if (y >= 400 && y <= 440) // QUADRATIC EQN.
    {
        box(xy1[1], 400, 70, BLACK, WHITE);
        delay(200);
        box(xy1[1], 400, 70, WHITE, BLACK);
        roots();
        draw();
        return 0;
    }
    setcolor(DARKGRAY);
    gcvt(cal, 10, str);
    outtextxy(35, 60, str);
    press();
    return 0;
}

/*-----------check for third column------------------*/
colm3(long double a, int y)

{
    double cal;
    char *str;
    setcolor(WHITE);
    setfillstyle(1, WHITE);
    bar(30, 55, 610, 70);
    if (y >= 100 && y <= 140) // TANGENT of entered no.
    {
        box(xy1[2], 100, 70, BLACK, WHITE);
        delay(200);
        box(xy1[2], 100, 70, WHITE, BLACK);
        cal = tan(a);
    }
    if (y >= 160 && y <= 200) //HYPERBOLIC TANGENT of entered no.
    {
        box(xy1[2], 160, 70, BLACK, WHITE);
        delay(200);
        box(xy1[2], 160, 70, WHITE, BLACK);
        cal = tanh(a);
    }
    if (y >= 220 && y <= 260) // LOG TO THE BASE 10 of entered no.
    {
        box(xy1[2], 220, 70, BLACK, WHITE);
        delay(200);
        box(xy1[2], 220, 70, WHITE, BLACK);
        cal = log10(a);
    }
    if (y >= 280 && y <= 320) // SQUARE of entered no.
    {
        box(xy1[2], 280, 70, BLACK, WHITE);
        delay(200);
        box(xy1[2], 280, 70, WHITE, BLACK);
        cal = pow(a, 2);
    }
    if (y >= 340 && y <= 380) // FACTORIAL of entered no.
    {
        box(xy1[2], 340, 70, BLACK, WHITE);
        delay(200);
        box(xy1[2], 340, 70, WHITE, BLACK);
        cal = 1;
        for (; a >= 1; a--)
            cal = cal * a;
    }
    if (y >= 400 && y <= 440) // conversion of DEGREES to RADIANS
    {
        box(xy1[2], 400, 70, BLACK, WHITE);
        delay(200);
        box(xy1[2], 400, 70, WHITE, BLACK);
        cal = (180 * a) / pi;
    }
    setcolor(DARKGRAY);
    gcvt(cal, 10, str);
    outtextxy(35, 60, str);
    24 press();
    return (0);
}

//Changing the blue rectangle contents

press()
{
    int x;
    x = getmaxx();
    setcolor(BLACK);
    setfillstyle(1, RED);
    bar(21, 20, x - 21, 40);
    floodfill(25, 25, BLACK); /* blue rectangle*/
    setcolor(WHITE);
    outtextxy(x - 250, 27, "Press Any Key To Continue"); /*---Continue---*/
    getch();
    setcolor(LIGHTGRAY);
    setfillstyle(1, WHITE);
    floodfill(32, 59, LIGHTGRAY);
    setcolor(BLACK);
    setfillstyle(1, BLUE);
    rectangle(21, 20, x - 21, 40);
    floodfill(25, 25, BLACK); /* blue rectangle*/
    setcolor(WHITE);
    outtextxy(x - 220, 27, "Press Any Key To Quit."); /*---Quit---*/
}

/*-----------------------END--------------------------------------*/