/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:25:45 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/25 12:15:03 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

t_data	*stuffing(char **av, int ac)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->howmanyphilos = ft_atoi(av[1]);
	data->dtime = ft_atoi(av[2]);
	data->etime = ft_atoi(av[3]);
	data->stime = ft_atoi(av[4]);
	if (ac == 6 && ft_atoi(av[5]))
		data->mealsnum = ft_atoi(av[5]);
	else
		data->mealsnum = -1;
	data->isend = 0;
	data->allfull = 0;
	data->allin = 0;
	return (data);
}

void	forking(t_philo *philo, t_mtx *forks, int pos)
{
	int		round;

	round = philo->data->howmanyphilos;
	if (philo->id % 2)
	{
		philo->rfork = &forks[pos];
		philo->lfork = &forks[(pos + 1) % round];
	}
	else
	{
		philo->rfork = &forks[(pos + 1) % round];
		philo->lfork = &forks[pos];
	}
}

int	creating_philosophers(t_data *data)
{
	int			i;
	t_philo		*philo;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * data->howmanyphilos);
	if (!data->philos)
	{
		ft_error(data, "philos's failing!");
		return (203);
	}
	while (++i < data->howmanyphilos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->isfull = 0;
		philo->meals = data->mealsnum;
		philo->meals_eaten = 0;
		philo->isdead = 0;
		philo->data = data;
		philo->end = 0;
		forking(philo, data->forks, i);
	}
	return (0);
}

int	creating(t_data *data)
{
	int		i;

	i = -1;
	data->forks = malloc(sizeof(t_mtx) * data->howmanyphilos);
	if (!data->forks)
		return (ft_error(data, "forkalloc!"), 777);
	while (++i < data->howmanyphilos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_error(data, "mutex init failed"), 42);
	}
	if (creating_philosophers(data))
		return (ft_error(data, "Error"), 21);
	return (0);
}
