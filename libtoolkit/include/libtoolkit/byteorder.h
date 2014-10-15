/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2010-2014 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LIBTOOLKIT_BYTEORDER_H
#define _LIBTOOLKIT_BYTEORDER_H

/**
 * @file
 *
 * Byte Swap Operations
 *
 * This file defines a generic API for byte swap operations. Part of
 * the implementation is architecture-specific.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <libtoolkit/asm/config.h>
#include <libtoolkit/asm/byteorder.h>

#ifndef CONFIG_FORCE_INTRINSICS
/**
 * Swap bytes in a 16-bit value.
 */
#define bswap16(x) ((uint16_t)(__builtin_constant_p(x) ?		\
				   constant_bswap16(x) :		\
				   arch_bswap16(x)))

/**
 * Swap bytes in a 32-bit value.
 */
#define bswap32(x) ((uint32_t)(__builtin_constant_p(x) ?		\
				   constant_bswap32(x) :		\
				   arch_bswap32(x)))

/**
 * Swap bytes in a 64-bit value.
 */
#define bswap64(x) ((uint64_t)(__builtin_constant_p(x) ?		\
				   constant_bswap64(x) :		\
				   arch_bswap64(x)))

#else

/**
 * Swap bytes in a 16-bit value.
 * __builtin_bswap16 is only available gcc 4.8 and upwards
 */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
#define bswap16(x) __builtin_bswap16(x)
#else
#define bswap16(x) ((uint16_t)(__builtin_constant_p(x) ?		\
				   constant_bswap16(x) :		\
				   arch_bswap16(x)))
#endif

/**
 * Swap bytes in a 32-bit value.
 */
#define bswap32(x) __builtin_bswap32(x)

/**
 * Swap bytes in a 64-bit value.
 */
#define bswap64(x) __builtin_bswap64(x)

#endif

/**
 * Convert a 16-bit value from CPU order to little endian.
 */
#define cpu_to_le16(x) (x)

/**
 * Convert a 32-bit value from CPU order to little endian.
 */
#define cpu_to_le32(x) (x)

/**
 * Convert a 64-bit value from CPU order to little endian.
 */
#define cpu_to_le64(x) (x)


/**
 * Convert a 16-bit value from CPU order to big endian.
 */
#define cpu_to_be16(x) bswap16(x)

/**
 * Convert a 32-bit value from CPU order to big endian.
 */
#define cpu_to_be32(x) bswap32(x)

/**
 * Convert a 64-bit value from CPU order to big endian.
 */
#define cpu_to_be64(x) bswap64(x)


/**
 * Convert a 16-bit value from little endian to CPU order.
 */
#define le16_to_cpu(x) (x)

/**
 * Convert a 32-bit value from little endian to CPU order.
 */
#define le32_to_cpu(x) (x)

/**
 * Convert a 64-bit value from little endian to CPU order.
 */
#define le64_to_cpu(x) (x)


/**
 * Convert a 16-bit value from big endian to CPU order.
 */
#define be16_to_cpu(x) bswap16(x)

/**
 * Convert a 32-bit value from big endian to CPU order.
 */
#define be32_to_cpu(x) bswap32(x)

/**
 * Convert a 64-bit value from big endian to CPU order.
 */
#define be64_to_cpu(x) bswap64(x)

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_BYTEORDER_H */

