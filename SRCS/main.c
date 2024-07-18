/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:58 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/18 15:33:06 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	size_t	elapsed;
	size_t	lastmeal;

	if (philo->isfull)
		return (0);
	pthread_mutex_lock(&philo->data->reading);
	lastmeal = philo->lastmeal_time;
	elapsed = get_time() - lastmeal;
	if (elapsed >= philo->data->dtime)
	{
		pthread_mutex_unlock(&philo->data->reading);
		return (1);
	}
	if (philo->meals_eaten == philo->meals)
	{
		philo->isfull = 1;
		pthread_mutex_unlock(&philo->data->reading);
		return (2);
	}
	pthread_mutex_unlock(&philo->data->reading);
	return (0);
}

int qosos_ending(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->howmanyphilos)
		if (!data->philos[i].isfull)
			return (0);
	return (1);
}

int	monitoring(void *dt)
{
	int			i;
	t_data		*data;

	data = (t_data *)dt;
	while (1)
	{
		i = -1;
		while (++i < data->howmanyphilos)
		{
			if (philo_is_dead(&data->philos[i]) == 1)
			{
				pthread_mutex_lock(&data->monilock);
				data->isend = 1;
				data->philos[i].isdead = 1;
				if (data->philos[i].isdead)
				{
					printf("%zu %d died\n", get_time() - data->simul_beg, data->philos[i].id);
					// exit(0);
					// ft_usleep(2);
					return (0);
				}
				pthread_mutex_unlock(&data->monilock);
				return (0);
			}
		}
		pthread_mutex_lock(&data->print);
		if (qosos_ending(data))
		{
			data->isend = 1;
			return 0;
		}
		pthread_mutex_unlock(&data->print);
		
	}
	return 0;
}

int main(int ac, char **av)
{
	t_data *data;

	if (ac != 6 && ac != 5)
		return (ft_error(NULL, "Usage: ./program [] [] [] [] []"), 1334);
	data = stuffing(av, ac);
	if (!data)
		return (ft_error(NULL, "Error 001"), 1335);
	data->philos = NULL;
	if (pthread_mutex_init(&data->print, NULL))
		return (ft_error(data, "printMutex error"), 1336);
	if (pthread_mutex_init(&data->monilock, NULL))
		return (ft_error(data, "monilock mutex init!"), 1337);
	if (pthread_mutex_init(&data->reading, NULL))
		return (ft_error(data, "monilock mutex init!"), 1337);
	if (pthread_mutex_init(&data->lock, NULL))
		return (ft_error(data, "sleeplock mutex init!"), 1337);
	if(creating(data))
		return(ft_error(data, "..Error in creating.."), 1338);
	if(simulation(data))
		return (ft_error(data, "...Error in simulation..."), 1339);
	if (monitoring(data))
		return (ft_error(data, "monitor failed soldier--"), 0x22);
// heeya
	// monitoring 
	// destroying
	// if (pthread_mutex_destroy(&data->print))
	// 	return (ft_error(data, "printMutex error"), 1340);
	// if (pthread_mutex_destroy(&data->monilock))
	// 	return (ft_error(data, "monilock mutex!"), 1341);
	// if (pthread_mutex_destroy(&data->reading))
	// 	return (ft_error(data, "monilock mutex!"), 1342);
	// if (pthread_mutex_destroy(&data->lock))
	// 	return (ft_error(data, "sleeplock mutex!"), 1343);
}
