#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libtoolkit/memcpy.h>
#include <libtoolkit/random.h>

/*
 * Set this to the maximum buffer size you want to test. If it is 0, then the
 * values in the buf_sizes[] array below will be used.
 */
#define TEST_VALUE_RANGE        0

/* List of buffer sizes to test */
#if TEST_VALUE_RANGE == 0
static size_t buf_sizes[] = {
	0, 1, 7, 8, 9, 15, 16, 17, 31, 32, 33, 63, 64, 65, 127, 128, 129, 255,
	256, 257, 320, 384, 511, 512, 513, 1023, 1024, 1025, 1518, 1522, 1600,
	2048, 3072, 4096, 5120, 6144, 7168, 8192
};
/* MUST be as large as largest packet size above */
#define SMALL_BUFFER_SIZE       8192
#else /* TEST_VALUE_RANGE != 0 */
static size_t buf_sizes[TEST_VALUE_RANGE];
#define SMALL_BUFFER_SIZE       TEST_VALUE_RANGE
#endif /* TEST_VALUE_RANGE == 0 */


/*
 * Arrays of this size are used for measuring uncached memory accesses by
 * picking a random location within the buffer. Make this smaller if there are
 * memory allocation errors.
 */
#define LARGE_BUFFER_SIZE       (100 * 1024 * 1024)

/* How many times to run timing loop for performance tests */
#define TEST_ITERATIONS         1000000
#define TEST_BATCH_SIZE         100

/* Data is aligned on this many bytes (power of 2) */
#define ALIGNMENT_UNIT          16



/* Structure with base memcpy func pointer, and number of bytes it copies */
struct base_memcpy_func {
	void (*func)(uint8_t *dst, const uint8_t *src);
	unsigned size;
};

/* To create base_memcpy_func structure entries */
#define BASE_FUNC(n) {sse_mov##n, n}

/* Max number of bytes that can be copies with a "base" memcpy functions */
#define MAX_BASE_FUNC_SIZE 256

/*
 * Test the "base" memcpy functions, that a copy fixed number of bytes.
 */
static int
base_func_test(void)
{
	const struct base_memcpy_func base_memcpy_funcs[6] = {
		BASE_FUNC(16),
		BASE_FUNC(32),
		BASE_FUNC(48),
		BASE_FUNC(64),
		BASE_FUNC(128),
		BASE_FUNC(256),
	};
	unsigned i, j;
	unsigned num_funcs = sizeof(base_memcpy_funcs) / sizeof(base_memcpy_funcs[0]);
	uint8_t dst[MAX_BASE_FUNC_SIZE];
	uint8_t src[MAX_BASE_FUNC_SIZE];

	for (i = 0; i < num_funcs; i++) {
		unsigned size = base_memcpy_funcs[i].size;
		for (j = 0; j < size; j++) {
			dst[j] = 0;
			src[j] = (uint8_t) random8();
		}
		base_memcpy_funcs[i].func(dst, src);
		for (j = 0; j < size; j++)
			if (dst[j] != src[j])
				return -1;
	}

	return 0;
}

/*
 * Create two buffers, and initialise one with random values. These are copied
 * to the second buffer and then compared to see if the copy was successful.
 * The bytes outside the copied area are also checked to make sure they were not
 * changed.
 */
