#include <stdlib.h>
#include <stdio.h>
#include "wait.h"

struct fuck {
	int a;
	int b;
};

int main()
{
	fuck c = {
		b : 2,
	};

	DECLARE_WAITQUEUE(queue);
	DECLARE_WAIT_QUEUE_HEAD(wq);

	wait_event(wq, 0);
printf("%d, %d\n", c.a, c.b);

	return 0;

}
