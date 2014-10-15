#ifndef _LIBTOOLKIT_CONFIG_H
#define _LIBTOOLKIT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* cpu config */
#define CONFIG_X86_CMOV	1
#define CONFIG_SMP	1
#undef	CONFIG_X86_PPRO_FENCE
#undef	CONFIG_X86_OOSTORE
#define CONFIG_X86_L1_CACHE_SHIFT 6

/* defined for using intrinsics implementation */
#undef	CONFIG_FORCE_INTRINSICS

/* debug log config */
#define CONFIG_DEBUG

/* gcc */
#define CONFIG_GCC_4_4

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_CONFIG_H */
