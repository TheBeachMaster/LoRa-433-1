#include "libmath.h"
#include "BDDTest.h"
#include "trace.h"

int test_addition()
{
    IT("Performs Addition Operation");
    LibMath math_ops;
    int a = 5;
    int b = 40;
    int expect = 45;
    int res = math_ops.add(a, b);
    IS_EQUAL(res , expect);
    END_IT
}

int test_subtraction()
{
    IT("Performs Subtraction  Operation");
    LibMath math_ops;
    int a = 40;
    int b = 30;
    int expect = 10;
    int res = math_ops.sub(a, b);
    IS_EQUAL(res , expect);
    END_IT
}

int test_division()
{
    IT("Performs Divison Operation");
    LibMath math_ops;
    int a = 100;
    int b = 4;
    int expect = 25;
    int res = math_ops.div(a, b);
    IS_EQUAL(res , expect);
    END_IT
}

int test_square()
{
    IT("Performs Square Operation");
    LibMath math_ops;
    int a = 5;
    int expect = 25;
    int res = math_ops.sqr(a);
    IS_EQUAL(res , expect);
    END_IT
}

int test_improper_subtraction()
{
    IT("Returns 0 if subtrahend is greater than subtractor");
    LibMath math_ops;
    int a = 20;
    int b = 70;
    int expect = 0;
    int res = math_ops.sub(a, b);
    IS_EQUAL(res , expect);
    END_IT
}

int test_return_0_on_0_division()
{
    IT("Always Return 0 if any of the arguments is 0");
    LibMath math_ops;
    int a = 0;
    int b = 50;
    int expect = 0;
    int res = math_ops.div(a, b);
    IS_EQUAL(res , expect);
    END_IT
}

int test_allow_negative_numbers_multiplication()
{
    IT("Allows -ve arguments on multiplication");
    LibMath math_ops;
    int a = -4;
    int b = -8;
    int expect = 32;
    int res = math_ops.mult(a, b);
    IS_EQUAL(res , expect);
    END_IT
}

int main()
{
    SUITE("Math Operations");
    test_addition();
    test_subtraction();
    test_division();
    test_square();
    test_improper_subtraction();
    test_return_0_on_0_division();
    test_allow_negative_numbers_multiplication();
    FINISH
}