#include <stdio.h>
#include <stdlib.h>

#include "lmath.h"

#include <stdint.h>

int main()
{
    struct l_uint num1;
    struct l_uint num2;
    struct l_uint num3;
    struct l_uint num4;

    l_uint_init(&num1, 4);
    l_uint_init(&num2, 4);
    l_uint_init(&num3, 16);
    l_uint_init(&num4, 16);

    l_uint_add32(&num1, 23454);
    l_uint_add32(&num2, 6432123);

    l_uint_add(&num3, &num1, &num2);

    l_uint_mult(&num4, &num1, &num2);

    l_uint_print(&num1);
    l_uint_print(&num2);
    l_uint_print(&num3);
    l_uint_print(&num4);

    return 0;
}
