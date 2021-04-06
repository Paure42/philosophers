/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:18:47 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:18:48 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void		is_eating(t_philo *philo)
{
	sem_wait(philo->sem_eating);
	gettimeofday(&philo->eat_start_time, NULL);
	print_state(philo, philo->str_philo, 2);
	while (get_timer(philo->eat_start_time) < philo->values->timetoeat)
		continue ;
	drop_fork(philo);
	philo->eat_count++;
	if (philo->eat_count == philo->values->neating)
		sem_post(philo->values->sem_eat_count_all);
	sem_post(philo->sem_eating);
}
