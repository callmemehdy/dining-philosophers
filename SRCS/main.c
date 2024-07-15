/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:58 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/15 15:16:25 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	size_t	elapsed;
	size_t	lastmeal;

	if (philo->isfull)
		return (0);
	lastmeal = philo->lastmeal_time;
	elapsed = get_time() - lastmeal;
	if (elapsed >= philo->data->dtime ||
		philo->data->allfull == philo->data->mealsnum)
		return (1);
	return (0);
}

void	*monitoring(void *dt)
{
	int			i;
	t_data		*data;

	data = (t_data *)dt;
	while (data->isend == 0)
	{
		i = -1;
		while (++i < data->howmanyphilos && !data->isend)
		{
			if (philo_is_dead(&data->philos[i]))
			{
				printf("%zu %d died\n", get_time() - data->simul_beg, data->philos[i].id);
				pthread_mutex_lock(&data->monilock);
				data->isend = 1;
				pthread_mutex_unlock(&data->monilock);
			}
			if (data->philos[i].isfull)
				data->allfull++;
		}
		
	}
	return NULL;
}

int main(int ac, char **av)
{
	t_data *data;

	if (ac != 6)
		return (ft_error(NULL, "Usage: ./program [] [] [] [] []"), 1334);
	data = stuffing(av);
	if (!data)
		return (ft_error(NULL, "Error 001"), 1335);
	data->philos = NULL;
	if (pthread_mutex_init(&data->print, NULL))
		return (ft_error(data, "printMutex error"), 1336);
	if (pthread_mutex_init(&data->monilock, NULL))
		return (ft_error(data, "monilock mutex init!"), 1337);
	creating(data);
	if(simulation(data))
		return (ft_error(data, "...Error in simulation..."), 1338);
}
