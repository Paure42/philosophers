/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:35:31 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:35:39 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void		is_sleeping(t_philo *philo)
{
	if (philo->values->exit == false)
	{
		gettimeofday(&philo->sleep_start_time, NULL);
		print_state(philo, philo->str_philo, 3);
		while (get_timer(philo->sleep_start_time) < philo->values->timetosleep)
		{
			if (philo->values->exit == true)
				break ;
		}
	}
}

void		is_thinking(t_philo *philo)
{
	if (philo->values->exit == false)
		print_state(philo, philo->str_philo, 4);
}

void		*is_starving(void *args)
{
	t_philo		*philo;

	philo = (t_philo*)args;
	while (1)
	{
		if (philo->values->exit == true)
			break ;
		pthread_mutex_lock(&philo->eat_mutex);
		philo->eat_timer = get_timer(philo->eat_start_time);
		pthread_mutex_unlock(&philo->eat_mutex);
		if (philo->eat_timer >= philo->values->timetodie)
		{
			print_state(philo, philo->str_philo, -1);
			philo->values->exit = true;
			break ;
		}
		else if (philo->eat_count >= philo->values->neating &&
				philo->values->neating != -1)
			break ;
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->values->mutex_death);
	return (NULL);
}
