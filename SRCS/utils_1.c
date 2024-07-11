/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:23:22 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/01 11:42:52 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	ft_error(t_data *data, int status, char *message)
{
	if (data && data->philos)
		free(data->philos);
	if (data)
		free(data);
	printf("%s%s\n", RED, message);
	exit(status);
}
int ft_atoi(char *s)
{
	long res;
	int i;
	long tmp;

	1337 && (tmp = 0, res = 0, i = 0);
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			ft_error(NULL, EXIT_FAILURE, "Enter a valid number: 0 < N < INTMAX + 1");
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		tmp = res;
		res = (res * 10) + (s[i] - 48);
		if ((res / 10) != tmp)
			ft_error(NULL, EXIT_FAILURE, "Overflow things hh.");
		i++;
	}
	return ((int)res);
}

size_t  get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t micros)
{
	size_t start;

	start = get_time() * 1000;
	while ((get_time() * 1000) - start < micros)
	{
		usleep(150);
	}
	// todo
}