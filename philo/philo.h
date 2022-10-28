/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:37:58 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/06 20:38:42 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>

typedef struct t_args
{
	int				time2die;
	int				time2sleep;
	int				time2eat;
	int				n;
	int				number_of_cycles;
	int				end;
	long long		start_time;
	pthread_t		*thread_id;
	pthread_mutex_t	die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check;
	pthread_mutex_t	pr;
	struct t_philo	*ph;
}t_args;

typedef struct t_philo
{
	int				id;
	t_args			*args;
	long long		la_eat;
	int				left_fork;
	int				right_fork;
	int				d;
	int				eat;
	pthread_mutex_t	eating;
	pthread_mutex_t	*forks;
}t_philo;

int			ft_isdigit(char *arg);
int			ft_checkarg(char **argv);
int			ft_check_pos_args(t_args *args);
long		ft_atoi(char *s);
void		ft_init_args(t_args *args, int argc, char **argv);
long long	ft_time(long long l);
int			ft_check_second_part(int argc, char **argv);
t_philo		*ft_init_philo(t_args *args);
void		*ft_calloc(size_t n, size_t size);
void		ft_sleep(long long t);
void		eat(t_philo *p);
long long	stat_time(long long t);
void		*monitoring(void *arg);
void		ft_print(int v, t_philo p);
int			delite(t_philo *p);
void		end(t_philo *p);
int			monitoring2(t_philo *p);
void		*philo_run(void *arg);
int			ft_create_t(t_args *args, t_philo *p);
int			calc_time2(int te, int ts, int n);
void		ft_init_philo2(t_philo *p, int i);
void		*ft_init_philo3(t_philo *p);
int			init_mutex(t_args *args);

#endif