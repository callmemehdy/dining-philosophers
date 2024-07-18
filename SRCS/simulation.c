/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:38 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/18 15:35:10 by mel-akar         ###   ########.fr       */
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
	if (philo->isfull || philo->data->isend)
		return (NULL);
	while (!thelastonestanding(philo->data))
	{
		// eating meal.......
		// eating(philo);
		/// ....
		if (!(philo->id % 2))
			ft_usleep(1);
		pthread_mutex_lock(philo->lfork);
		if (!philo->data->isend)
			printf("%zu %d has taken a fork\n", get_time() - philo->data->simul_beg, philo->id);
		pthread_mutex_lock(philo->rfork);
		if (!philo->data->isend)
			printf("%zu %d has taken a fork\n", get_time() - philo->data->simul_beg, philo->id);
		philo->lastmeal_time = get_time();
		if (!philo->data->isend)
			printf("%zu %d is eating\n", get_time() - philo->data->simul_beg, philo->id);
		philo->meals_eaten++;
		ft_usleep(philo->data->etime);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);

		
		/// ...
		// sleeping time
		// pthread_mutex_lock(&philo->data->lock);
		if (!philo->data->isend)
			printf("%zu %d is sleeping\n", get_time() - philo->data->simul_beg, philo->id);
		ft_usleep(philo->data->stime);
		// pthread_mutex_unlock(&philo->data->lock);

		
		// thinking time
		// pthread_mutex_lock(&philo->data->print);
		if (!philo->data->isend)
			printf("%zu %d is thinking\n", get_time() - philo->data->simul_beg, philo->id);
		// pthread_mutex_unlock(&philo->data->print);
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
		
		return 0;
		// todo
	}
	else
	{
		data->simul_beg = get_time();
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
