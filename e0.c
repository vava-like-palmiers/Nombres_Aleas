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
    assert(i < size);
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
    assert(i < size);
	const size_t caseTab = i / 8;
	const size_t decalage = i % 8;
	const byte_t masqueInverse = ~(1 << decalage);
	const byte_t valeurPlacee = val << decalage;

	tab[caseTab] = (tab[caseTab] & masqueInverse) | valeurPlacee;
}

<<<<<<< HEAD
void decalageLFSR(byte_t * tab, size_t size){
	bool bit;
	int i;
	for(i=0; i<size; i++){
		bit = get(tab, size, 8*i+7);
		tab[i] = tab[i] >> 1;
		if(i != 0){
			set(tab, size, 8*i, bit);
		}
	}
}

bool premierBit(bool bit1, bool bit2, bool bit3, bool bit4){
    return bitASet = bit1 ^ bit2 ^ bit3 ^ bit4;
=======

>>>>>>> a8273b63e1ead85d50cc73849900fc0a459a7d8d
}

void LFSR(size_t size, bool bit1, bool bit2, bool bit3, bool bit4){
    int tab[size/8+1];
    int i;
    bool bit;
    tabToString(tab, size);
    for(int=0; i<5; i++){
        bit = premierBit(bit1, bit2, bit3, bit4);
        decalageLFSR(tab, size);
        set(tab, size, 0, bit);
        tabToString(tab, size);
    }
}

void tabToString(byte_t * tab, size_t size){
    int i;
    printf{"{"};
    for(i=0; i<size; i++){
        printf(" %d ", get(tab, size, i));
    }
    printf{"}\n"};
}
