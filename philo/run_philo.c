/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:32:28 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/06 21:18:54 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring2(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->args->n)
	{
		pthread_mutex_lock(&p->args->check);
		if (p->args->time2die < (ft_time(0) - p[i].la_eat) * 1000)
		{
			pthread_mutex_unlock(&p->args->check);
			end(p);
			ft_print(5, p[i]);
			pthread_mutex_lock(&p->args->pr);
			return (1);
		}
		pthread_mutex_unlock(&p->args->check);
		pthread_mutex_lock(&p->eating);
		if (p->eat == p->args->number_of_cycles + 1)
		{
			end(p);
			pthread_mutex_lock(&p->args->pr);
			return (1);
		}
		pthread_mutex_unlock(&p->eating);
	}
	return (0);
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->forks[p->left_fork]);
	ft_print(1, *p);
	pthread_mutex_lock(&p->forks[p->right_fork]);
	ft_print(1, *p);
	ft_print(2, *p);
	pthread_mutex_lock(&p->args->check);
	p->la_eat = ft_time(0);
	pthread_mutex_unlock(&p->args->check);
	ft_sleep(p->args->time2eat / 1000);
	pthread_mutex_lock(&p->eating);
	p->eat++;
	pthread_mutex_unlock(&p->eating);
	pthread_mutex_unlock(&p->forks[p->right_fork]);
	pthread_mutex_unlock(&p->forks[p->left_fork]);
	ft_print(4, *p);
	ft_sleep(p->args->time2eat / 1000);
	ft_print(3, *p);
}

void	end(t_philo *p)
{
	pthread_mutex_lock(&p->args->die);
	p->args->end = 4;
	pthread_mutex_unlock(&p->args->die);
}

void	*monitoring(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (monitoring2(p) == 1)
			return (0);
		ft_sleep(10);
	}
}
