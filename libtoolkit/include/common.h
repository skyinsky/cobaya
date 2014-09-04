#ifndef _LIBTOOLKIT_COMMON_H
#define _LIBTOOLKIT_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

/**
 * Check if a branch is likely to be taken.
 *
 * This compiler builtin allows the developer to indicate
 * if a branch is likely to be taken. Example:
 *
 *   if (likely(x > 1))
 *      do_stuff();
 */
#ifndef likely
#define likely(x)  __builtin_expect((x),1)
#endif

/**
 * Check if a branch is unlikely to be taken.
 *
 * This compiler builtin allows the developer to indicate
 * if a branch is unlikely to be taken. Example:
 *
 *   if (unlikely(x < 1))
 *      do_stuff();
 */
#ifndef unlikely
#define unlikely(x)  __builtin_expect((x),0)
#endif

#ifdef __SSE2__
#include <emmintrin.h>
/**
 * PAUSE instruction for tight loops (avoid busy waiting)
 */
static inline void mm_pause (void)
{
	_mm_pause();
}
#else
static inline void mm_pause(void) { }
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_COMMON_H */
