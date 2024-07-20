/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:38 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/20 17:12:08 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	thelastonestanding(t_data *data)
{
	pthread_mutex_lock(&data->reading);
	if (data->isend == 1)
	{
		pthread_mutex_unlock(&data->reading);
		return (1);
	}
	pthread_mutex_unlock(&data->reading);
	return (0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	if (!philo->data->isend && !philo->isfull)
		printf("%zu %d has taken a fork\n",
			get_time() - philo->data->simul_beg, philo->id);
	pthread_mutex_lock(philo->rfork);
	if (!philo->data->isend && !philo->isfull)
		printf("%zu %d has taken a fork\n",
			get_time() - philo->data->simul_beg, philo->id);
	if (!philo->data->isend && !philo->isfull)
		printf("%zu %d is eating\n",
			get_time() - philo->data->simul_beg, philo->id);
	philo->meals_eaten++;
	ft_usleep(philo->data->etime);
	philo->lastmeal_time = get_time();
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	*qosos(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->isfull || philo->data->isend)
		return (NULL);
	pthread_mutex_lock(&philo->data->lock);
	philo->data->allin++;
	pthread_mutex_unlock(&philo->data->lock);
	while (!thelastonestanding(philo->data))
	{
		if (!(philo->id % 2))
			ft_usleep(1);
		eating(philo);
		if (!philo->data->isend)
			printf("%zu %d is sleeping\n", get_time() - philo->data->simul_beg,
				philo->id);
		ft_usleep(philo->data->stime);
		if (!philo->data->isend)
			printf("%zu %d is thinking\n", get_time() - philo->data->simul_beg,
				philo->id);
	}
	return (NULL);
}

int	simulation(t_data *data)
{
	int			i;

	i = -1;
	if (!data->howmanyphilos)
		return (4817);
	else if (data->howmanyphilos == 1)
	{
		return (0);
	}
	else
	{
		data->simul_beg = get_time();
		while (++i < data->howmanyphilos)
		{
			data->philos[i].lastmeal_time = get_time();
			if (pthread_create(&data->philos[i].thread_id, NULL,
					qosos, &data->philos[i]))
			{
				ft_error(data, "..while creating threads..");
				return (1337);
			}
		}
	}
	return (0);
}
