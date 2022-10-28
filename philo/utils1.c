/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:38:07 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/06 19:32:37 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_checkarg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(char *s)
{
	long	i;
	int		x;
	int		a;

	x = 0;
	i = 0;
	a = 1;
	if (s[0] == '-')
	{
		a = -1;
		x++;
	}
	if (s[0] == '+')
		x++;
	while (s[x])
	{
		i = i * 10;
		i += s[x++] - '0';
	}
	return (i * a);
}

long long	ft_time(long long l)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	l = 1;
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_check_pos_args(t_args *args)
{
	if (args->time2sleep <= 0 || args->time2die <= 0 || args->n <= 0
		|| args->time2sleep <= 0)
	{
		if (args->forks)
			free(args->forks);
		if (args->thread_id)
			free(args->thread_id);
		write(2, "wrong argument\n", 22);
		return (0);
	}
	return (1);
}
