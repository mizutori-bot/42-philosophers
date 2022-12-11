/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:09:48 by sho               #+#    #+#             */
/*   Updated: 2022/10/20 19:58:19 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

long long int get_current_time_in_usec(void)
{
	struct timeval mytime;
	
	gettimeofday(&mytime, NULL);
	return((mytime.tv_sec * 1000000) + mytime.tv_usec);
}

void timer(void)
{
	static int count;
	static long long int time1;
	long long int time2;
	count++;

	if (count % 2) //奇数
		time1 = get_current_time_in_usec();
	else
	{
		time2 = get_current_time_in_usec();
		printf("time = %lld\n", time2 - time1);
	}
}

int main(void)
{
	pthread_mutex_t eat;
	pthread_mutex_init(&eat, NULL);
	timer();
	for (int i = 0; i < 100; i++)
	{
		pthread_mutex_lock(&eat);
		pthread_mutex_unlock(&eat);
	}
	timer();
}