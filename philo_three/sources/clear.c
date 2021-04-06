/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:19:23 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:19:24 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int		close_semaphore(t_values *values)
{
	sem_close(values->sem_speak);
	sem_unlink("sem_speak");
	sem_close(values->sem_fork_checking);
	sem_unlink("sem_fork_checking");
	sem_close(values->sem_death);
	sem_unlink("sem_death");
	sem_close(values->sem_check_death);
	sem_unlink("sem_check_death");
	sem_close(values->sem_forks);
	sem_unlink("sem_forks");
	sem_close(values->sem_eat_count_all);
	sem_unlink("sem_eat_count_all");
	return (-1);
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

int		clear_philo(t_philo **philo, int nphilo)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < nphilo)
	{
		sem_close(philo[i]->sem_eating);
		temp = sem_name(i);
		sem_unlink(temp);
		if (temp)
			free(temp);
		if (philo[i])
		{
			free(philo[i]->str_philo);
			free(philo[i]);
		}
		i++;
	}
	free(philo);
	return (-1);
}
