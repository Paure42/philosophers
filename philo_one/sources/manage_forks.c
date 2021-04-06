/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:36:28 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:36:29 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	drop_fork(t_philo *philo)
{
	philo->hold_fork_right = 0;
	philo->hold_fork_left = 0;
}

void	taking_fork_left(t_philo *philo)
{
	if (philo->values->exit == 0)
	{
		print_state(philo, philo->str_philo, 1);
		philo->hold_fork_left = 1;
	}
}

void	taking_fork_right(t_philo *philo)
{
	if (philo->values->exit == 0)
	{
		print_state(philo, philo->str_philo, 1);
		philo->hold_fork_right = 1;
	}
}

int		check_can_eat(int *list_eat, int n, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (list_eat[i] == n)
			return (0);
		i++;
	}
	return (1);
}

void	taking_forks(t_philo *philo)
{
	while (philo->values->exit == false)
	{
		pthread_mutex_lock(&philo->values->fork_mutex_checking);
		if (((philo->is_even == 1 && philo->values->even_checking == true)
			|| (philo->is_odd == 1 && philo->values->odd_checking == true)
			|| (philo->is_last == 1 && philo->values->last_checking == true))
			&& check_can_eat(philo->values->list_eat, philo->current_philo,
				philo->values->neven) == 1)
		{
			taking_fork_left(philo);
			taking_fork_right(philo);
		}
		pthread_mutex_unlock(&philo->values->fork_mutex_checking);
		if (philo->hold_fork_left == 1 && philo->hold_fork_right == 1)
			break ;
		else if (philo->hold_fork_left == 1 || philo->hold_fork_right == 1)
			drop_fork(philo);
		usleep(1000);
	}
}
