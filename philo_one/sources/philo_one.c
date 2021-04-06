/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:36:35 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:36:36 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void		thread_loop(t_philo *philo)
{
	while (1)
	{
		if (philo->values->exit == true)
			break ;
		taking_forks(philo);
		is_eating(philo);
		if ((philo->is_last == 1 &&
			philo->eat_count == philo->values->neating
			&& philo->values->neating != -1))
		{
			print_state(philo, philo->str_philo, 5);
			philo->values->exit = true;
		}
		is_sleeping(philo);
		is_thinking(philo);
	}
}

void		*manage_threads(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	gettimeofday(&philo->eat_start_time, NULL);
	philo->eat_count = 0;
	philo->hold_fork_right = 0;
	philo->hold_fork_left = 0;
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

t_philo		**malloc_tab(t_philo **philo, t_values *values)
{
	int count;

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

int			ft_philo_one(t_values *values)
{
	int				count;
	t_philo			**philo;

	count = 0;
	philo = NULL;
	if ((philo = malloc_tab(philo, values)) == NULL)
		return (-1);
	if (init_philosophers(philo, values) == NULL)
		return (clear_philo(philo, values->nphilo));
	gettimeofday(&values->sim_start_time, NULL);
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
	while (--count > -1)
		pthread_join(philo[count]->philosopher, NULL);
	clear_philo(philo, values->nphilo);
	return (0);
}
