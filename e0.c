/*
 * e0.c
 *
 *  Created on: 21 mars 2017
 *      Author: perso
 */

#include "e0.h"


bool get(byte_t * tab, size_t size, size_t i){
	const size_t caseTab = i / 8;
	const size_t decalage = i % 8;

	return (tab[caseTab] >> decalage) % 2;
}


void set(byte_t * tab, size_t size, size_t i, bool val){
	const size_t caseTab = i / 8;
	const size_t decalage = i % 8;
	const byte_t masque = (val ? 1 : 0) << decalage;
	const byte_t normalise = tab[caseTab] & (255 & (0 << decalage));

	tab[caseTab] = normalise | masque;
}

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
