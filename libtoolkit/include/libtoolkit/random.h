#ifndef _LIBTOOLKIT_RANDOM_H
#define _LIBTOOLKIT_RANDOM_H

/**
 * @file
 *
 * different sequence of real random 
 * for different threads 
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* one random byte */	
extern uint8_t random8();

/* two random bytes */
extern uint16_t random16();

/* four random bytes */
extern uint32_t random32();

/* eight random bytes */
extern uint64_t random64();

/* a random floating point number between start and end, inclusive */
extern double random_range_double(double start, double end);

/* a random integer between start and end, inclusive */
extern uint64_t random_range(uint64_t start, uint64_t end);

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_RANDOM_H */
