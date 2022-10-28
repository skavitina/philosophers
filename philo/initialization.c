/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:10:50 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/06 21:20:04 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_init_philo(t_args *args)
{
	t_philo		*p;
	int			i;

	i = -1;
	p = ft_calloc(sizeof (t_philo), args->n);
	if (!p)
		return (NULL);
	while (++i < args->n)
	{
		p[i].id = i;
		p[i].la_eat = args->start_time;
		p[i].args = args;
		p[i].left_fork = i;
		p[i].right_fork = i + 1;
		p[i].eat = 0;
		p[i].forks = args->forks;
		if (args->n == 1)
			p[i].right_fork = 0;
		if (i == args->n - 1)
			ft_init_philo2(p, i);
		if (pthread_mutex_init(&p[i].eating, NULL) != 0)
			return (ft_init_philo3(p));
	}
	return (p);
}

void	ft_init_philo2(t_philo *p, int i)
{
	p[i].left_fork = i;
	p[i].right_fork = 0;
}

void	*ft_init_philo3(t_philo *p)
{
	free(p);
	return (NULL);
}

int	init_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->check, NULL) != 0)
	{
		free(args);
		return (1);
	}
	if (pthread_mutex_init(&args->pr, NULL) != 0)
	{
		free(args);
		return (1);
	}
	if (pthread_mutex_init(&args->die, NULL) != 0)
	{
		free(args);
		return (1);
	}
	return (0);
}
