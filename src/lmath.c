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

//------ADDITION-----

int l_uint_add8_at(struct l_uint *res, int at, uint8_t add)
{
    if(res->size - at < 0)
        return 0;

    int count = 0;
    int overflow = 0;
    do
    {
        if(res->data[count + at] + add > UINT8_MAX)
            overflow = 1;
        else
            overflow = 0;
        res->data[count + at] += add;
        add = (uint8_t)overflow;
        count++;
    } while(count < res->size - at - 1 && overflow);

    return overflow;
}

int l_uint_add8(struct l_uint *res, uint8_t add)
{
    return l_uint_add8_at(res, 0, add);
}

int l_uint_add16(struct l_uint *res, uint16_t add)
{
    int overflow = 0;
    if(1 < res->size)
        overflow += l_uint_add8_at(res, 0, ((uint8_t*)(&add))[0]);
    if(2 < res->size)
        overflow +=l_uint_add8_at(res, 1, ((uint8_t*)(&add))[1]);

    return overflow;
}

int l_uint_add32(struct l_uint *res, uint32_t add)
{
    int overflow = 0;
    if(1 < res->size)
        overflow += l_uint_add8_at(res, 0, ((uint8_t*)(&add))[0]);
    if(2 < res->size)
        overflow += l_uint_add8_at(res, 1, ((uint8_t*)(&add))[1]);
    if(3 < res->size)
        overflow += l_uint_add8_at(res, 2, ((uint8_t*)(&add))[2]);
    if(4 < res->size)
        overflow += l_uint_add8_at(res, 3, ((uint8_t*)(&add))[3]);

    return overflow;
}

int l_uint_add(struct l_uint *res, struct l_uint *add)
{
    int overflow = 0;
    for(int i = 0; i < add->size && i < res->size; i++)
    {
        if(i < add->size)
            overflow += l_uint_add8_at(res, i, add->data[i]);
    }

    return overflow;
}

//------SUBTRACTION------

int l_uint_sub8_at(struct l_uint *res, int at, uint8_t sub)
{
    if(res->size - at < 0)
        return 0;

    int count = 0;
    int overflow = 0;
    do
    {
        if(res->data[count + at] < sub)
            overflow = 1;
        else
            overflow = 0;
        res->data[count + at] -= sub;
        sub = (uint8_t)overflow;
        count++;
    } while(count < res->size - at - 1 && overflow);

    return overflow;
}

int l_uint_sub8(struct l_uint *res, uint8_t sub)
{
    return l_uint_sub8_at(res, 0, sub);
}

int l_uint_sub16(struct l_uint *res, uint16_t sub)
{
    int overflow = 0;
    if(1 < res->size)
        overflow += l_uint_sub8_at(res, 0, ((uint8_t*)(&sub))[0]);
    if(2 < res->size)
        overflow += l_uint_sub8_at(res, 1, ((uint8_t*)(&sub))[1]);

    return overflow;
}

int l_uint_sub32(struct l_uint *res, uint32_t sub)
{
    int overflow = 0;
    if(1 < res->size)
        overflow += l_uint_sub8_at(res, 0, ((uint8_t*)(&sub))[0]);
    if(2 < res->size)
        overflow += l_uint_sub8_at(res, 1, ((uint8_t*)(&sub))[1]);
    if(3 < res->size)
        overflow += l_uint_sub8_at(res, 2, ((uint8_t*)(&sub))[2]);
    if(4 < res->size)
        overflow += l_uint_sub8_at(res, 3, ((uint8_t*)(&sub))[3]);

    return overflow;
}

int l_uint_sub(struct l_uint *res, struct l_uint *sub)
{
    int overflow = 0;
    for(int i = 0; i < sub->size && i < res->size; i++)
    {
        overflow += l_uint_sub8_at(res, i, sub->data[i]);
    }

    return overflow;
}


