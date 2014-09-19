#ifndef _LIBTOOLKIT_LIST_SORT_H
#define _LIBTOOLKIT_LIST_SORT_H

///* example to use 'list_sort()' */
//
//struct debug_el {
//	struct list_head l_h;
//	int value;
//	unsigned serial;
//};
//
//static int cmp(void *priv, struct list_head *a, struct list_head *b)
//{
//	return container_of(a, struct debug_el, l_h)->value
//	     - container_of(b, struct debug_el, l_h)->value;
//}
//
///*
// * The pattern of set bits in the list length determines which cases
// * are hit in list_sort().
// */
//#define LIST_SORT_TEST_LENGTH (512+128+2) /* not including head */
//
//static int __init list_sort_test(void)
//{
//	int i, r = 1, count;
//	struct list_head *head = kmalloc(sizeof(*head), GFP_KERNEL);
//	struct list_head *cur;
//
//	printk(KERN_WARNING "testing list_sort()\n");
//
//	cur = head;
//	for (i = 0; i < LIST_SORT_TEST_LENGTH; i++) {
//		struct debug_el *el = kmalloc(sizeof(*el), GFP_KERNEL);
//		BUG_ON(!el);
//		 /* force some equivalencies */
//		el->value = (r = (r * 725861) % 6599) % (LIST_SORT_TEST_LENGTH/3);
//		el->serial = i;
//
//		el->l_h.prev = cur;
//		cur->next = &el->l_h;
//		cur = cur->next;
//	}
//	head->prev = cur;
//
//	list_sort(NULL, head, cmp);
//
//	count = 1;
//	for (cur = head->next; cur->next != head; cur = cur->next) {
//		struct debug_el *el = container_of(cur, struct debug_el, l_h);
//		int cmp_result = cmp(NULL, cur, cur->next);
//		if (cur->next->prev != cur) {
//			printk(KERN_EMERG "list_sort() returned "
//						"a corrupted list!\n");
//			return 1;
//		} else if (cmp_result > 0) {
//			printk(KERN_EMERG "list_sort() failed to sort!\n");
//			return 1;
//		} else if (cmp_result == 0 &&
//				el->serial >= container_of(cur->next,
//					struct debug_el, l_h)->serial) {
//			printk(KERN_EMERG "list_sort() failed to preserve order"
//						 " of equivalent elements!\n");
//			return 1;
//		}
//		kfree(cur->prev);
//		count++;
//	}
//	kfree(cur);
//	if (count != LIST_SORT_TEST_LENGTH) {
//		printk(KERN_EMERG "list_sort() returned list of"
//						"different length!\n");
//		return 1;
//	}
//	return 0;
//}

#include <linux/types.h>
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct list_head;

/**
 * list_sort - sort a list
 * @priv: private data, opaque to list_sort(), passed to @cmp
 * @head: the list to sort
 * @cmp: the elements comparison function
 *
 * This function implements "merge sort", which has O(nlog(n))
 * complexity.
 *
 * The comparison function @cmp must return a negative value if @a
 * should sort before @b, and a positive value if @a should sort after
 * @b. If @a and @b are equivalent, and their original relative
 * ordering is to be preserved, @cmp must return 0.
 */
void list_sort(void *priv, struct list_head *head,
	       int (*cmp)(void *priv, struct list_head *a,
			  struct list_head *b));

#ifdef __cplusplus
}
#endif

#endif /* _LIBTOOLKIT_LIST_SORT_H */
