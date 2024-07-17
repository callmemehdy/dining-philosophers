/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:23:22 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/16 18:29:22 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	ft_error(t_data *data, char *message)
{
	if (data && data->philos)
		free(data->philos);
	if (data)
		free(data);
	printf("%s%s\n", RED, message);
	return ;
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
		{
			ft_error(NULL, "Enter a valid number: 0 < N < INTMAX + 1");
			return (-1);	
		}
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		tmp = res;
		res = (res * 10) + (s[i] - 48);
		if ((res / 10) != tmp)
		{
			ft_error(NULL, "Overflow things hh.");
			return (-1);
		}
		i++;
	}
	return ((int)res);
}

size_t  get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t micros)
{
	size_t start;

	start = get_time() * MS;
	while ((get_time() * MS) - start <= micros)
	{
		usleep(150);
	}
	// todo
}

void	mutexing(t_mtx mutex, t_ops op)
{
	if (op == lock)
	{
		if (pthread_mutex_lock(&mutex))
			return ;
	}
	else if (op == init)
	{
		if (pthread_mutex_init(&mutex, NULL))
			return ;
	}
	else if (op == destroy)
	{
		if (pthread_mutex_destroy(&mutex))
			return ;
	}
	else if (op == unlock)
	{
		if (pthread_mutex_unlock(&mutex))
			return ;
	}
	else
	{
		printf("slo\n");
		exit(0);
		return ;
	}
}
