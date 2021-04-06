/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:22:15 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:22:17 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

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

	sem_wait(philo->values->sem_speak);
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
	if (philo->exit == false)
		write(1, to_print, ft_strlen(to_print));
	if (state != -1)
		sem_post(philo->values->sem_speak);
}

void			print_death(t_philo *philo, char *str_philo,
							long int death_time)
{
	char	to_print[100];
	char	*str_sim_time;

	sem_wait(philo->values->sem_speak);
	to_print[0] = 0;
	str_sim_time = ft_itoa(death_time);
	ft_strcat(to_print, str_sim_time);
	ft_strcat(to_print, " ms ");
	ft_strcat(to_print, str_philo);
	ft_strcat(to_print, " \033[0;31mdied\033[0;37m\n");
	free(str_sim_time);
	if (philo->exit == false)
		write(1, to_print, ft_strlen(to_print));
}