static int
test_single_memcpy(unsigned int off_src, unsigned int off_dst, size_t size)
{
	unsigned int i;
	uint8_t dest[SMALL_BUFFER_SIZE + ALIGNMENT_UNIT];
	uint8_t src[SMALL_BUFFER_SIZE + ALIGNMENT_UNIT];
	void * ret;

	/* Setup buffers */
	for (i = 0; i < SMALL_BUFFER_SIZE + ALIGNMENT_UNIT; i++) {
		dest[i] = 0;
		src[i] = (uint8_t) random8();
	}

	/* Do the copy */
	ret = sse_memcpy(dest + off_dst, src + off_src, size);
	if (ret != (dest + off_dst)) {
		printf("sse_memcpy() returned %p, not %p\n",
		       ret, dest + off_dst);
	}

	/* Check nothing before offset is affected */
	for (i = 0; i < off_dst; i++) {
		if (dest[i] != 0) {
			printf("sse_memcpy() failed for %u bytes (offsets=%u,%u): "
			       "[modified before start of dst].\n",
			       (unsigned)size, off_src, off_dst);
			return -1;
		}
	}

	/* Check everything was copied */
	for (i = 0; i < size; i++) {
		if (dest[i + off_dst] != src[i + off_src]) {
			printf("sse_memcpy() failed for %u bytes (offsets=%u,%u): "
			       "[didn't copy byte %u].\n",
			       (unsigned)size, off_src, off_dst, i);
			return -1;
		}
	}

	/* Check nothing after copy was affected */
	for (i = size; i < SMALL_BUFFER_SIZE; i++) {
		if (dest[i + off_dst] != 0) {
			printf("sse_memcpy() failed for %u bytes (offsets=%u,%u): "
			       "[copied too many].\n",
			       (unsigned)size, off_src, off_dst);
			return -1;
		}
	}
	return 0;
}

/*
 * Check functionality for various buffer sizes and data offsets/alignments.
 */
static int
func_test(void)
{
	unsigned int off_src, off_dst, i;
	unsigned int num_buf_sizes = sizeof(buf_sizes) / sizeof(buf_sizes[0]);
	int ret;

	for (off_src = 0; off_src < ALIGNMENT_UNIT; off_src++) {
		for (off_dst = 0; off_dst < ALIGNMENT_UNIT; off_dst++) {
			for (i = 0; i < num_buf_sizes; i++) {
				ret = test_single_memcpy(off_src, off_dst,
				                         buf_sizes[i]);
				if (ret != 0)
					return -1;
			}
		}
	}
	return 0;
}

int
test_memcpy(void)
{
	int ret;

	ret = func_test();
	if (ret != 0)
		return -1;
	ret = base_func_test();
	if (ret != 0)
		return -1;
	return 0;
}

/* a server in the cluster */
struct Node {
	uint64_t server_id;	/* id of the server */
	uint16_t port;		/* port */
	char	 addr[40];	/* host address */	
} __attribute((__packed__));

/* servers in the cluster */
struct Config {
	uint8_t	len;		/* count of nodes */
	Node	node[0];	/* nodes array  */
} __attribute__((__packed__));

/* log entry */
struct Entry {
#define RAFT_CONF (0x1 << 0)	/* stores a 'configuration' */
#define RAFT_DATA (0x1 << 1)	/* stores a cmd to be processed by the state machine */
#define RAFT_NOOP (0x1 << 2)	/* no operation */

	uint64_t term;		/* term in which the entry was first created */
	uint64_t idx;		/* entry's unique ID */

	uint16_t type:2;	/* the entry's type */
	uint16_t len:14;	/* data's length in bytes */
	char     data[0];
} __attribute__((__packed__));

void test_cpy(int size)
{

	int err = 0;
	uint64_t last_term = 0;
	uint64_t last_index = 0;
	Entry entry;
	Entry *ent1;
	Entry *ent2;

	/* build 'CONFIG' entry */

	entry.term = 1;
	entry.idx = 1;
	entry.type = 1;
	entry.len = size;

	ent1 = (Entry *)malloc(sizeof(Entry) + size);
	*ent1 = entry;
	//ent2 = (Entry *)malloc(sizeof(Entry) + size);
	for (int i = 0; i < size; i++) {
		ent1->data[i] = random8();
	}

	sse_memcpy(entry.data, ent1->data, entry.len);
	if (strncmp((char *)&entry, (char *)ent1, sizeof(Entry) + size)) {
		printf("fuck sse_memcpy\n");
	}
}

int main()
{

	for (int i = 1; i < 5000; i++)
		test_cpy(51);
	test_memcpy();

	return 0;
}
