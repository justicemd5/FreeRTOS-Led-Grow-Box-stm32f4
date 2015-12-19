/*
 * bitwise_operations.h
 *
 *  Created on: 11.9.2014
 *      Author: Almir
 */

#ifndef BITWISE_OPERATIONS_H_
#define BITWISE_OPERATIONS_H_

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(VARIABLE, SHIFT) 	((VARIABLE) |= (1 << (SHIFT)))
#define BIT_CLEAR(VARIABLE, SHIFT) 	((VARIABLE) &= ~(1 << (SHIFT)))
#define BIT_TOGGLE(VARIABLE, SHIFT) ((VARIABLE) ^= (1 << (SHIFT)))
#define BIT_CHECK(VARIABLE, SHIFT) 	((VARIABLE) & (1 << (SHIFT)))

/* x=target variable, y=mask */
#define BITMASK_SET(VARIABLE, MASK) 	((VARIABLE) |= (MASK))
#define BITMASK_CLEAR(VARIABLE, MASK) 	((VARIABLE) &= (~(MASK)))
#define BITMASK_TOGGLE(VARIABLE, MASK) 	((VARIABLE) ^= (MASK))
#define BITMASK_CHECK(VARIABLE, MASK) 	((VARIABLE) & (MASK))

#endif /* BITWISE_OPERATIONS_H_ */
