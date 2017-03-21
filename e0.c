/*
 * e0.c
 *
 *  Created on: 21 mars 2017
 *      Author: perso
 */

#include "e0.h"

#include <stdio.h>
#include <assert.h>


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

bool premierBit(bool bit1, bool bit2, bool bit3, bool bit4){
    return bit1 ^ bit2 ^ bit3 ^ bit4;
}

void LFSR(size_t size, int bit1, int bit2, int bit3, int bit4){
    byte_t tab[4];
    /*tab[0] = 128;
    tab[1] = 0;
    tab[2] = 0;*/
    tab[3] = 222;
    int i;
    bool bit;
    tabToString(tab, size);
    //for(i=0; i<1; i++){
        bit = premierBit(get(tab, size, bit1),
                         get(tab, size, bit2),
                         get(tab, size, bit3),
                         get(tab, size, bit4));
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
