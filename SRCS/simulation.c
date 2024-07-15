/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:38 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/15 15:40:56 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	*qosos(void *data)
{
	(void)data;
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
		// todo
	}
	else
	{
		while (++i < data->howmanyphilos)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL, qosos, &data->philos[i]))
			{
				ft_error(data, "..while creating threads..");
				return (1337);	
			}
		}
		i = -1;
		while (++i < data->howmanyphilos)
		{
			if (pthread_detach(data->philos[i].thread_id))
			{
				ft_error(data, "..while detaching threads..");
				return (1338);	
			}
		}
	}
	return (0);
}
