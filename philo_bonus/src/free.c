/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:52:52 by sho               #+#    #+#             */
/*   Updated: 2022/10/06 19:48:19 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo_bonus.h"

void	free_all(t_info *info)
{
	int	i;

	i = 0;
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
