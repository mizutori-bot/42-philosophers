/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:30:14 by sho               #+#    #+#             */
/*   Updated: 2022/10/06 19:41:59 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include<unistd.h>
# include<stdio.h>
# include<sys/time.h>
# include<stdlib.h>
# include<stdbool.h>
# include<pthread.h>
# include<limits.h>
# include<semaphore.h>
# include<signal.h>
# include<fcntl.h>
# include<sys/types.h>
# include<sys/wait.h>

typedef struct philo {
	int				philo_num;
	int				sum_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	long long int	last_eat_time;
	int				eat_count;
	int				stop_num;
	bool			need_to_count;
	void			*ptr_to_info;
	sem_t			*write;
	sem_t			*eat;
	sem_t			*fork;
	pthread_t		death_watch_thread;
	int				can_continue;
}	t_philo;

typedef struct info {
	sem_t		*eat;
	sem_t		*fork;
	sem_t		*write;
	int			sum_of_philo;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	pthread_t	meal_times_watch_thread;
	bool		need_to_count;
	int			stop_num;
	pid_t		*pid;
	t_philo		*all_philosophers;
}	t_info;

//arg_check.c
int				arg_checker(int argc, char **argv);
int				check_num_of_arg(int argc);
int				check_param_of_each_arg(int argc, char **argv);
int				wait_and_die(long long int time_to_death);
int				check_if_time_is_within_range(long long int time);

//treat_num.c
long long int	ft_atoi(const char *str);
int				check_if_args_are_number(int argc, char **argv);
int				check_if_it_is_number(char *arg);
int				ps_isdigit(int c);

//philosophers.c
int				launch(t_info *info);
void			philosophers_activity(t_philo *philo);
void			wait_and_kill(t_info *info);

//act.c
int				take_fork(t_philo *philo);
int				eat(t_philo *philo);
int				sleep_philo(t_philo *philo);
int				think(t_philo *philo);

//util.c
int				print_error_msg(char *message);
long long int	get_current_time_in_ms(void);
int				print_time_and_activity(t_info *info,
					long long int current_time, int philo_num, char *message);
int				kill_all(t_info *info);

//init.c
void			init_philo(t_info *info);
int				init_philosophers(t_info *info, int argc, char **argv);
void			allocate_args(t_info *info, int argc, char **argv);
int				init_semaphore(t_info *info);

//free.c
void			free_all(t_info *info);
void			free_all_and_exit(t_info *info);

//util.c
int				print_error_msg(char *message);
long long int	get_current_time_in_ms(void);
int				wait_philo(t_philo *philo, int wait_time);

//watch.c
void			*death_watcher(void *arg);
void			kill_philo_if_lapse_death_time_from_lasteat(
					long long int current_time, t_philo *philo);
void			kill_philo_if_lapse_death_time_from_start(
					long long int current_time, long long int start_time,
					t_philo *philo);

#endif