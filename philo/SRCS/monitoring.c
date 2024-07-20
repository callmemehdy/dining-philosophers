/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:25:16 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/20 17:03:59 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	if (philo->isfull)
		return (0);
	pthread_mutex_lock(&philo->data->reading);
	if (philo->meals_eaten == philo->meals && philo->data->mealsnum > 0)
	{
		philo->isfull = 1;
		pthread_mutex_unlock(&philo->data->reading);
		return (2);
	}
	if ((get_time() - philo->lastmeal_time > philo->data->dtime)
		&& !philo->isfull)
	{
		pthread_mutex_unlock(&philo->data->reading);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->reading);
	return (0);
}

int	qosos_ending(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->howmanyphilos)
		if (!data->philos[i].isfull)
			return (0);
	return (1);
}

int	checking(t_data *data, int i)
{
	if (philo_is_dead(&data->philos[i]) == 1)
	{
		pthread_mutex_lock(&data->monilock);
		data->isend = 1;
		data->philos[i].isdead = 1;
		if (data->philos[i].isdead)
		{
			printf("%zu %d died\n", get_time() - data->simul_beg,
				data->philos[i].id);
			pthread_mutex_unlock(&data->monilock);
			return (0);
		}
		pthread_mutex_unlock(&data->monilock);
		return (0);
	}
	return (1);
}

int	monitoring(t_data *data)
{
	int			i;

	while (1)
	{
		i = -1;
		while (++i < data->howmanyphilos)
			if (!checking(data, i))
				return (0);
		pthread_mutex_lock(&data->muting);
		if (qosos_ending(data))
		{
			data->isend = 1;
			pthread_mutex_unlock(&data->muting);
			return (0);
		}
		pthread_mutex_unlock(&data->muting);
	}
	return (0);
}
