/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:19:09 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:19:10 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void		is_sleeping(t_philo *philo)
{
	gettimeofday(&philo->sleep_start_time, NULL);
	print_state(philo, philo->str_philo, 3);
	while (get_timer(philo->sleep_start_time) < philo->values->timetosleep)
		continue ;
}

void		is_thinking(t_philo *philo)
{
	print_state(philo, philo->str_philo, 4);
}

void		*is_starving(void *args)
{
	t_philo		*philo;

	philo = (t_philo*)args;
	while (1)
	{
		sem_wait(philo->sem_eating);
		philo->sim_time_death = get_sim_time(philo);
		philo->eat_timer = get_timer(philo->eat_start_time);
		if (philo->eat_timer >= philo->values->timetodie)
		{
			print_death(philo, philo->str_philo, philo->sim_time_death);
			philo->values->exit = true;
			sem_post(philo->values->sem_eat_count_all);
			break ;
		}
		sem_post(philo->sem_eating);
		usleep(1000);
	}
	sem_post(philo->sem_eating);
	return (NULL);
}
