/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:56:29 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:34 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	print_error_msg(char *message)
{
	if (printf("%s\n", message) < 0)
		return (print_error_msg("\nprintf error\n"));
	return (-1);
}

long long int	get_current_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (print_error_msg("gettimeofday error\n"));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print_time_and_activity(t_info *info, int philo_num, int act)
{
	long long int current_time;
	
	
	pthread_mutex_lock(&info->write);
	current_time = get_elapsed_time(info);
	if (act == NUM_FORK && if_can_continue_true(info))
	printf("%lld %d has taken a fork\n", current_time, philo_num);
	else if (act == NUM_EAT && if_can_continue_true(info))
	printf("%lld %d is eating\n", current_time, philo_num);
	else if (act == NUM_SLEEP && if_can_continue_true(info))
	printf("%lld %d is sleeping\n", current_time, philo_num);
	else if (act == NUM_THINK && if_can_continue_true(info))
	printf("%lld %d is thinking\n", current_time, philo_num);
	else if (act == NUM_DIE && if_can_continue_true(info))
	printf("%lld %d died\n", current_time, philo_num);
	pthread_mutex_unlock(&info->write);
	return (0);
}

int	wait_philo(int wait_time, t_info *info)
{
	long long int	start_time;
	long long int	current_time;

	start_time = get_elapsed_time(info);
	if (start_time == -1)
		return (-1);
	while (1)
	{
		current_time = get_elapsed_time(info);
		if (current_time >= start_time + wait_time)
			return (0);
		usleep(500);
	}
	return (0);
}
