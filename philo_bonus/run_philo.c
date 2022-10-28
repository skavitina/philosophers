/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:32:19 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/06 21:00:54 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	go_philo(t_philo *p, t_args *args)
{
	if ((p->id + 1) % 2 == 0)
		usleep(200);
	while (1)
	{
		if (p->d == args->nc && p->id == args->number - 1)
			exit(0);
		sem_wait(p->args->forks);
		ft_print(1, *p, args);
		sem_wait(p->args->forks);
		ft_print(1, *p, args);
		ft_print(2, *p, args);
		sem_wait(args->check);
		gettimeofday(&p->last_eat, NULL);
		sem_post(args->check);
		ft_sleep(args->time2eat / 1000);
		sem_post(p->args->forks);
		sem_post(p->args->forks);
		p->d++;
		ft_print(4, *p, args);
		ft_sleep(args->time2sleep / 1000);
		ft_print(3, *p, args);
	}
}

unsigned long	get_time(t_timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*die_checker(void *arg)
{
	t_args			*a;
	unsigned long	x;

	a = (t_args *)arg;
	while (1)
	{
		sem_wait(a->check);
		x = get_time(a->philo[a->pi].last_eat);
		sem_post(a->check);
		if (a->time2die < (ft_time(0) - x) * 1000)
		{
			sem_wait(a->pr);
			printf("%lld %i died\n", ft_time(0) - a->start_time, a->pi + 1);
			exit(0);
		}
		ft_sleep(10);
	}
}

void	process(t_args *args, int i)
{
	t_philo	*p;

	p = &args->philo[i];
	args->pi = i;
	if (pthread_create(&args->philo[i].m_id, 0, die_checker, args))
	{
		free(args->philo);
		free(args);
		exit(3);
	}
	if (pthread_detach(args->philo[i].m_id))
	{
		free(args->philo);
		free(args);
		exit(3);
	}
	go_philo(p, args);
	exit(3);
}

void	start(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number)
	{
		args->philo[i].pid = fork();
		if (args->philo[i].pid == -1)
			exit(3);
		if (args->philo[i].pid == 0)
			process(args, i);
		i++;
	}
}
