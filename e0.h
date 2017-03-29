/*
 * eo.h
 *
 *  Created on: 21 mars 2017
 *      Author: perso
 */

#ifndef CODE_E0_H_
#define CODE_E0_H_

#include <stdbool.h>
#include <stddef.h>


typedef unsigned char byte_t;


bool get(byte_t * tab, size_t size, size_t i);
void set(byte_t * tab, size_t size, size_t i, bool val);
bool premierBit(bool bit1, bool bit2, bool bit3, bool bit4, bool bit5);
void LFSR(byte_t *tab, size_t size, int bit1, int bit2, int bit3, int bit4, int bit5);
void tabToString(byte_t * tab, size_t size);
void decalageLFSR(byte_t * tab, size_t size);



struct FSM {
    byte_t LFSR1[25/8 + 1];
    byte_t LFSR2[31/8 + 1];
    byte_t LFSR3[33/8 + 1];
    byte_t LFSR4[39/8 + 1];

    byte_t ct;

    size_t taille;
};
typedef struct FSM FSM;

extern const size_t TAILLE_1;
extern const size_t TAILLE_2;
extern const size_t TAILLE_3;
extern const size_t TAILLE_4;



void avancerLFSR(FSM * fsm);


byte_t yt(bool x1, bool x2, bool x3, bool x4, bool ct);
byte_t ct(bool c0, bool c1);
bool c1t(bool s1t, bool c1tm1, bool c0tm2);
bool c0t(bool s0t, bool c0tm1, bool c1tm2, bool c0tm2);
byte_t s(byte_t ytm1);


void majFSM(FSM * fsm);


#endif /* CODE_E0_H_ */