int l_uint_sub_at(struct l_uint *res, struct l_uint *sub, int at)
{
    int overflow = 0;
    for(int i = 0; i < sub->size && i + at < res->size; i++)
    {
        overflow += l_uint_sub8_at(res, i + at, sub->data[i]);
    }

    return overflow;
}

//------MULTIPLICATION------

int l_uint_mult(struct l_uint *res, struct l_uint *mult)
{
    struct l_uint mult2;
    l_uint_init(&mult2, res->size);
    l_uint_add(&mult2, res);

    int overflow = 0;
    uint16_t buf = 0;
    for(int i = 0; i < mult->size; i++)
    {
        for(int n = 0; n < mult2.size; n++)
        {
            buf = (uint16_t)mult->data[i] * (uint16_t)mult2.data[n];
            if(i + n < res->size)
                overflow += l_uint_add8_at(res, n + i, ((uint8_t*)(&buf))[0]);
            if(i + n + 1 < res->size)
                overflow += l_uint_add8_at(res, n + i + 1, ((uint8_t*)(&buf))[1]);
        }
    }
    l_uint_delete(res);

    return overflow;
}

//-----DIVISION-----

int l_uint_div(struct l_uint *res, struct l_uint *div)
{
    struct l_uint div1;
    l_uint_init(&div1, res->size);
    l_uint_add(&div1, res);

    //TODO: implement
    return 0;
}


//-----MODULAR-DIVISION-----

int l_uint_mdiv(struct l_uint *res, struct l_uint *mod)
{
    int overflow = 0;
    int count = 0;
    for(int i = 0; i < res->size && i < mod->size && (res->data[i] != 0 || mod->data[i] != 0); i++)
        if(res->data[i] > 0 && mod->data[i] == 0)
            count++;

    for(int i = count; i >= 0; i--)
    {
        if(!l_uint_grt_at(mod, res, i))
        {
            overflow += l_uint_sub_at(res, mod, i);
        }
    }

    return overflow;
}

//-----COMPARISION-----

int l_uint_grt(struct l_uint *num1, struct l_uint *num2)
{
    int size = num1->size > num1->size ? num1->size : num2->size;

    for(int i = size; i >= 0; i--)
    {
        uint8_t n1 = num1->size <= i ? num1->data[i] : 0;
        uint8_t n2 = num2->size <= i ? num2->data[i] : 0;

        if(n1 > n2)
            return 1;
        else if(n1 < n2)
            return 0;
    }
    return 0;
}

int l_uint_grt_at(struct l_uint *num1, struct l_uint *num2, int at)
{
    int size = num1->size + at > num1->size ? num1->size + at : num2->size;

    for(int i = size; i >= at; i--)
    {
        uint8_t n1 = num1->size + at <= i ? num1->data[i - at] : 0;
        uint8_t n2 = num2->size <= i ? num2->data[i] : 0;

        if(n1 > n2)
            return 1;
        else if(n1 < n2)
            return 0;
    }
    return 0;
}

int l_uint_grt_eq(struct l_uint *num1, struct l_uint *num2)
{
    int size = num1->size > num1->size ? num1->size : num2->size;

    for(int i = size; i >= 0; i--)
    {
        uint8_t n1 = num1->size <= i ? num1->data[i] : 0;
        uint8_t n2 = num2->size <= i ? num2->data[i] : 0;

        if(n1 >= n2 && n1 != 0)
            return 1;
        else if(n1 < n2)
            return 0;
    }
    return 1;
}

int l_uint_grt_eq_at(struct l_uint *num1, struct l_uint *num2, int at)
{
    int size = num1->size + at > num1->size ? num1->size + at : num2->size;

    for(int i = size; i >= at; i--)
    {
        uint8_t n1 = num1->size + at <= i ? num1->data[i - at] : 0;
        uint8_t n2 = num2->size <= i ? num2->data[i] : 0;

        if(n1 >= n2 && n1 != 0)
            return 1;
        else if(n1 < n2)
            return 0;
    }
    return 1;
}



//etc

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

