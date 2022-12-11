/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:16:05 by sho               #+#    #+#             */
/*   Updated: 2022/10/06 20:05:15 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo_bonus.h"

int	print_error_msg(char *message)
{
	printf("%s\n", message);
	return (-1);
}

long long int	get_current_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print_time_and_activity(t_info *info, long long int current_time,
							int philo_num, char *message)
{
	sem_wait(info->write);
	printf("%lld %d %s", current_time, philo_num, message);
	sem_post(info->write);
	return (0);
}

int	kill_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->sum_of_philo)
	{
		kill(info->pid[i], SIGKILL);
		i++;
	}
	return (0);
}

int	wait_philo(t_philo *philo, int wait_time)
{
	long long int	start_time;
	long long int	current_time;

	(void)philo;
	start_time = get_current_time_in_ms();
	while (1)
	{
		current_time = get_current_time_in_ms();
		if (current_time >= start_time + wait_time)
			return (0);
		usleep(1000);
	}
	return (0);
}
