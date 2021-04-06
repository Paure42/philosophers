/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:19:37 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:19:39 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	drop_fork(t_philo *philo)
{
	sem_post(philo->values->sem_forks);
}

void	taking_forks(t_philo *philo)
{
	sem_wait(philo->values->sem_fork_checking);
	sem_wait(philo->values->sem_forks);
	print_state(philo, philo->str_philo, 1);
	print_state(philo, philo->str_philo, 1);
	sem_post(philo->values->sem_fork_checking);
}
