/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:38:22 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/06 21:20:17 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_args(t_args *args, int argc, char **argv)
{
	args->number = ft_atoi(argv[1]);
	args->time2die = ft_atoi(argv[2]) * 1000;
	args->time2eat = ft_atoi(argv[3]) * 1000;
	args->time2sleep = ft_atoi(argv[4]) * 1000;
	args->start_time = ft_time(0);
	if (argc == 6)
		args->nc = ft_atoi(argv[5]);
	ft_check_o(args);
}

void	ft_check_args(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc > 6 || argc < 5)
	{
		write(2, "Error: wrong number of argument\n", 32);
		exit(3);
	}
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 1)
		{
			write(2, "Error: wrong argument\n", 22);
			exit(3);
		}
		i++;
	}
}

t_philo	*ft_init_philo(t_args *args)
{
	int		i;
	t_philo	*p;

	p = ft_calloc(sizeof (t_philo), args->number);
	if (!p)
	{
		free(args);
		exit(3);
	}
	i = -1;
	while (++i < args->number)
	{
		p[i].id = i;
		p[i].args = args;
		if (args->nc > 0)
			p[i].d = 0;
		gettimeofday(&p[i].last_eat, NULL);
	}
	return (p);
}

void	init_sem(t_args *args)
{
	sem_unlink("forks");
	sem_unlink("pr");
	sem_unlink("check");
	args->forks = sem_open("forks", O_CREAT, S_IRWXU, args->number);
	if (args->pr == SEM_FAILED)
	{
		write(2, "semaphore error\n", 16);
		exit(3);
	}
	args->check = sem_open("check", O_CREAT, S_IRWXU, 1);
	if (args->forks == SEM_FAILED)
	{
		write(2, "semaphore error\n", 16);
		exit(3);
	}
	args->pr = sem_open("pr", O_CREAT, S_IRWXU, 1);
	if (args->pr == SEM_FAILED)
	{
		write(2, "semaphore error\n", 16);
		exit(3);
	}
}

int	main(int argc, char **argv)
{
	t_args	*args;
	int		a;
	int		i;

	ft_check_args(argv, argc);
	args = malloc(sizeof (t_args));
	if (!args)
		return (0);
	ft_init_args(args, argc, argv);
	args->philo = ft_init_philo(args);
	init_sem(args);
	args->start_time = ft_time(0);
	start(args);
	i = -1;
	waitpid(0, &a, 0);
	while (++i < args->number)
		kill(args->philo[i].pid, SIGTERM);
	delite(args, args->philo);
}
