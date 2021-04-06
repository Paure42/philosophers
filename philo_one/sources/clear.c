/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:35:45 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:35:46 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int		destroy_mutex(t_values *values, int n)
{
	if (n == 1)
		pthread_mutex_destroy(&values->speak);
	else if (n == 2)
	{
		pthread_mutex_destroy(&values->speak);
		pthread_mutex_destroy(&values->fork_mutex_checking);
	}
	else if (n == 3)
	{
		pthread_mutex_destroy(&values->speak);
		pthread_mutex_destroy(&values->fork_mutex_checking);
		pthread_mutex_destroy(&values->mutex_death);
	}
	else if (n == 4)
	{
		pthread_mutex_destroy(&values->speak);
		pthread_mutex_destroy(&values->fork_mutex_checking);
		pthread_mutex_destroy(&values->mutex_death);
		pthread_mutex_destroy(&values->eat_mutex_checking);
	}
	return (clear_values(values, -1, 0));
}

int		exit_failure(int exit)
{
	if (exit == 1)
		ft_putstr_fd("ERROR: incorrect number of philosophers\n", 2);
	else if (exit == 2)
		ft_putstr_fd("ERROR: incorrect timer to die\n", 2);
	else if (exit == 3)
		ft_putstr_fd("ERROR: incorrect timer to eat\n", 2);
	else if (exit == 4)
		ft_putstr_fd("ERROR: incorrect timer to sleep\n", 2);
	else if (exit == 5)
		ft_putstr_fd("ERROR: incorrect number of eating\n", 2);
	else if (exit == 6)
		ft_putstr_fd("ERROR: malloc failed\n", 2);
	return (-1);
}

int		clear_values(t_values *values, int ret, int mutex)
{
	if (values->list_eat != NULL)
		free(values->list_eat);
	values->list_eat = NULL;
	if (mutex != 0)
		destroy_mutex(values, mutex);
	return (ret);
}

int		clear_philo(t_philo **philo, int nphilo)
{
	int i;

	i = 0;
	while (i < nphilo)
	{
		if (philo[i])
		{
			pthread_mutex_destroy(&philo[i]->eat_mutex);
			free(philo[i]->str_philo);
			free(philo[i]);
		}
		i++;
	}
	free(philo);
	return (-1);
}
