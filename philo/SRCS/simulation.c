/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:38 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/30 18:31:32 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	thelastonestanding(t_data *data)
{
	int		res;

	res = (data->isend == 1);
	return (res);
}

int	caniprint(t_data *data, t_philo *philo, char *s)
{
	int		id;
	size_t	start;

	pthread_mutex_lock(&data -> lock);
	if (philo -> isfull || philo->data->isend)
		return (pthread_mutex_unlock(&data -> lock), 1);
	(*s == 'd') && (philo -> data -> isend++);
	id = philo->id;
	start = philo->data->simul_beg;
	printf("%zu %d %s\n", get_time() - start, id, s);
	pthread_mutex_unlock(&data -> lock);
	return (0);
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
	philo->lastmeal_time = get_time();
	philo->meals_eaten++;
	ft_usleep(philo->data->etime);
	if (philo->meals_eaten == philo->data->mealsnum)
		1337 && (philo -> isfull = 1, philo->end = 1);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (philo -> end);
}

void	*qosos(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (!(philo->id % 2))
		ft_usleep(100);
	while (!thelastonestanding(philo->data))
	{
		if (eating(philo))
			break ;
		usleep(50);
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
	if (!data->howmanyphilos || !data->mealsnum)
		return (4817);
	else
	{
		if (data->howmanyphilos == 1)
			data->philos[0].isloner = 1;
		data->simul_beg = get_time();
		while (++i < data->howmanyphilos)
		{
			data->philos[i].lastmeal_time = get_time();
			if (pthread_create(&data->philos[i].thread_id, NULL, qosos,
					&data->philos[i]))
			{
				ft_error(data, "..while creating threads..");
				return (1337);
			}
		}
	}
	return (0);
}
