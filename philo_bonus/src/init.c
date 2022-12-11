/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:24:17 by sho               #+#    #+#             */
/*   Updated: 2022/10/06 20:11:52 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo_bonus.h"

void	init_philo(t_info *info)
{
	int		i;
	int		sum_philo;
	t_philo	*philos;

	sum_philo = info->sum_of_philo;
	philos = info->all_philosophers;
	i = 0;
	while (i < sum_philo)
	{
		philos[i].philo_num = i + 1;
		philos[i].time_to_eat = info->time_to_eat;
		philos[i].time_to_sleep = info->time_to_sleep;
		philos[i].time_to_die = info->time_to_die;
		philos[i].eat = info->eat;
		philos[i].fork = info->fork;
		philos[i].write = info->write;
		philos[i].ptr_to_info = info;
		philos[i].sum_of_philo = info->sum_of_philo;
		philos[i].stop_num = info->stop_num;
		philos[i].eat_count = 0;
		philos[i].need_to_count = info->need_to_count;
		i++;
	}
}

int	init_philosophers(t_info *info, int argc, char **argv)
{
	allocate_args(info, argc, argv);
	info->all_philosophers = (t_philo *)malloc(sizeof(t_philo)
			* info->sum_of_philo);
	info->pid = (pid_t *)malloc(sizeof(pid_t) * info->sum_of_philo);
	if (!info->all_philosophers || !info->pid)
		return (print_error_msg("malloc error"));
	return (0);
}

void	allocate_args(t_info *info, int argc, char **argv)
{
	*info = (t_info){
		.sum_of_philo = (int)ft_atoi(argv[1]),
		.time_to_die = ft_atoi(argv[2]),
		.time_to_eat = ft_atoi(argv[3]),
		.time_to_sleep = ft_atoi(argv[4]),
		.need_to_count = false,
	};
	if (argc == 6)
	{
		info->need_to_count = true;
		info->stop_num = ft_atoi(argv[5]);
	}
}

int	init_semaphore(t_info *info)
{
	sem_unlink("/fork");
	sem_unlink("/eat");
	sem_unlink("/write");
	info->eat = sem_open("/eat", O_CREAT, 0700, 1);
	if (info->eat == SEM_FAILED)
		perror("sem_open error");
	info->fork = sem_open("/fork", O_CREAT, 0700, info->sum_of_philo);
	if (info->fork == SEM_FAILED)
		perror("sem_open error");
	info->write = sem_open("/write", O_CREAT, 0700, 1);
	if (info->write == SEM_FAILED)
		perror("sem_open error");
	return (0);
}
