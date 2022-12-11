/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:20:03 by sho               #+#    #+#             */
/*   Updated: 2022/09/08 19:55:16 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

#define TAKEN 1
#define NOT_TAKEN 0
#define PHILOSOPHERS 5

long long int	ft_atoi(const char *str)
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

void	ph_wait(philosopher *man, int wait_time, int philo_num)
{
	long long	start;
	long long	time;

	start = get_current_time_in_ms();
	while (1)
	{
		time = get_current_time_in_ms();
		if (time >= start + wait_time)
			return ;
		usleep(50);
	}
}

void eat(philosopher *philo, int philo_num, pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	//long long lag_time = 0;
	//if (philo->time_of_process[philo_num - 1])
	//	lag_time = philo->time_of_process[philo_num - 1] - philo->time_of_eat - philo->time_of_sleep;
	//printf("lag = %lld\n", lag_time);
	philo->last_eat_time[philo_num - 1] = get_current_time_in_ms(); 
	printf("%lld %d is eating\n", get_current_time_in_ms(), philo_num);
	ph_wait(philo, philo->time_of_eat, philo_num);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
}

void sleep_philo(philosopher *philo, size_t time, int philo_num)
{
	/* long long int current_time;
	current_time = get_current_time_in_ms(); */
	printf("%lld %d is sleeping\n", get_current_time_in_ms(), philo_num);
	ph_wait(philo, philo->time_of_sleep, philo_num);
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
	printf("%lld philo %d has taken a right fork\n", current_time, philo_num);
	pthread_mutex_lock(mutex);
	*right_fork = TAKEN;
	pthread_mutex_unlock(mutex);
}

//leftとrightを一つの関数にまとめることも可能だが、コーディング段階では哲学者が右・左どっちを取ったのかもみたいのでそのままとする

void take_left_fork(const long long int current_time, int *left_fork, pthread_mutex_t *mutex, const int philo_num)
{
	pthread_mutex_lock(mutex);
	printf("%lld philo %d has taken a left fork\n", current_time, philo_num);

}

void take_fork(pthread_mutex_t *mutex, const int philo_num)
{
	pthread_mutex_lock(mutex);
	printf("%lld %d has taken a fork\n", get_current_time_in_ms(), philo_num);
}

void *philosopher_behavior(void *arg)
{
	static int count_philo;
	count_philo++;
	int philo_num = count_philo;
	philosopher *data = (philosopher *)arg;
	pthread_mutex_t *right_fork = &data->mutex[philo_num - 1];
	pthread_mutex_t *left_fork = &data->mutex[(philo_num + data->sum_of_philo) % data->sum_of_philo];
	

	if (philo_num % 2 == 0)
		usleep(200);
	while (1)
	{	
		take_fork(right_fork, philo_num);
		take_fork(left_fork, philo_num);
		eat(data, philo_num, right_fork, left_fork);
		sleep_philo(data, data->time_of_sleep, philo_num);
		printf("%lld %d is thinking\n", get_current_time_in_ms(), philo_num);
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
	//philo->last_eat_time[philo_num - 1] = get_current_time_in_ms(); 
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
			usleep(200);
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
