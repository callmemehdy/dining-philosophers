/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:38 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/16 19:06:48 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	thelastonestanding(t_data *data)
{
	mutexing(data->reading, lock);
	if (data->isend == 1)
		return (1);
	mutexing(data->reading, unlock);
	return (0);	
}

// void	eating(t_philo *philo)
// {
// 	// mutexing(philo->rfork->fork, lock);

// 	// mutexing(philo->rfork->fork, unlock);
// 	// mutexing(philo->lfork->fork, unlock);
// }

// void	sleeping(t_philo *philo)
// {
// 	// mutexing(philo->data->lock, lock);

// 	// mutexing(philo->data->lock, unlock);
// }

// void	thinking(t_philo *philo)
// {

// }

void	*qosos(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->isfull)
		return (NULL);
	if ((philo->id % 2) != 0)
		ft_usleep(10 * MS);
	while (!thelastonestanding(philo->data))
	{
		// eating meal.......
		// eating(philo);
		/// ....
		pthread_mutex_lock(&philo->rfork->fork);
		if (!philo->data->key)
			13 && (philo->data->key = 1, philo->data->simul_beg = get_time());
		printf("%zu %d has taken a fork\n", get_time() - philo->data->simul_beg, philo->id);
		pthread_mutex_lock(&philo->lfork->fork);
		printf("%zu %d has taken a fork\n", get_time() - philo->data->simul_beg, philo->id);
		printf("%zu %d is eating\n", get_time() - philo->data->simul_beg, philo->id);
		philo->meals_eaten++;
		philo->lastmeal_time = get_time();
		ft_usleep(philo->data->etime * MS);
		pthread_mutex_unlock(&philo->rfork->fork);
		pthread_mutex_unlock(&philo->lfork->fork);

		
		/// ...
		// sleeping time
		pthread_mutex_lock(&philo->data->lock);
		printf("%zu %d is sleeping\n", get_time() - philo->data->simul_beg, philo->id);
		ft_usleep(philo->data->stime * MS);
		pthread_mutex_unlock(&philo->data->lock);

		
		// thinking time
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %d is thinking\n", get_time() - philo->data->simul_beg, philo->id);
		pthread_mutex_unlock(&philo->data->print);
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
