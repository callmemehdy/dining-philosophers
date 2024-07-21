/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:21:53 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/21 14:13:39 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	f_a_r(t_data *data)
{
	if (data)
	{
		if (data->forks)
			(free(data->forks), data->forks = NULL);
		if (data->philos)
			(free(data->philos), data->philos = NULL);
		free(data);
		data = NULL;
	}
}

int	init_m(t_data *data)
{
	if (pthread_mutex_init(&data->muting, NULL))
		return (ft_error(data, "printMutex error"), 1336);
	if (pthread_mutex_init(&data->monilock, NULL))
		return (ft_error(data, "monilock mutex init!"), 1337);
	if (pthread_mutex_init(&data->reading, NULL))
		return (ft_error(data, "monilock mutex init!"), 1337);
	if (pthread_mutex_init(&data->lock, NULL))
		return (ft_error(data, "sleeplock mutex init!"), 1337);
	return (0);
}

int	destroying(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->howmanyphilos)
		if (pthread_mutex_destroy(&data->forks[i]))
			return (1339);
	if (pthread_mutex_destroy(&data->muting))
		return (1340);
	if (pthread_mutex_destroy(&data->monilock))
		return (1341);
	if (pthread_mutex_destroy(&data->reading))
		return (1342);
	if (pthread_mutex_destroy(&data->lock))
		return (1);
	return (0);
}

int	waiting(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->howmanyphilos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
		{
			ft_error(data, "..while joining threads..");
			return (1338);
		}
	}
	return (0);
}

int	preventing_headach(t_data *data)
{
	if (data->dtime <= 60)
		return (1);
	else if (data->stime <= 60)
		return (1);
	else if (data->etime <= 60)
		return (1);
	else if (data->howmanyphilos > 199)
		return (1);
	return (0);
}
