/*
 * pseudo_rand.h
 *
 *  Created on: 10 sty 2018
 *      Author: konrad
 */

#ifndef PSEUDO_RAND_H_
#define PSEUDO_RAND_H_

#include <stdint.h>

void pseudo_rand_init(uint32_t);
int pseudo_rand_get();

#endif /* PSEUDO_RAND_H_ */
