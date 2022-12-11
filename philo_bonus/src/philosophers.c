/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:56:39 by sho               #+#    #+#             */
/*   Updated: 2022/10/06 20:11:39 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo_bonus.h"

/* __attribute__((destructor))
static void destructor() {
    system("leaks -q philo_bonus");
} */

int	main(int argc, char **argv)
{
	t_info	info;

	if (arg_checker(argc, argv) == -1)
		return (0);
	if (init_philosophers(&info, argc, argv) == -1)
		free_all_and_exit(&info);
	if (init_semaphore(&info) == -1)
		free_all_and_exit(&info);
	init_philo(&info);
	if (launch(&info) == -1)
		free_all_and_exit(&info);
	free_all_and_exit(&info);
}

int	launch(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->sum_of_philo)
	{
		info->pid[i] = fork();
		if (info->pid[i] < 0)
			return (print_error_msg("fork"));
		if (info->pid[i] == 0)
		{
			pthread_create(&info->all_philosophers[i].death_watch_thread,
				NULL, death_watcher, (void *)&info->all_philosophers[i]);
			philosophers_activity(&info->all_philosophers[i]);
		}
		i++;
	}
	wait_and_kill(info);
	sem_close(info->fork);
	sem_close(info->eat);
	sem_close(info->write);
	sem_unlink("/fork");
	sem_unlink("/eat");
	sem_unlink("/write");
	return (0);
}

void	wait_and_kill(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->sum_of_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) > 0)
		{
			kill_all(info);
			break ;
		}
		i++;
	}
}

void	philosophers_activity(t_philo *philo)
{
	usleep(225 * (philo->sum_of_philo - philo->philo_num));
	if (philo->philo_num % 2 == 0)
		usleep(30000);
	while (1)
	{
		take_fork(philo);
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	pthread_join(philo->death_watch_thread, NULL);
	exit(0);
}
