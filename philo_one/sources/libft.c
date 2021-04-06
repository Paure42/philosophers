/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:36:07 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:36:08 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int			ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s || s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	p;

	n = 0;
	i = 0;
	p = 1;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\t'
			|| str[i] == ' ' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		n = -n;
		p = -1;
	}
	else if (str[i] != '+')
		i--;
	while (str[++i] >= '0' && str[i] <= '9')
		n = n * 10 + (str[i] - '0');
	return (n * p);
}

void		ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
