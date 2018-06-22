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


//------ADDITION-----

int l_uint_add8_at(struct l_uint *res, int at, uint8_t add);

int l_uint_add8(struct l_uint *res, uint8_t add);

int l_uint_add16(struct l_uint *res, uint16_t add);

int l_uint_add32(struct l_uint *res, uint32_t add);

int l_uint_add(struct l_uint *res, struct l_uint *add);

//------SUBTRACTION-----

int l_uint_sub8_at(struct l_uint *res, int at, uint8_t sub);

int l_uint_sub8(struct l_uint *res, uint8_t sub);

int l_uint_sub16(struct l_uint *res, uint16_t sub);

int l_uint_sub32(struct l_uint *res, uint32_t sub);

int l_uint_sub(struct l_uint *res, struct l_uint *sub);

int l_uint_sub_at(struct l_uint *res, struct l_uint *sub, int at);

//------MULTIPLICATION------

int l_uint_mult(struct l_uint *res, struct l_uint *mult);

//-----DIVISION-----

int l_uint_div(struct l_uint *res, struct l_uint *div);

//-----MODULAR-DIVISION-----

int l_uint_mdiv(struct l_uint *res, struct l_uint *mod);

//-----COMPARISION-----

int l_uint_grt(struct l_uint *num1, struct l_uint *num2);

int l_uint_grt_at(struct l_uint *num1, struct l_uint *num2, int at);

int l_uint_grt_eq(struct l_uint *num1, struct l_uint *num2);

int l_uint_grt_eq_at(struct l_uint *num1, struct l_uint *num2, int at);

//etc

int l_uint_toa(char *res, struct l_uint *num);

int l_uint_print(struct l_uint *num);


#endif

