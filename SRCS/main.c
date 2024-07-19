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

int	init_m(t_data *data);
int	destroying(t_data * data);


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

int	monitoring(t_data *data)
{
	int			i;

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
					pthread_mutex_unlock(&data->monilock);
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
			pthread_mutex_unlock(&data->print);
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
		return (ft_error(NULL, "Usage: ./program [] [] [] [] []"), 1);
	data = stuffing(av, ac);
	if (!data)
		return (ft_error(NULL, "Error 001"), 2);
	data->philos = NULL;
	if (init_m(data)) // initializing mutexes
		return (ft_error(data, "...while initializing..."), 3);
	if(creating(data)) // creating philoz and forks ilakh(etc)...
		return(ft_error(data, "..Error in creating.."), 4);
	if(simulation(data)) // beginning of simulation
		return (ft_error(data, "...Error in simulation..."), 5);
	if (monitoring(data))
		return (ft_error(data, "monitor failed soldier--"), 6);
	// if (destroying(data)) // destroying mutexes
	// 	return (ft_error(data, "some issues while destroying!"), 7);
}

int	init_m(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL))
		return (ft_error(data, "printMutex error"), 1336);
	if (pthread_mutex_init(&data->monilock, NULL))
		return (ft_error(data, "monilock mutex init!"), 1337);
	if (pthread_mutex_init(&data->reading, NULL))
		return (ft_error(data, "monilock mutex init!"), 1337);
	// if (pthread_mutex_init(&data->lock, NULL))
	// 	return (ft_error(data, "sleeplock mutex init!"), 1337);
	return (0);
}

int	destroying(t_data * data)
{
	if (pthread_mutex_destroy(&data->print))
		return (ft_error(data, "printMutex error"), 1340);
	if (pthread_mutex_destroy(&data->monilock))
		return (ft_error(data, "monilock mutex!"), 1341);
	if (pthread_mutex_destroy(&data->reading))
		return (ft_error(data, "monilock mutex!"), 1342);
	// if (pthread_mutex_destroy(&data->lock))
	// 	return (ft_error(data, "sleeplock mutex!"), 1343);
	return (0);
}