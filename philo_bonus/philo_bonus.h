/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:38:26 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/06 21:19:36 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct t_args
{
	unsigned long			time2die;
	int						time2sleep;
	int						time2eat;
	int						number;
	int						nc;
	long long				start_time;
	int						pi;
	sem_t					*forks;
	sem_t					*pr;
	sem_t					*check;
	struct t_philo			*philo;
}t_args;

typedef struct timeval	t_timeval;

typedef struct t_philo
{
	int				id;
	pid_t			pid;
	t_args			*args;
	long long		la_eat;
	int				d;
	int				cn;
	t_timeval		last_eat;
	pthread_t		m_id;
}t_philo;

int				ft_isdigit(char *arg);
long long		ft_time(long long l);
void			*ft_calloc(size_t n, size_t size);
long			ft_atoi(char *s);
void			ft_check_o(t_args *args);
void			start(t_args *args);
void			ft_print(int v, t_philo p, t_args *a);
void			ft_sleep(long long t);
unsigned long	get_time(t_timeval time);
void			delite(t_args *a, t_philo *p);
void			go_philo(t_philo *p, t_args *args);
void			process(t_args *args, int i);
void			ft_init_args(t_args *args, int argc, char **argv);
void			ft_check_args(char **argv, int argc);
t_philo			*ft_init_philo(t_args *args);
void			*die_checker(void *arg);

#endif