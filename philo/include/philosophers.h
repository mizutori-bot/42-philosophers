/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:29:59 by sho               #+#    #+#             */
/*   Updated: 2022/10/31 19:42:40 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include<unistd.h>
# include<stdio.h>
# include<pthread.h>
# include<sys/time.h>
# include<stdlib.h>
# include<stdbool.h>
# include<limits.h>

# define ERROR -1
# define NUM_FORK 1
# define NUM_EAT 2
# define NUM_SLEEP 3
# define NUM_THINK 4
# define NUM_DIE 5
# define LOCK 1
# define UNLOCK 0

typedef struct philo {
	int				eat_times;
	long long int	last_eat_time;
	int				philo_num;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*time;
	void			*info;
	bool			*can_continue;
	long long int	ideal_time;
}	t_philo;

typedef struct philosophers {
	int				sum_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	long long int	start_time;
	bool			can_continue;
	bool			need_to_count;
	pthread_mutex_t	*fork;
	pthread_mutex_t end_flag;
	pthread_mutex_t count_meals;
	pthread_mutex_t	write;
	pthread_mutex_t	*time;
	int				philos_complete_meal;
	int				stop_num;
	t_philo			*all_philosophers;
	pthread_t		*thread;
	pthread_t		watch_thread; 
}	t_info;

//philosophers.c
int				launch(t_info *info);
void			*philosophers_activity(void *arg);

//util.c
int				print_error_msg(char *message);
long long int	ft_atoi(const char *str);
long long int	get_current_time_in_ms(void);
int				print_time_and_activity(t_info *info, int philo_num, int act);

//util2.c
long long int	get_current_time_in_usec(void);
long long int	get_elapsed_time(t_info *info);
void			timer(t_philo *philo);


//init_philo.c
int				init_mutex(t_info *info);
int				init_philosophers(t_info *info,
					int argc, char **argv);
void			init_philo(t_info *info);
void			allocate_args(t_info *info,
					int argc, char **argv);
int				unlock_mutex(pthread_mutex_t *fork, bool *can_contine);

//free.c
void			free_all(t_info *info);
void			free_all_and_exit(t_info *info);

//act.c
void				take_fork(t_philo *philo, t_info *info, int philo_num);
void				eat(t_philo *philo, pthread_mutex_t *right_fork,
					pthread_mutex_t *left_fork);
void				sleep_philo(t_info *info,
					t_philo *philo, int time_to_sleep);
void				think(t_info *info, t_philo *philo);

int				wait_philo(int wait_time, t_info *info);
int				if_can_continue_true(t_info *info);
int				lock_unlock_mutex(int lock_or_unlock,
					pthread_mutex_t *mutex, bool *can_contine);
void				eat_times_checker(t_philo *philo);

//watcher.c
int				kill_philo_if_lapse_death_time_from_start(
					long long int current_time, long long int start_time,
					t_philo *philo, t_info *info);
int				set_can_continue_to_false(bool *can_continue);
void			*watch_if_need_to_stop(void *arg);
int death_checker(t_philo *philo,
				 long long int current_time, long long int start_time);
int	kill_philo_if_lapse_death_time_from_lasteat(long long int current_time,
												t_philo *philo, t_info *info, long long int last_time_eat);

//arg_check.c
int				check_num_of_arg(int argc);
int				arg_checker(int argc, char **argv);
int				check_if_time_is_within_range(long long int time);
int				check_param_of_each_arg(int argc, char **argv);
void			wait_and_die(t_philo *philo);

int				check_if_args_are_number(int argc, char **argv);
int				check_if_it_is_number(char *arg);
int				ps_isdigit(int c);

#endif