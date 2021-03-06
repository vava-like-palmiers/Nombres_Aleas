/*
 * e0.c
 *
 *  Created on: 21 mars 2017
 *      Author: perso
 */

#include "e0.h"

#include <stdio.h>
#include <assert.h>



const size_t TAILLE_1 = 25;
const size_t TAILLE_2 = 31;
const size_t TAILLE_3 = 33;
const size_t TAILLE_4 = 39;



bool get(byte_t * tab, size_t size, size_t i){

    //assert(i < size);
	const size_t caseTab = i / 8;
	const size_t decalage = i % 8;

	return (tab[caseTab] >> decalage) % 2;
}


/**
 * xxxx
 * and 0111 (masque inversé)
 * = 0xxx
 * or y000 (valeur placée)
 * = yxxx
 */
void set(byte_t * tab, size_t size, size_t i, bool val){

    //assert(i < size);
	const size_t caseTab = i / 8;
	const size_t decalage = i % 8;
	const byte_t masqueInverse = ~(1 << decalage);
	const byte_t valeurPlacee = val << decalage;

	tab[caseTab] = (tab[caseTab] & masqueInverse) | valeurPlacee;
}


void decalageLFSR(byte_t * tab, size_t size){
	bool bit;
	int i, lastval=0,firstval=0;
	for(i=0; i<size/8 + 1; i++){
        /*if(8*(i+1) < sd){
            set(tab, size, 8*(i+1), bit);
		}*/

		lastval=get(tab, size, (i*8)+7);
        printf("%d, %d\n", size, 8*i+7);
		tab[i] = tab[i] << 1;
		set(tab, size, 8*i, firstval);
		firstval=lastval;
	}
}


bool premierBit(bool bit1, bool bit2, bool bit3, bool bit4, bool bit5){
    return bit1 ^ bit2 ^ bit3 ^ bit4 ^ bit5;
}



void LFSR(byte_t *tab, size_t size, int bit1, int bit2, int bit3, int bit4, int bit5){
    int i;
    bool bit;
    tabToString(tab, size);
    //for(i=0; i<1; i++){
        bit = premierBit(get(tab, size, bit1),
                         get(tab, size, bit2),
                         get(tab, size, bit3),
                         get(tab, size, bit4),
                         get(tab, size, bit5));
        decalageLFSR(tab, size);
        set(tab, size, 0, bit);
        tabToString(tab, size);
    //}
}


void tabToString(byte_t * tab, size_t size){
    int i;
    printf("{");
    for(i=0; i<size; i++){
        printf(" %d ", get(tab, size, i));
    }
    printf("}\n");
}







void avancerLFSR(FSM * fsm){
    LFSR(fsm->LFSR1, TAILLE_1, 0, 7, 11, 19, 24);
    LFSR(fsm->LFSR2, TAILLE_2, 0, 11, 15, 23, 30);
    LFSR(fsm->LFSR3, TAILLE_3, 0, 3, 23, 27, 32);
    LFSR(fsm->LFSR4, TAILLE_4, 0, 3, 27, 35, 38);
}


byte_t yt(bool x1, bool x2, bool x3, bool x4, bool ct){
    return (x1 + x2 + x3 + x4 + ct) % (1<<3);
}

byte_t ct(bool c0, bool c1){
    return ((c1 << 1) + c0) % (1 << 2);
}

bool c1t(bool s1t, bool c1tm1, bool c0tm2){
    return s1t ^ c1tm1 ^ c0tm2;
}

bool c0t(bool s0t, bool c0tm1, bool c1tm2, bool c0tm2){
    return s0t ^ c0tm1 ^ c1tm2 ^ c0tm2;
}

byte_t s(byte_t ytm1){
    return ytm1 >> 1;
}



void majFSM(FSM * fsm){
    byte_t s = 0; //TODO

    byte_t c0t_v = c0t(
                     get(&s, 2, 0),
                     get(&fsm->ct, 4, 2),
                     get(&fsm->ct, 4, 1),
                     get(&fsm->ct, 4, 0)
                     );
    byte_t c1t_v = c1t(
                     get(&s, 2, 1),
                     get(&fsm->ct, 4, 3),
                     get(&fsm->ct, 4, 0)
                     );

    byte_t ctp1 = ct(
                     c0t_v,
                     c1t_v
                     );

    byte_t ytp1 = yt(
              get(fsm->LFSR1, TAILLE_1, 22),
              get(fsm->LFSR2, TAILLE_2, 22),
              get(fsm->LFSR3, TAILLE_3, 30),
              get(fsm->LFSR4, TAILLE_4, 36),
              ctp1
              );
}



