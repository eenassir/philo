#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int main()
{
	struct timeval lst;

	gettimeofday(&lst, NULL);
	printf ("%ld\n", lst.tv_sec);
	printf ("%d\n", lst.tv_usec);
}
