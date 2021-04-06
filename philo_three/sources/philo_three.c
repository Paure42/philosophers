/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:19:46 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:19:47 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void		thread_loop(t_philo *philo)
{
	while (1)
	{
		taking_forks(philo);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
}

void		manage_threads(t_philo *philo)
{
	gettimeofday(&philo->eat_start_time, NULL);
	philo->eat_count = 0;
	if (pthread_create(&philo->death_t, NULL,
		&is_starving, philo) != 0)
		exit(0);
	pthread_detach(philo->death_t);
	thread_loop(philo);
	exit(3);
}

t_philo		**malloc_tab(t_values *values)
{
	int		count;
	t_philo	**philo;

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

void		check_neating(t_values *values)
{
	int		i;

	i = 0;
	values->pid_check_neating = fork();
	if (values->pid_check_neating == 0 && values->neating != -1)
	{
		while (1)
		{
			if (i == values->nphilo)
			{
				sem_post(values->sem_death);
				sem_wait(values->sem_speak);
				write(1, "All philosophers have finished to eat.\n", 39);
				sem_post(values->sem_speak);
				break ;
			}
			sem_wait(values->sem_eat_count_all);
			i++;
		}
	}
}

int			ft_philo_three(t_values *values)
{
	int				count;
	t_philo			**philo;

	count = 0;
	if ((philo = malloc_tab(values)) == NULL)
		return (-1);
	if (init_philosophers(philo, values) == NULL)
		return (clear_philo(philo, values->nphilo));
	while (count < values->nphilo)
	{
		philo[count]->philosopher = fork();
		if (philo[count]->philosopher < 0)
			break ;
		else if (philo[count]->philosopher == 0)
			manage_threads(philo[count]);
		usleep(1000);
		count++;
	}
	check_neating(values);
	sem_wait(values->sem_death);
	while (--count > -1)
		kill(philo[count]->philosopher, SIGKILL);
	kill(values->pid_check_neating, SIGKILL);
	clear_philo(philo, values->nphilo);
	return (0);
}
