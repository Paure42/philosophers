/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:20:53 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:20:54 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int			check_values(t_values *values, int argc)
{
	if (values->nphilo < 2)
		return (exit_failure(1));
	else if (values->timetodie < 1)
		return (exit_failure(2));
	else if (values->timetoeat < 1)
		return (exit_failure(3));
	else if (values->timetosleep < 1)
		return (exit_failure(4));
	else if (values->neating < 1 && argc == 6)
		return (exit_failure(5));
	return (0);
}

int			parse_args(t_values *values, char **argv, int argc)
{
	values->nphilo = ft_atoi(argv[1]);
	values->timetodie = ft_atoi(argv[2]);
	values->timetoeat = ft_atoi(argv[3]);
	values->timetosleep = ft_atoi(argv[4]);
	if (argc == 6)
		values->neating = ft_atoi(argv[5]);
	else
		values->neating = ft_atoi("-1");
	values->exit = false;
	return (check_values(values, argc));
}

int			parse_values(t_values *values, char **argv, int argc)
{
	if (parse_args(values, argv, argc) == -1)
		return (-1);
	return (init_values(values));
}

int			main(int argc, char **argv)
{
	t_values		values;
	int				ret;

	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			ft_putstr_fd("Error: not enough arguments\n", 2);
		else if (argc > 6)
			ft_putstr_fd("Error: too many arguments\n", 2);
		return (-1);
	}
	if (parse_values(&values, argv, argc) == -1)
		return (close_semaphore(&values));
	ret = ft_philo_two(&values);
	close_semaphore(&values);
	return (ret);
}
