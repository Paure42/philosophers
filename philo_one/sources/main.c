/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:36:21 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:36:22 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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
	return (check_values(values, argc));
}

int			parse_values(t_values *values, char **argv, int argc)
{
	values->list_eat = NULL;
	if (parse_args(values, argv, argc) == -1)
		return (clear_values(values, -1, 0));
	values->even_checking = true;
	values->odd_checking = false;
	values->last_checking = false;
	values->exit = false;
	values->count_even = 0;
	values->count_odd = 0;
	if ((values->nphilo % 2) == 0)
	{
		values->neven = values->nphilo / 2;
		values->nodd = (values->nphilo / 2) - 1;
	}
	else
	{
		values->neven = values->nphilo / 2;
		values->nodd = values->nphilo / 2;
	}
	return (init_values(values));
}

int			main(int argc, char **argv)
{
	t_values		values;
	int				ret;

	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			ft_putstr_fd("not enough arguments\n", 2);
		else if (argc > 6)
			ft_putstr_fd("too many arguments\n", 2);
		return (-1);
	}
	if (parse_values(&values, argv, argc) == -1)
		return (-1);
	ret = ft_philo_one(&values);
	clear_values(&values, ret, 4);
	return (ret);
}
