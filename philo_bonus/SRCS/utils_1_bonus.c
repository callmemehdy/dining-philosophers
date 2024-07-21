/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:39:09 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/21 06:39:33 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

void	ft_error(t_data *data, char *message)
{
	if (data)
		free(data);
	printf("%s%s\n", RED, message);
	return ;
}

int	ft_atoi(char *s)
{
	long		res;
	int			i;
	long		tmp;

	1337 && (tmp = 0, res = 0, i = 0);
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			return (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		tmp = res;
		res = (res * 10) + (s[i] - 48);
		if ((res / 10) != tmp)
			return (-1);
		i++;
	}
	return ((int)res);
}

size_t	get_time(void)
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
