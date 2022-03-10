#include<stdio.h>
#include<math.h>


// Function to round - off(1) / Chop off(0)   the number
double Round_off(double N, double n, int choice)
{
    int h;
    double l, a, b, c, d, e, i, j, m, f, g, x;
    b = N;
    c = floor(N);
 
    // Counting the no. of digits to the left of decimal point
    // in the given no.
    for (i = 0; b >= 1; ++i)
        b = b / 10;
 
    d = n - i;
    b = N;
    b = b * pow(10, d);
    if (choice == 1)
    {
        e = b + 0.5;
        g = floor(b);
        x = floor(e);
        if ((int)g % 2 == 0 && e-x < 0.1f)
        {
            j = floor(g);
            m = pow(10, d);
            j = j / m;
            return j;
        }

        if ((double)e == (double)ceil(b)) 
        {
            f = (ceil(b));
            h = f - 2;
            if (h % 2 != 0)
                e = e - 1;
        }
        j = floor(e);
        m = pow(10, d);
        j = j / m;
        return j;
    }
    else
    {
        j = floor(b);
        m = pow(10, d);
        j = j / m;
        return j;
    }
}



int main()
{
    double x = 2.991071;
    double y = Round_off(x,5,1);
    double a = 15.25656;
    double b = Round_off(a,6,1);
    double t = 15.25656028;
    double w = Round_off(t,9,1);
    double q = 15.25646;
    double r = Round_off(q,5,1);
    printf("%lf",y);


    return 0;
}

