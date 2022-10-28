/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:37:54 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/08 22:06:03 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_second_part(int argc, char **argv)
{
	int	fd;

	fd = 2;
	if (ft_checkarg(argv) == 1)
	{
		write(fd, "wrong argument\n", 15);
		return (0);
	}
	if (argc > 6 || argc < 5)
	{
		write(fd, "wrong number of arguments\n", 26);
		return (0);
	}
	return (1);
}

void	ft_init_args(t_args *args, int argc, char **argv)
{
	int				i;

	i = -1;
	args->n = ft_atoi(argv[1]);
	args->forks = ft_calloc(sizeof (pthread_mutex_t), args->n);
	args->time2die = 1000 * ft_atoi(argv[2]);
	args->time2eat = 1000 * ft_atoi(argv[3]);
	args->time2sleep = 1000 * ft_atoi(argv[4]);
	args->start_time = ft_time(0);
	args->thread_id = malloc(sizeof(pthread_t) * (args->n));
	if (!args->forks || !args->thread_id)
		args->n = 0;
	if (argc == 6)
		args->number_of_cycles = ft_atoi(argv[5]);
	while (++i < args->n)
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			args->n = 0;
}

void	*philo_run(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	if ((p->id + 1) % 2 == 0)
		usleep(100);
	while (1)
	{
		if (p->args->end == 4)
			break ;
		eat(p);
	}
	return (0);
}

int	ft_create_t(t_args *args, t_philo *p)
{
	int	i;

	i = 0;
	while (i < args->n)
	{
		if (pthread_create(&args->thread_id[i], 0, philo_run, &p[i]))
			return (0);
		if (pthread_detach(args->thread_id[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_args			*args;
	t_philo			*philo;

	if (ft_check_second_part(argc, argv) != 1)
		return (0);
	args = malloc(sizeof (t_args));
	if (!args || init_mutex(args))
		return (0);
	ft_init_args(args, argc, argv);
	if (ft_check_pos_args(args) == 0)
		return (1);
	philo = ft_init_philo(args);
	args->ph = philo;
	if (!philo)
	{
		free(args->thread_id);
		free(args);
		free(args->forks);
		return (0);
	}
	if (!ft_create_t(args, philo))
		return (delite(philo));
	monitoring(philo);
	delite(philo);
	return (0);
}
