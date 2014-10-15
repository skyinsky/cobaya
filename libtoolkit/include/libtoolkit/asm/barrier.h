#ifndef _LIBTOOLKIT_ASM_BARRIER_H
#define _LIBTOOLKIT_ASM_BARRIER_H

#include <libtoolkit/asm/config.h>

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

#ifdef CONFIG_SMP
#define smp_mb()	mb()
#ifdef CONFIG_X86_PPRO_FENCE
# define smp_rmb()	rmb()
#else
# define smp_rmb()	barrier()
#endif
#ifdef CONFIG_X86_OOSTORE
# define smp_wmb() 	wmb()
#else
# define smp_wmb()	barrier()
#endif
#else
#define smp_mb()	barrier()
#define smp_rmb()	barrier()
#define smp_wmb()	barrier()
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_ASM_BARRIER_H */
