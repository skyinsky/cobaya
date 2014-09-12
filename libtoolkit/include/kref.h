/*
 * kref.h - library routines for handling generic reference counted objects
 *
 * Copyright (C) 2004 Greg Kroah-Hartman <greg@kroah.com>
 * Copyright (C) 2004 IBM Corp.
 *
 * based on kobject.h which was:
 * Copyright (C) 2002-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (C) 2002-2003 Open Source Development Labs
 *
 * This file is released under the GPLv2.
 *
 */

#ifndef _LIBTOOLKIT_KREF_H
#define _LIBTOOLKIT_KREF_H

/**
 * @file
 *
 * Thread-safe Reference Counter Operations.
 */

#include <assert.h>
#include "asm/barrier.h"
#include "atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

struct kref {
	atomic32_t refcount;
};

/**
 * kref_init - initialize object.
 * @kref: object in question.
 */
void kref_init(struct kref *kref)
{
	atomic_set(&kref->refcount, 1);
	smp_mb();
}

/**
 * kref_get - increment refcount for object.
 * @kref: object.
 *
 * NOTE: If refcount was 0 before incrementing then we have a race
 * condition when this kref is freeing by some other thread right now.
 */
void kref_get(struct kref *kref)
{
	atomic_inc(&kref->refcount);
	smp_mb__after_atomic_inc();
}

/**
 * kref_put - decrement refcount for object.
 * @kref: object.
 * @release: pointer to the function that will clean up the object when the
 *	     last reference to the object is released.
 *	     This pointer is required, and it is not acceptable to pass kfree
 *	     in as this function.
 *
 * Decrement the refcount, and if 0, call release().
 * Return 1 if the object was removed, otherwise return 0.  Beware, if this
 * function returns 0, you still can not count on the kref from remaining in
 * memory.  Only use the return value if you want to see if the kref is now
 * gone, not present.
 */
int kref_put(struct kref *kref, void (*release)(struct kref *kref))
{
	assert(release != NULL);

	if (atomic32_dec_and_test(&kref->refcount)) {
		release(kref);
		return 1;
	}
	return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_KREF_H */
