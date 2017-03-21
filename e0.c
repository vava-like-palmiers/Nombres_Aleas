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


