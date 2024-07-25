/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:38 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/25 15:38:29 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	thelastonestanding(t_data *data)
{
	int res;

	pthread_mutex_lock(&data->monilock);
	res = (data->isend == 1);
	pthread_mutex_unlock(&data->monilock);
	return (res);
}

void	caniprint(t_data *data, t_philo *philo, char *s)
{
	if (!philo -> isfull && !data->isend)
		printf("%zu %d %s\n",
				get_time() - philo->data->simul_beg, philo->id, s);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	caniprint(philo -> data, philo, "has taken a fork");
	if (philo->isloner)
		return (1);
	pthread_mutex_lock(philo->rfork);
	caniprint(philo -> data, philo, "has taken a fork");
	caniprint(philo -> data, philo, "is eating");
	// pthread_mutex_lock(&philo->data->reading);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->mealsnum)
		1337 && (philo -> isfull = 1, philo->end = 1);
	// pthread_mutex_unlock(&philo->data->reading);
	ft_usleep(philo->data->etime);
	philo->lastmeal_time = get_time();
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (philo -> end);
}

void	*qosos(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (!(philo->id % 2))
		ft_usleep(5);
	pthread_mutex_lock(&philo->data->lock);
	philo->data->allin++;
	pthread_mutex_unlock(&philo->data->lock);
	while (!thelastonestanding(philo->data))
	{
		if(eating(philo))
			break ;
		caniprint(philo -> data, philo, "is sleeping");
		ft_usleep(philo->data->stime);
		caniprint(philo -> data, philo, "is thinking");
	}
	return (NULL);
}

int	simulation(t_data *data)
{
	int			i;

	i = -1;
	if (!data->howmanyphilos)
		return (4817);
	else
	{
		if (data->howmanyphilos == 1)
			data->philos[0].isloner = 1;
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
