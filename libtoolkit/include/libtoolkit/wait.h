#ifndef _LIBTOOLKIT_WAIT_H
#define _LIBTOOLKIT_WAIT_H

#include <libtoolkit/asm/config.h>

#if defined(CONFIG_GCC_4_4) && defined(__cplusplus)
#include <libtoolkit/wait_gcc4.h>
#else
#include <libtoolkit/wait_gcc.h>
#endif

#endif /* _LIBTOOLKIT_WAIT_H */
