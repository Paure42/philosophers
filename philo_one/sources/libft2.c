/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:36:13 by paure             #+#    #+#             */
/*   Updated: 2021/01/25 14:36:14 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (!(str = malloc(count * size)))
		return (0);
	str = memset(str, 0, count * size);
	return (str);
}

char		*ft_strcat(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL || !s1 || !s2)
		return (s1);
	while (s1[i])
		i++;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = 0;
	return (s1);
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

int			ft_countnumbers(int n)
{
	int i;

	if (n < 0)
		i = 1;
	else if (n == 0)
		i = 1;
	else
		i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		k;
	int		negatif;

	if (n == -2147483648)
		return (str = ft_strdup("-2147483648"));
	k = ft_countnumbers(n) + 1;
	if (!(str = ft_calloc(k, sizeof(str))))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
		negatif = 0;
	}
	else
		negatif = -1;
	k--;
	while (--k > negatif)
	{
		str[k] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
