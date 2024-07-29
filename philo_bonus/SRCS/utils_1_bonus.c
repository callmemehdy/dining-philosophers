/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:39:09 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/21 14:06:45 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

int	p_error(char *message, int status)
{
	printf(YLW"%s\n", message);
	return (exit(status), status);
}

int	ft_atoi(char *s)
{
	long		res;
	int			i;
	long		tmp;

	1337 && (tmp = 0, res = 0, i = 0);
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-' || !(s[i] >= '0' && s[i] <= '9'))
			p_error("Invalid input", EXIT_FAILURE);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		tmp = res;
		res = (res * 10) + (s[i] - 48);
		if ((res / 10) != tmp)
			p_error("Invalid input", EXIT_FAILURE);
		i++;
	}
	if (s[i] && !(s[i] >= '0' && s[i] <= '9'))
		p_error("Invalid input", EXIT_FAILURE);
	return ((int)res);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		p_error("gettimeofday failed\n", EXIT_FAILURE);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / (size_t)1000));
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

void	printing(t_philo *philo, char *message)
{
	int		id;
	size_t	start;

	sem_wait(philo -> data -> stop);
	start = philo -> data ->simul_beg;
	id = philo -> id;
	printf("%zu %d %s", get_time() - start, id, message);
	sem_post(philo -> data -> stop);
}
