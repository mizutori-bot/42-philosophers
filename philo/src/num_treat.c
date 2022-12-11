/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_treat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:44:39 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:30 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long int	ft_atoi(const char *str)
{
	size_t			i;
	int				sig;
	long long int	num;

	i = 0;
	sig = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{	
		sig = sig * (',' - str[i]);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sig * num);
}

int	check_if_args_are_number(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_if_it_is_number(argv[i]) == -1)
			return (print_error_msg("Arguments contain not a proper number"));
		i++;
	}
	return (0);
}

int	check_if_it_is_number(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] == '\0')
		return (-1);
	while (arg[i] != '\0')
	{
		if (!ps_isdigit(arg[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	ps_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}
