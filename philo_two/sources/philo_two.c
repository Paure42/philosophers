/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:11:26 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 13:11:27 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void		thread_loop(t_philo *philo)
{
	while (1 && philo->values->exit == false)
	{
		taking_forks(philo);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
}

void		*manage_threads(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	gettimeofday(&philo->eat_start_time, NULL);
	philo->eat_count = 0;
	if (pthread_create(&philo->death_t, NULL,
		&is_starving, philo) != 0)
	{
		philo->values->exit = true;
		return (NULL);
	}
	thread_loop(philo);
	pthread_join(philo->death_t, NULL);
	return (NULL);
}

t_philo		**malloc_tab(t_values *values)
{
	int		count;
	t_philo	**philo;

	count = 0;
	if (!(philo = malloc(values->nphilo * sizeof(t_philo*))))
		return (NULL);
	while (count < values->nphilo)
	{
		if (!(philo[count] = malloc(sizeof(t_philo))))
			return (NULL);
		count++;
	}
	return (philo);
}

void		check_neating(t_values *values)
{
	int		i;

	i = 0;
	if (values->neating != -1)
	{
		while (1 && values->exit == false)
		{
			if (i == values->nphilo)
			{
				sem_wait(values->sem_speak);
				write(1, "All philosophers have finished to eat.\n", 39);
				sem_post(values->sem_speak);
				values->exit = true;
				break ;
			}
			sem_wait(values->sem_eat_count_all);
			i++;
		}
	}
}

int			ft_philo_two(t_values *values)
{
	int				count;
	t_philo			**philo;

	count = 0;
	if ((philo = malloc_tab(values)) == NULL)
		return (-1);
	if (init_philosophers(philo, values) == NULL)
		return (clear_philo(philo, values->nphilo));
	while (count < values->nphilo)
	{
		if (pthread_create(&philo[count]->philosopher,
			NULL, manage_threads, philo[count]) != 0)
		{
			values->exit = true;
			break ;
		}
		usleep(1000);
		count++;
	}
	check_neating(values);
	while (--count > -1)
		pthread_join(philo[count]->philosopher, NULL);
	clear_philo(philo, values->nphilo);
	return (0);
}
