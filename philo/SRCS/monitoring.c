/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:25:16 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/30 19:22:59 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	qosos_ending(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->howmanyphilos)
		if (!data->philos[i].isfull)
			return (0);
	data->isend = 1;
	return (1);
}

int	checking(t_data *data, int i)
{
	t_philo *philo;


	philo = &data->philos[i];
	if (!philo->isfull && (long)get_time() - (long)philo->lastmeal_time > (long)philo->data->dtime)
	{
		// pthread_mutex_lock(&data->lock);
		caniprint(data, &data->philos[i], "died");
		// pthread_mutex_unlock(&data->lock);
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
		if (qosos_ending(data))
			return (0);
	}
	return (0);
}
