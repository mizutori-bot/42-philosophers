/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:01:09 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:35 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long int get_current_time_in_usec(void)
{
	struct timeval mytime;
	
	gettimeofday(&mytime, NULL);
	return((mytime.tv_sec * 1000000) + mytime.tv_usec);
}

long long int	get_elapsed_time(t_info *info)
{
	return (get_current_time_in_ms() - info->start_time);
}
