/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:50:45 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:27 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->sum_of_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&info->time[i]);
		i++;
	}
	pthread_mutex_destroy(&info->end_flag);
	pthread_mutex_destroy(&info->count_meals);
	pthread_mutex_destroy(&info->write);
	if (info->all_philosophers)
	{
		free(info->all_philosophers);
		info->all_philosophers = NULL;
	}
}

void	free_all_and_exit(t_info *info)
{
	free_all(info);
	exit(0);
}
