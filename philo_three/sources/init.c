/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:19:31 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:19:32 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int			init_values(t_values *values)
{
	sem_unlink("sem_speak");
	sem_unlink("sem_fork_checking");
	sem_unlink("sem_death");
	sem_unlink("sem_check_death");
	sem_unlink("sem_forks");
	sem_unlink("sem_eat_count_all");
	if ((values->sem_speak =
		sem_open("sem_speak", O_CREAT |
			O_EXCL, 0644, 1)) == SEM_FAILED
		|| (values->sem_check_death = sem_open("sem_check_death", O_CREAT
			| O_EXCL, 0644, 1)) == SEM_FAILED
		|| (values->sem_death = sem_open("sem_death", O_CREAT
			| O_EXCL, 0644, 0)) == SEM_FAILED
		|| (values->sem_fork_checking = sem_open("sem_fork_checking", O_CREAT
			| O_EXCL, 0644, 1)) == SEM_FAILED
		|| (values->sem_forks = sem_open("sem_forks", O_CREAT
			| O_EXCL, 0644, values->nphilo / 2)) == SEM_FAILED
		|| (values->sem_eat_count_all = sem_open("sem_eat_count_all", O_CREAT
			| O_EXCL, 0644, 0)) == SEM_FAILED)
		return (-1);
	return (0);
}

char		*sem_name(int count)
{
	char	*ret;
	char	*temp;

	temp = ft_itoa(count);
	ret = 0;
	if (temp)
	{
		ret = ft_strjoin("philo ", temp);
		free(temp);
	}
	sem_unlink(ret);
	return (ret);
}

t_philo		**init_philosophers(t_philo **philo, t_values *values)
{
	int		count;
	char	*temp;

	count = 0;
	while (count < values->nphilo)
	{
		philo[count]->values = (void*)values;
		philo[count]->current_philo = count;
		philo[count]->eat_count = 0;
		philo[count]->str_philo = ft_itoa(count);
		philo[count]->exit = false;
		temp = sem_name(count);
		if ((philo[count]->sem_eating =
			sem_open(temp, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		{
			if (temp)
				free(temp);
			return (NULL);
		}
		if (temp)
			free(temp);
		count++;
	}
	gettimeofday(&values->sim_start_time, NULL);
	return (philo);
}
