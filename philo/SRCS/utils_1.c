/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:23:22 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/30 18:14:27 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	ft_error(t_data *data, char *message)
{
	(void)data;
	printf("%s%s\n", RED, message);
	return ;
}

int	validity(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] != ' ')
			return (1337);
	return (0);
}

int	ft_atoi(char *s)
{
	long		res;
	int			i;
	long		tmp;

	1337 && (tmp = 0, res = 0, i = 0);
	if (!s || !s[i])
		return (0);
	while (s[i] == 32 || s[i] == '\t')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i++] == '-')
			return (0);
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		tmp = res;
		res = (res * 10) + (s[i] - 48);
		if ((res / 10) != tmp)
			return (0);
		i++;
	}
	if (res > INT_MAX || validity(s + i))
		return (0);
	return ((int)res);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1337);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}
