/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:30:29 by sho               #+#    #+#             */
/*   Updated: 2022/09/27 17:27:53 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./include/philo_bonus.h"

typedef struct {
	int count;
	int id[2];
	sem_t *sem;
} t_data;

/* void *test_semapho(void *arg)
{
	t_data *data;
	data = (t_data *)arg;

	printf("ok");
	for (int i = 0; i < 100000; i++)
	{
		sem_wait(data->sem);
		data->count++;
		//printf("sem = %d\n", *data->sem);
		sem_post(data->sem);
	}
	return (NULL);
} */

void count(sem_t *sem, int i)
{
	int count = 0;
	while (count < 10)
	{
		sem_wait(sem);
		count++;
		sleep(2);
		printf("I'm %d count = %d\n", i, count);
		sem_post(sem);
	}
}

int main(void)
{
	
	//pthread_t thread[2];
	pid_t pid;
	t_data data;
	int status;

	data.count = 0;
	//sem_unlink("/fork");
	data.sem = sem_open("/fork", O_CREAT, 0600, 2);
	if (data.sem == SEM_FAILED)
		perror("sem_open");
	int i = 0;
	while (i++ < 2)
	{
		printf("ok");
		pid = fork();
		if (pid == 0)
		{
			count(data.sem, i);
			exit(1);
		}
	}
	waitpid(-1, &status, 0);
	/* pthread_create(&thread[0], NULL, test_semapho, (void *)&data);
	pthread_create(&thread[1], NULL, test_semapho, (void *)&data); */
	//pthread_create(&thread[2], NULL, test_semapho, (void *)&data);

	/* pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL); */
	//pthread_join(thread[2], NULL);
	sem_close(data.sem);
	sem_unlink("/fork");
	//printf("%d\n", data.count);
	return (0);
}
