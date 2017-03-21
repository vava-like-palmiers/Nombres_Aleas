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
    assert(i >= 0 && i < size);
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
    assert(i >= 0 && i < size);
	const size_t caseTab = i / 8;
	const size_t decalage = i % 8;
	const byte_t masqueInverse = ~(1 << decalage);
	const byte_t valeurPlacee = val << decalage;


	tab[caseTab] = (tab[caseTab] & masqueInverse) | valeurPlacee;
}

