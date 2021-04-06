/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:22:02 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:22:04 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

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

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*dest;

	i = 0;
	dest = 0;
	while (s1[i] != 0)
		i++;
	if (!(dest = malloc((i + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = -1;
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return ((char*)s1);
	else if (!s1 && !s2)
		return (0);
	i = ft_strlen(s1) + ft_strlen(s2);
	if (i <= 0 || !(str = malloc((i + 1) * sizeof(*str))))
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++n])
	{
		str[i] = s2[n];
		i++;
	}
	str[i] = 0;
	return (str);
}
