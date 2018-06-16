#ifndef LMATH_H
#define LMATH_H

#include <stdint.h>

struct l_uint
{
    uint8_t *data;
    uint8_t size;
};

void l_uint_init(struct l_uint *num, int size);

void l_uint_delete(struct l_uint *num);

int l_uint_add8_at(struct l_uint *res, int at, uint8_t add);

int l_uint_add8(struct l_uint *res, uint8_t add);

int l_uint_add16(struct l_uint *res, uint16_t add);

int l_uint_add32(struct l_uint *res, uint32_t add);

int l_uint_add(struct l_uint *res, struct l_uint *add1, struct l_uint *add2);

int l_uint_mult(struct l_uint *res, struct l_uint *mult1, struct l_uint *mult2);

int l_uint_toa(char *res, struct l_uint *num);

int l_uint_print(struct l_uint *num);

#endif

