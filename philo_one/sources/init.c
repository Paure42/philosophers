/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:35:58 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:35:59 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int			init_values(t_values *values)
{
	if (pthread_mutex_init(&values->speak, NULL) != 0)
		return (destroy_mutex(values, 1));
	if (pthread_mutex_init(&values->fork_mutex_checking, NULL) != 0)
		return (destroy_mutex(values, 2));
	if (pthread_mutex_init(&values->mutex_death, NULL) != 0)
		return (destroy_mutex(values, 3));
	if (pthread_mutex_init(&values->eat_mutex_checking, NULL) != 0)
		return (destroy_mutex(values, 4));
	if ((!(values->list_eat = malloc(values->neven * sizeof(int)))))
		return (clear_values(values, -1, 4));
	values->list_eat = reinit_list_eat(values->list_eat, -1, values->neven);
	return (0);
}

t_philo		**init_philosophers(t_philo **philo, t_values *values)
{
	int		count;

	count = 0;
	while (count < values->nphilo)
	{
		philo[count]->is_last = 0;
		philo[count]->is_odd = 0;
		philo[count]->is_even = 0;
		philo[count]->values = values;
		philo[count]->current_philo = count;
		if (pthread_mutex_init(&philo[count]->eat_mutex, NULL) != 0
			|| (philo[count]->str_philo = ft_itoa(count)) == NULL)
			return (NULL);
		if (count == (values->nphilo - 1))
			philo[count]->is_last = 1;
		else if (count == 0 || (count % 2) == 0)
			philo[count]->is_even = 1;
		else
			philo[count]->is_odd = 1;
		count++;
	}
	return (philo);
}
