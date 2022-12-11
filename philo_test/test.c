/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:35:04 by sho               #+#    #+#             */
/*   Updated: 2022/09/18 18:51:07 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

typedef struct 
{
	pthread_mutex_t fork;
	pthread_mutex_t eat;
	int count;
} t_data;

void *count_up(void *arg)
{
	t_data *data;
	data = (t_data *)arg;

	int i = 0;
	while (i < 50000)
	{
		pthread_mutex_lock(&data->fork);
		data->count++;
		pthread_mutex_unlock(&data->fork);
		i++;
	}
	return (NULL);
}

void *sleep_one(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
	static int id;
	id++;
	int num = id;

	while (1)
	{
		pthread_mutex_lock(&data->eat);
		printf("hello, id %d is eating", num);
		data->count++;
		printf(" count = %d\n", data->count);
		sleep(2);
		pthread_mutex_unlock(&data->eat);
		sleep(1);
	}
}

void *think_one(void *arg)
{
	t_data *data;
	data = (t_data *)arg;

	while(1)
	{
		pthread_mutex_lock(&data->eat);
		printf("hello, i am thinkin\n");
		data->count++;
		printf(" count = %d\n", data->count);
		sleep(2);
		pthread_mutex_unlock(&data->eat);
		sleep(1);
	}
}

int main(void)
{
	t_data data;
	pthread_t thread[3];

	pthread_mutex_init(&data.eat, NULL);
	data.count = 0;
	pthread_create(&thread[0], NULL, sleep_one, (void *)&data);
	pthread_create(&thread[1], NULL, sleep_one, (void *)&data);
	pthread_create(&thread[2], NULL, think_one, (void *)&data);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);

	pthread_mutex_destroy(&data.eat);

	printf("%d\n", data.count);

}