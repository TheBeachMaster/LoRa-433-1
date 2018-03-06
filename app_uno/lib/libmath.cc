#include "libmath.h"

int LibMath::add(int a, int b)
{
    return (a + b);
}

int LibMath::sub(int a, int b)
{
    if(a > b)
    {
       return (a - b); 
    }
    else
    {
        return 0;
    }
}

int LibMath::div(int a , int b)
{
    if(a == 0 || b == 0)
    {
        return 0;
    }
    if(a < b)
    {
        return 0;
    }
    if(a > b)
    {
        return (a / b);
    }

}

int LibMath::mult(int a, int b )
{
    return (a * b);
}

int LibMath::sqr(int a)
{
    // TODO -- Check -ve Numbers
    return (a * a);
}