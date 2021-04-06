/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:36:40 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:36:41 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

long int		get_timer(struct timeval start_time)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- (start_time.tv_sec * 1000 + start_time.tv_usec / 1000));
}

long int		get_sim_time(t_philo *philo)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- (philo->values->sim_start_time.tv_sec * 1000
			+ philo->values->sim_start_time.tv_usec / 1000));
}

void			print_state(t_philo *philo, char *str_philo, int state)
{
	char	to_print[100];
	char	*str_sim_time;

	pthread_mutex_lock(&philo->values->speak);
	to_print[0] = 0;
	str_sim_time = ft_itoa(get_sim_time(philo));
	ft_strcat(to_print, str_sim_time);
	ft_strcat(to_print, " ms ");
	ft_strcat(to_print, str_philo);
	if (state == 1)
		ft_strcat(to_print, " has taken a fork\n");
	else if (state == 2)
		ft_strcat(to_print, " \033[0;34mis eating\033[0;37m\n");
	else if (state == 3)
		ft_strcat(to_print, " is sleeping\n");
	else if (state == 4)
		ft_strcat(to_print, " is thinking\n");
	else
		ft_strcat(to_print, " \033[0;31mdied\033[0;37m\n");
	free(str_sim_time);
	if (state != 5 && philo->values->exit == false)
		write(1, to_print, ft_strlen(to_print));
	else if (philo->values->exit == false)
		write(1, "All philosophers have finished to eat\n", 38);
	pthread_mutex_unlock(&philo->values->speak);
}

int				*reinit_list_eat(int *list_eat, int n, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		list_eat[i] = n;
		i++;
	}
	return (list_eat);
}
