/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:38:10 by tpeggie           #+#    #+#             */
/*   Updated: 2022/07/06 20:38:09 by tpeggie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t n, size_t size)
{
	char			*s;
	size_t			total;
	size_t			i;

	if (size && SIZE_MAX / size < n)
		return (NULL);
	total = n * size;
	s = malloc(total);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (total--)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

void	ft_sleep(long long t)
{
	long long	b;

	b = ft_time(0);
	while (ft_time(0) < (b + t))
	{
		usleep(10);
	}
}

long long	stat_time(long long t)
{
	return (ft_time(0) - t);
}

void	ft_print(int v, t_philo p)
{
	int	x;

	pthread_mutex_lock(&p.args->pr);
	x = p.id + 1;
	if (v == 1)
		printf("%lld %i has taken a fork\n", ft_time(0) - p.args->start_time, x);
	if (v == 2)
		printf("%lld %i is eating\n", ft_time(0) - p.args->start_time, x);
	if (v == 3)
		printf("%lld %i is thinking\n", ft_time(0) - p.args->start_time, x);
	if (v == 4)
		printf("%lld %i is sleeping\n", ft_time(0) - p.args->start_time, x);
	if (v == 5)
		printf("%lld %i died\n", ft_time(0) - p.args->start_time, x);
	pthread_mutex_unlock(&p.args->pr);
}

int	delite(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->args->n)
	{
		pthread_mutex_destroy(&p[i].eating);
		pthread_mutex_destroy(&p->args->forks[i]);
	}
	free(p->args->forks);
	free(p->args->thread_id);
	free(p->args);
	pthread_mutex_destroy(&p->args->check);
	pthread_mutex_destroy(&p->args->die);
	pthread_mutex_destroy(&p->args->pr);
	free(p);
	return (0);
}
