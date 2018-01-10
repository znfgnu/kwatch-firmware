/*
 * pseudo_rand.c
 *
 *  Created on: 10 sty 2018
 *      Author: konrad
 */

#include "pseudo_rand.h"

static uint32_t seed;

void pseudo_rand_init(uint32_t newseed) {
	seed = newseed;
}
int pseudo_rand_get() {
	seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
	return seed;
}


