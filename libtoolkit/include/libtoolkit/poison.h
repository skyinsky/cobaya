#ifndef _LIBTOOLKIT_POISON_H
#define _LIBTOOLKIT_POISON_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __x86_64__
#define POISON_POINTER_DELTA	0xdead000000000000
#else
#define POISON_POINTER_DELTA	0xdead0000
#endif

/********** include/list.h **********/
/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#define LIST_POISON1  ((void *) 0x00000001 + POISON_POINTER_DELTA)
#define LIST_POISON2  ((void *) 0x00000002 + POISON_POINTER_DELTA)

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_POISON_H */
