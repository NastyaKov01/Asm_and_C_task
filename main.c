#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int num = 0; /// количество итераций при поиске корня
int counter = 0; ///количество итераций при подсчете интеграла

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double f1_(double x);
extern double f2_(double x);
extern double f3_(double x);

double f4(double x)
{
    return 3 * x + 4;
}

double f5(double x)
{
    return x * x + 7 * x + 8;
}

double f6(double x)
{
    return x * x + 5 * x + 5;
}

double f4_(double x)
{
    return 3;
}

double f5_(double x)
{
    return 2 * x + 7;
}

double f6_(double x)
{
    return 2 * x + 5;
}

double root(double f(double), double g(double), double f_(double), double g_(double), double a, double b, double eps1)
{
    double x0;
    int m, u;
    num = 0;
    if(f(a) - g(a) < 0)
        m = 1;  ///m - показатель монотонности(1 - возрастает)
    else m = -1;
    if((f((a + b)/2) - g((a + b)/2)) > (f(a) - g(a) + f(b) - g(b))/2 )
        u = 1;  ///u - положение относительно хорды(1 - выше хорды)
    else u = -1;
    if(m * u == 1)
        x0 = a;
    else x0 = b;
    if(x0 == b) ///приближение справа
    {
        while((f(x0 - eps1) - g(x0 - eps1)) * (f(x0) - g(x0)) > 0)
        {
            x0 -= (f(x0) - g(x0))/(f_(x0) - g_(x0));
            num++;
        }
    }
    else ///приближение слева
    {
        while((f(x0 + eps1) - g(x0 + eps1)) * (f(x0) - g(x0)) > 0)
        {
            x0 -= (f(x0) - g(x0))/(f_(x0) - g_(x0));
            num++;
        }
    }
    return x0;
}


double integral(double f(double), double a, double b, double eps2)
{
    double h, prev = 0, integ, t;
    int i = 0, n = 5;
    counter = 0;
    h = (b - a)/n;
    integ = h * (0.5 * f(a) + 0.5 * f(b));
    while(fabs(prev - integ) >= 3 * eps2)
    {
        counter++;
        prev = integ; ///prev = In
        n *= 2;
        h /= 2;
        t = 0;///временная переменная для подсчета суммы значений в новых точках разбиения
        for(i = 1; i < n; i += 2)
        {
            t += f(a + i * h);
        }
        integ = integ / 2 + t * h; ///расчет нового значения интеграла(I2n)
    }
    return integ;
}

void test(void)
{
    int x, y, z;
    double a, b, eps;
    printf("Press 0 if you want to find the root of the equation, press 1 if you want to calculate the integral\n");
    scanf("%d", &x);
    if(x == 0)
    {
        printf("Enter the parameters(a, b, eps)\n");
        scanf("%lf%lf%lf", &a, &b, &eps);
        printf("Enter the numbers of functions you want to use\n");
        scanf("%d%d", &x, &y);
        printf("Press 1 if you want to get the number of iterations, press 0 if you don't\n");
        scanf("%d", &z);
        if((x == 4) && (y == 5))
        {
            printf("3x + 4 = x^2 + 7x + 8   x = %lf\n", root(f4, f5, f4_, f5_, a, b, eps));
            if(z)
                printf("Number of iterations: %d\n", num);
        }
        if((x == 5) && (y == 6))
        {
            printf("x^2 + 7x + 8 = x^2 + 5x + 5   x = %lf\n", root(f5, f6, f5_, f6_, a, b, eps));
            if(z)
                printf("Number of iterations: %d\n", num);
        }
        if((x == 4) && (y == 6))
        {
            printf("3x + 4 = x^2 + 5x + 5   x = %lf\n", root(f4, f6, f4_, f6_, a, b, eps));
            if(z)
                printf("Number of iterations: %d\n", num);
        }
    }
    else
    {
        printf("Enter the parameters(a, b, eps)\n");
        scanf("%lf%lf%lf", &a, &b, &eps);
        printf("Enter the number of function you want to use\n");
        scanf("%d", &x);
        printf("Press 1 if you want to get the number of iterations, press 0 if you don't\n");
        scanf("%d", &z);
        if(x == 4)
        {
            printf("Integral of 3*x + 4 = %lf\n", integral(f4, a, b, eps));
            if(z)
                printf("Number of iterations: %d\n", counter);
        }
        if(x == 5)
        {
            printf("Integral of x^2 + 7x + 8 = %lf\n", integral(f5, a, b, eps));
            if(z)
                printf("Number of iterations: %d\n", counter);
        }
        if(x == 6)
        {
            printf("Integral of x^2 + 5x + 5 = %lf\n", integral(f6, a, b, eps));
            if(z)
                printf("Number of iterations: %d\n", counter);
        }
    }
}

int main(int argc, char* argv[])
{
    double x1, x2, x3, res, prom1, prom2;
    int i, x, num1, num2, num3;
    x1 = root(f1, f3, f1_, f3_, 2.1, 4, 0.000025);
    num1 = num;
    x2 = root(f2, f3, f2_, f3_, 3, 7, 0.000025);
    num2 = num;
    x3 = root(f1, f2, f1_, f2_, 2.1, 7, 0.000025);
    num3 = num;
    if(argc == 1)
        printf("Enter -help to get the instructions\n");
    for(i = 1; i < argc; ++i)
    {
        if(!strcmp(argv[i], "-help")) ///вывод на печать всех доступных ключей
        {
            printf("The programm supports following functions:\n");
            printf("1. lnx   2. -2x + 14   3. 1/(2-x) + 6   4. 3x + 4   5. x^2 + 7x + 8     6. x^2 + 5x + 5\n");
            printf("You can use:\n");
            printf("    -test to test functions\n");
            printf("    -roots to get the crossing points\n");
            printf("    -square to get the square of the figure\n");
        }

        if(!strcmp(argv[i], "-test"))
        {
            test();
        }

        if(!strcmp(argv[i], "-roots"))
        {
            printf("Roots: x1 = %lf     x2 = %lf    x3 = %lf\n", x1, x2, x3);
            printf("Press 1 if you want to get the number of iterations, press 0 if you don't\n");
            scanf("%d", &x);
            if(x == 1)
                printf("Iter1 = %d  Iter2 = %d  Iter3 = %d\n", num1, num2, num3);
        }

        if(!strcmp(argv[i], "-square"))
        {
            prom1 = integral(f3, x1, x2, 0.000025);
            prom2 = integral(f2, x2, x3, 0.000025);
            res = prom1 + prom2;
            prom1 = integral(f1, x1, x3, 0.000025);
            res -= prom1;
            printf("Square: S = %f\n", res);
        }
    }
    return 0;
}
