/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:20:03 by sho               #+#    #+#             */
/*   Updated: 2022/09/05 19:50:05 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

#define TAKEN 1
#define NOT_TAKEN 0
#define PHILOSOPHERS 5

int	ft_atoi(const char *str)
{
	size_t			i;
	int				sig;
	long long int	num;

	i = 0;
	sig = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{	
		sig = sig * (',' - str[i]);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sig * num);
}

typedef struct {
	pthread_mutex_t mutex[PHILOSOPHERS];
	int sum_of_philo;
	int philo_num;
	int philo_fork[PHILOSOPHERS];
	long long int last_eat_time[PHILOSOPHERS];
	size_t time_of_death;
	size_t time_of_eat;
	size_t time_of_sleep;
	long long int next_action_time[PHILOSOPHERS];
	long long int time_of_process[PHILOSOPHERS];
} philosopher;

//void eat(const size_t time, int philo_num, pthread_mutex_t *mutex, int *right_fork, int *left_fork)


long long int get_current_time_in_ms(void)
{
	struct timeval time;
	//long long int current_time_ms;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	/* current_time_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time_ms); */
}

void eat(philosopher *philo, int philo_num, int *right_fork, int *left_fork)
{
	//long long lag_time = 0;
	//if (philo->time_of_process[philo_num - 1])
	//	lag_time = philo->time_of_process[philo_num - 1] - philo->time_of_eat - philo->time_of_sleep;
	//printf("lag = %lld\n", lag_time);
	philo->last_eat_time[philo_num - 1] = get_current_time_in_ms(); 
	printf("%lld %d is eating\n", get_current_time_in_ms(), philo_num);
	usleep(philo->time_of_eat * 1000);
	pthread_mutex_lock(&philo->mutex[philo_num - 1]);
	*right_fork = NOT_TAKEN;
	*left_fork = NOT_TAKEN;
	pthread_mutex_unlock(&philo->mutex[philo_num - 1]);
}

void sleep_philo(size_t time, int philo_num)
{
	/* long long int current_time;
	current_time = get_current_time_in_ms(); */
	printf("%lld %d is sleeping\n", get_current_time_in_ms(), philo_num);
	usleep(time * 1000);
}

void think(const size_t time, int philo_num)
{
	long long int current_time;
	current_time = get_current_time_in_ms();
	printf("%lld philo %d is thinking now\n", current_time, philo_num);
	usleep(time * 1000);
}

void take_right_fork(const long long int current_time, int *right_fork, pthread_mutex_t *mutex, const int philo_num)
{
	pthread_mutex_lock(mutex);
	*right_fork = TAKEN;
	printf("%lld philo %d has taken a right fork\n", current_time, philo_num);
	pthread_mutex_unlock(mutex);
}

//leftとrightを一つの関数にまとめることも可能だが、コーディング段階では哲学者が右・左どっちを取ったのかもみたいのでそのままとする

void take_left_fork(const long long int current_time, int *left_fork, pthread_mutex_t *mutex, const int philo_num)
{
	printf("%lld philo %d has taken a left fork\n", current_time, philo_num);
	pthread_mutex_lock(mutex);
	*left_fork = TAKEN;
	pthread_mutex_unlock(mutex);
}

void take_fork(int *fork, pthread_mutex_t *mutex, const int philo_num)
{
	printf("%lld %d has taken a fork\n", get_current_time_in_ms(), philo_num);
	pthread_mutex_lock(mutex);
	*fork = TAKEN;
	pthread_mutex_unlock(mutex);
}

