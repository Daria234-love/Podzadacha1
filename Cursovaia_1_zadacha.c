#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

double Y(double x);
double V(double x);
void graph(double (*f)(double), double a, double b);

int main(void)
{
    setlocale(LC_ALL,"RUS");
    double a, b, h, x;
    double (*f)(double);
    int choice;

    printf("1 - Y(x)\n");
    printf("2 - V(x)\n");
    printf("Выберите функцию: ");

    if (scanf("%d", &choice) != 1)
        return 1;

    if (choice == 1)
        f = Y;
    else if (choice == 2)
        f = V;
    else
    {
        printf("Неверный выбор!\n");
        return 1;
    }

    printf("Введите начало интервала: ");
    if (scanf("%lf", &a) != 1)
        return 1;

    printf("Введите конец интервала: ");
    if (scanf("%lf", &b) != 1)
        return 1;

    printf("Введите шаг: ");
    if (scanf("%lf", &h) != 1)
        return 1;

    
    if (a >= b || h <= 0 || (choice == 1 && a <= 0))
    {
        printf("Неверные значения!\n");
        return 1;
    }

    printf("\n       x          y\n");

    for (x = a; x <= b + 1e-9; x += h)
        printf("%10.3lf   %10.5lf\n", x, f(x));

    printf("\nГрафик функции:\n");
    graph(f, a, b);

    return 0;
}


double Y(double x)
{
    if (x <= 0)
        return NAN;

    return exp((sin(x) * sin(x) /
        cbrt(0.2 * pow(x, 8))) * log(5.0 * x));
}


double V(double x)
{
    if (x <= 0)
        return (1.0 + x) / cbrt(1.0 + x * x);
    else if (x < 1)
        return 2.0 * exp(-2.0 * x);
    else
        return cbrt(fabs(2.0 - x));
}


void graph(double (*f)(double), double a, double b)
{
    char picture[21][61];
    double y[61], min, max, x;
    int i, j, row, col;

    for (i = 0; i < 61; i++)
    {
        x = a + (b - a) * i / 60.0;
        y[i] = f(x);
    }

    min = y[0];
    max = y[0];

    for (i = 1; i < 61; i++)
    {
        if (y[i] < min)
            min = y[i];

        if (y[i] > max)
            max = y[i];
    }

    for (i = 0; i < 21; i++)
        for (j = 0; j < 61; j++)
            picture[i][j] = ' ';

    if (min <= 0 && max >= 0 && max != min)
    {
        row = (int)(max / (max - min) * 20);

        if (row < 0)
            row = 0;
        if (row > 20)
            row = 20;

        for (j = 0; j < 61; j++)
            picture[row][j] = '-';
    }

    if (a <= 0 && b >= 0)
    {
        col = (int)((0 - a) / (b - a) * 60);

        if (col < 0)
            col = 0;
        if (col > 60)
            col = 60;

        for (i = 0; i < 21; i++)
            picture[i][col] = '|';
    }

    for (i = 0; i < 61; i++)
    {
        if (max == min)
            row = 10;
        else
            row = (int)((max - y[i]) / (max - min) * 20);

        if (row < 0)
            row = 0;
        if (row > 20)
            row = 20;

        picture[row][i] = '*';
    }

    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 61; j++)
            printf("%c", picture[i][j]);

        printf("\n");
    }
}