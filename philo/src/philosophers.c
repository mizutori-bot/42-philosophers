/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:47:57 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:32 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (arg_checker(argc, argv) == -1)
		return (0);
	if (init_philosophers(&info, argc, argv) == -1)
		free_all_and_exit(&info);
	if (init_mutex(&info) == -1)
		free_all_and_exit(&info);
	init_philo(&info);
	if (launch(&info) == -1)
		free_all_and_exit(&info);
}

int	launch(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->sum_of_philo)
	{
		if (pthread_create(&info->thread[i], NULL, &philosophers_activity,
				(void *)&info->all_philosophers[i]) != 0)
			return (print_error_msg("pthread_create error"));
		i++;
	}
	pthread_create(&info->watch_thread, NULL, &watch_if_need_to_stop, (void *)info);
	i = 0;
	while (i < info->sum_of_philo)
	{
		pthread_join(info->thread[i], NULL);
		i++;
	}
	pthread_join(info->watch_thread, NULL);
	free_all_and_exit(info);
	return (0);
}

void	*philosophers_activity(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = (t_info *)philo->info;
	if (philo->philo_num % 2 == 0)
		usleep(500);
	if (info->sum_of_philo == 1)
	{
		wait_and_die(philo);
		return (NULL);
	}
	if (info->sum_of_philo % 2 && philo->philo_num == info->sum_of_philo)
		wait_philo(info->time_to_eat * 2, info);
	while (if_can_continue_true(info))
	{
		take_fork(philo, info, philo->philo_num);
		eat(philo, philo->right_fork, philo->left_fork);
		sleep_philo(info, philo, info->time_to_sleep);
		think(info, philo);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void wait_and_die(t_philo *philo)
{
	t_info	*info;
	info = (t_info *)philo->info;

	print_time_and_activity(info, philo->philo_num, NUM_FORK);
	wait_philo(info->time_to_die, info);
}

int	if_can_continue_true(t_info *info)
{
	pthread_mutex_lock(&info->end_flag);
	if (info->can_continue)
	{
		pthread_mutex_unlock(&info->end_flag);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&info->end_flag);
		return (0);
	}
}