void *philosopher_behavior(void *arg)
{
	static int count_philo;
	count_philo++;
	int philo_num = count_philo;
	philosopher *data = (philosopher *)arg;
	int *right_fork = &data->philo_fork[philo_num - 1];
	int *left_fork = &data->philo_fork[philo_num % data->sum_of_philo];
	long long int interval_start = 0;
	long long int interval_end = 0;
	long long int lag = 0;

	if (philo_num % 2 == 0)
		usleep(200);
	while (1)
	{	
		/* interval_start = get_current_time_in_ms();
		printf("start = %lld\n", interval_start); */
		if (*right_fork == NOT_TAKEN)
		{
			//data->time_of_process[philo_num - 1] = interval_end - interval_start;
			//printf("interval %lld\n", data->time_of_process[philo_num - 1]);
			take_fork(right_fork, &data->mutex[philo_num - 1], philo_num);
			while (1)
			{
				if(*left_fork == NOT_TAKEN)
				{
					take_fork(left_fork, &data->mutex[philo_num - 1], philo_num);
					eat(data, philo_num, right_fork, left_fork);
					//interval_end = get_current_time_in_ms();
					//if (interval_start)
					//	lag = (interval_end - interval_start) - (data->time_of_eat + data->time_of_sleep);
					//printf("lag = %lld\n", lag);
					//long long int sleep_time_with_lag = data->time_of_sleep - lag; 
					//printf("sleep_time_with_lag = %lld\n", sleep_time_with_lag);
					//interval_start = get_current_time_in_ms();
					sleep_philo(data->time_of_sleep, philo_num);
					printf("%lld %d is thinking\n", get_current_time_in_ms(), philo_num);
					break;
				}
			}
			//interval_end = get_current_time_in_ms();
			//data->next_action_time[philo_num - 1] = data->time_of_eat - lag;
		}
	}
	return (NULL);
}

void *watch_if_philo_alive(void *arg)
{
	static int count_philo;
	count_philo++;
	int philo_num = count_philo;
	philosopher *philo;
	philo = (philosopher *)arg;
	long long int start_time = get_current_time_in_ms();
	//long long int current_time = get_current_time_in_ms();
	philo->last_eat_time[philo_num - 1] = get_current_time_in_ms(); 
	while (1)
	{
		/* if(get_current_time_in_ms() - philo->last_eat_time >= philo->time_of_death)
		{
			printf("philo %d died", philo_num);
			exit(EXIT_FAILURE);
		} */
		/* if (philo->last_eat_time[philo_num - 1] == 0)
			if (get_current_time_in_ms() - start_time >= (long long int)philo->time_of_death)
			{
				printf("philo %d died", philo_num);
				exit(EXIT_FAILURE);
			} */
		if (philo->last_eat_time[philo_num - 1])
		{
			/* long long int elapsed = get_current_time_in_ms() - philo->last_eat_time[philo_num - 1];
			if (elapsed != get_current_time_in_ms() - philo->last_eat_time[philo_num - 1])
				printf("[%d] %lld\n", philo_num, get_current_time_in_ms() - philo->last_eat_time[philo_num - 1]); */
			if (get_current_time_in_ms() - philo->last_eat_time[philo_num - 1] >= (long long int)philo->time_of_death)
			{
				printf("%lld %d died\n", get_current_time_in_ms(), philo_num);
				exit(EXIT_FAILURE);
			}
		}

		
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int philosophers = ft_atoi(argv[1]);
	philosopher data;
	pthread_t thread[philosophers];
	pthread_t dead_monitor[philosophers];
	
	if (argc != 5)
		exit(EXIT_FAILURE);
	//ーーエラー処理ーー
	//argv[1] [2] [3] [4]が数字じゃない場合
	//哲学者の数がスレッドの上限値を超えてしまっている場合
	for (int i = 0; i < philosophers; i++)
		pthread_mutex_init(&data.mutex[i], NULL);
	for (int i = 0; i < philosophers; i++)
		data.philo_fork[i] = NOT_TAKEN;
	for (int i = 0; i < philosophers; i++)
		data.last_eat_time[i] = 0;
	for (int i = 0; i < philosophers; i++)
		data.time_of_process[i] = 0;
	for (int i = 0; i < philosophers; i++)
		data.next_action_time[i] = 0; 
	data.sum_of_philo = philosophers;
	data.time_of_death = ft_atoi(argv[2]);
	data.time_of_eat = ft_atoi(argv[3]);
	data.time_of_sleep = ft_atoi(argv[4]);

	for (int i = 0; i < philosophers; i++)
	{
		pthread_create(&thread[i], NULL, philosopher_behavior, &data);
		pthread_create(&dead_monitor[i], NULL, watch_if_philo_alive, &data);
	}
	
	for (int i = 0; i < philosophers; i++)
	{
		pthread_join(thread[i], NULL);
		pthread_join(dead_monitor[i], NULL);
	}
	
	for (int i = 0; i < philosophers; i++)
		pthread_mutex_destroy(&data.mutex[i]);

	return (0);
}
