#ifndef _LIBTOOLKIT_ASM_BARRIER_H
#define _LIBTOOLKIT_ASM_BARRIER_H

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_SMP
#define LOCK_PREFIX	"lock ; "
#else
#define LOCK_PREFIX
#endif

/**
 * General memory barrier.
 *
 * Guarantees that the LOAD and STORE operations generated before the
 * barrier occur before the LOAD and STORE operations generated after.
 */
#ifdef __x86_64__
#define mb()	asm volatile("mfence":::"memory")
#else
#define	mb()	_mm_mfence()
#endif

/**
 * Write memory barrier.
 *
 * Guarantees that the STORE operations generated before the barrier
 * occur before the STORE operations generated after.
 */
#ifdef __x86_64__
#define wmb()	asm volatile("sfence" ::: "memory")
#else
#define	wmb()	_mm_sfence()
#endif

/**
 * Read memory barrier.
 *
 * Guarantees that the LOAD operations generated before the barrier
 * occur before the LOAD operations generated after.
 */
#ifdef __x86_64__
#define rmb()	asm volatile("lfence":::"memory")
#else
#define	rmb()	_mm_lfence()
#endif

/**
 * Compiler barrier.
 *
 * Guarantees that operation reordering does not occur at compile time
 * for operations directly before and after the barrier.
 */
#define	barrier()					\
	do {						\
		asm volatile ("" : : : "memory");	\
	} while(0)

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_ASM_BARRIER_H */
