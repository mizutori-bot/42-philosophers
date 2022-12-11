#include <stdio.h>
#include <time.h>
#include <sys/time.h>



int main(void)
{
	struct timeval mytime;
	
	gettimeofday(&mytime, NULL);
	printf("%ld %d\n", mytime.tv_sec, mytime.tv_usec); */
	get_current_time_in_usec();	
}
