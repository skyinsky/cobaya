#ifndef _LIBTOOLKIT_WAIT_H
#define _LIBTOOLKIT_WAIT_H

#include "asm/config.h"

#ifdef CONFIG_GCC_4_4
#include "wait_cpp.h"
#else
#include "wait_c.h"
#endif

#endif /* _LIBTOOLKIT_WAIT_H */
