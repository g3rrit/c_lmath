#include "lmath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void l_uint_init(struct l_uint *num, int size)
{
    num->data = calloc(1,size);
    num->size = size;
}

void l_uint_delete(struct l_uint *num)
{
    if(num->data)
        free(num->data);
    num->size = 0;
}

int l_uint_add8_at(struct l_uint *res, int at, uint8_t add)
{
    if(res->size - at < 0)
        return 0;

    int count = 0;
    uint16_t overflow = 0;
    do
    {
        if(res->data[count + at] + add > UINT8_MAX)
            overflow = 1;
        else
            overflow = 0;
        res->data[count + at] += add;
        add = overflow;
        count++;
    } while(count < res->size - at - 1 && overflow);

    return 1;
}

int l_uint_add8(struct l_uint *res, uint8_t add)
{
    if(res->size < 0)
        return 0;

    int count = 0;
    uint16_t overflow = 0;
    do
    {
        if(res->data[count] + add > UINT8_MAX)
            overflow = 1;
        else
            overflow = 0;
        res->data[count] += add;
        add = overflow;
        count++;
    } while(count < res->size -1 && overflow);

    return 1;
}

int l_uint_add16(struct l_uint *res, uint16_t add)
{
    if(1 < res->size)
        l_uint_add8_at(res, 0, ((uint8_t*)(&add))[0]);
    if(2 < res->size)
        l_uint_add8_at(res, 1, ((uint8_t*)(&add))[1]);

    return 1;
}

int l_uint_add32(struct l_uint *res, uint32_t add)
{
    if(1 < res->size)
        l_uint_add8_at(res, 0, ((uint8_t*)(&add))[0]);
    if(2 < res->size)
        l_uint_add8_at(res, 1, ((uint8_t*)(&add))[1]);
    if(3 < res->size)
        l_uint_add8_at(res, 2, ((uint8_t*)(&add))[2]);
    if(4 < res->size)
        l_uint_add8_at(res, 3, ((uint8_t*)(&add))[3]);

    return 1;
}

int l_uint_add(struct l_uint *res, struct l_uint *add1, struct l_uint *add2)
{
    for(int i = 0; (i < add1->size || i < add2->size) && i < res->size; i++)
    {
        if(i < add1->size)
            l_uint_add8_at(res, i, add1->data[i]);
        if(i < add2->size)
            l_uint_add8_at(res, i, add2->data[i]);
    }

    return 1;
}

int l_uint_mult(struct l_uint *res, struct l_uint *mult1, struct l_uint *mult2)
{
    uint16_t buf = 0;
    for(int i = 0; i < mult1->size; i++)
    {
        for(int n = 0; n < mult2->size; n++)
        {
            buf = (uint16_t)mult1->data[i] * (uint16_t)mult2->data[n];
            if(i + n < res->size)
                l_uint_add8_at(res, n + i, ((uint8_t*)(&buf))[0]);
            if(i + n + 1 < res->size)
                l_uint_add8_at(res, n + i + 1, ((uint8_t*)(&buf))[1]);
        }
    }

    return 1;
}


int l_uint_toa(char *res, struct l_uint *num)
{
    //TODO implement
    return 1;
}


int l_uint_print(struct l_uint *num)
{
    printf("number - size: %i ->\n", num->size);
    for(int i = num->size - 1; i >= 0; i--)
    {
        for(int b = 0; b < 8; b++)
            printf("%d", !!((num->data[i] << b) & 0x80));
        printf(" ");
        //if(!(i % 8))
        //    printf("\n");
    }
    printf("\n");
    return 1;
}

