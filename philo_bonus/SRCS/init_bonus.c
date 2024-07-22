/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:33:30 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/21 21:21:34 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

sem_t	*phalloc(t_data *data)
{
	size_t		size;

	size = data->howmanyphilos;
	data -> forks = sem_open("/sem", O_CREAT , size);
	if (!data -> forks)
		p_error(ALLO_ERROR, ERR_NO);
	unlink("/sem");
	return (data -> forks);
}

t_philo	*init_philo(t_data *data)
{
	int		i;

	i = -1;
	data -> philos = malloc(sizeof(t_philo) * data -> howmanyphilos);
	if (!data)
		p_error(ALLO_ERROR, ERR_NO);
	while (++i < data->howmanyphilos)
	{
		data -> philos[i].data = data;
		data -> philos[i].id = i + 1;
		data -> philos[i].isdead = 0;
		data -> philos[i].isfull = 0;
		data -> philos[i].meals_eaten = 0;
		data -> philos[i].lfork = data -> forks;
		data -> philos[i].rfork = data -> forks;
	}
	return (data -> philos);
}

t_data	*making_philos(t_data *data, int ac, char **av)
{
	if (ac != 6 && ac != 5)
		return ((void)p_error(ARG_ERR, ERR_NO), NULL);
	(ac == 6) && (data->mealsnum = ft_atoi(av[5]));
	(ac == 5) && (data->mealsnum = 0);
	data -> stime = ft_atoi(av[4]);
	data -> etime = ft_atoi(av[3]);
	data -> dtime = ft_atoi(av[2]);
	data -> howmanyphilos = ft_atoi(av[1]);
	data -> isend = 0;
	data -> forks = phalloc(data);
	data -> philos = init_philo(data);
	return (data);
}
