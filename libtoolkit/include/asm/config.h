#ifndef _LIBTOOLKIT_CONFIG_H
#define _LIBTOOLKIT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_X86_CMOV	1
#define CONFIG_SMP	1
#undef	CONFIG_FORCE_INTRINSICS
#define CONFIG_X86_L1_CACHE_SHIFT 6

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_CONFIG_H */
