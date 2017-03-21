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

#endif /* CODE_E0_H_ */
