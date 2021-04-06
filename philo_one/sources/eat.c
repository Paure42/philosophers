/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:35:51 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:35:53 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int			*fill_list_eat(int *list_eat, int n, int len)
{
	int i;

	i = 0;
	while (list_eat[i] != -1 && i < len)
		i++;
	list_eat[i] = n;
	return (list_eat);
}

void		eat_last(t_philo *philo)
{
	philo->values->list_eat = reinit_list_eat(philo->values->list_eat,
		-1, philo->values->neven);
	philo->values->last_checking = false;
	philo->values->even_checking = true;
}

void		eat_even(t_philo *philo)
{
	philo->values->count_even++;
	if (philo->values->count_even == philo->values->neven)
	{
		philo->values->list_eat = reinit_list_eat(philo->values->list_eat,
			-1, philo->values->neven);
		philo->values->even_checking = false;
		if (philo->values->nphilo == 2)
			philo->values->last_checking = true;
		else
			philo->values->odd_checking = true;
		philo->values->count_even = 0;
	}
}

void		eat_odd(t_philo *philo)
{
	philo->values->count_odd++;
	if (philo->values->count_odd == philo->values->nodd)
	{
		philo->values->list_eat = reinit_list_eat(philo->values->list_eat,
			-1, philo->values->neven);
		philo->values->last_checking = true;
		philo->values->odd_checking = false;
		philo->values->count_odd = 0;
	}
}

void		is_eating(t_philo *philo)
{
	if (philo->values->exit == false)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		gettimeofday(&philo->eat_start_time, NULL);
		print_state(philo, philo->str_philo, 2);
		while (get_timer(philo->eat_start_time) < philo->values->timetoeat)
			continue ;
		gettimeofday(&philo->eat_start_time, NULL);
		pthread_mutex_unlock(&philo->eat_mutex);
		drop_fork(philo);
		philo->eat_count++;
		pthread_mutex_lock(&philo->values->eat_mutex_checking);
		philo->values->list_eat = fill_list_eat(philo->values->list_eat,
			philo->current_philo, philo->values->neven);
		if (philo->is_even == 1)
			eat_even(philo);
		else if (philo->is_odd == 1)
			eat_odd(philo);
		else if (philo->is_last == 1)
			eat_last(philo);
		pthread_mutex_unlock(&philo->values->eat_mutex_checking);
	}
}
