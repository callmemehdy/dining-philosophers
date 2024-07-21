/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:31:01 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/21 21:43:21 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

void f()
{
	system("lsof -c philo_bonus");
}

void	qosos(t_philo *philo)
{
	sem_post(philo -> lfork);
	printf("%zu %d has taken a fork", get_time(), philo ->id);
	sem_post(philo -> rfork);
	printf("%zu %d has taken a fork", get_time(), philo ->id);
}

void	proccesses_forking(t_data *data)
{
	size_t		size;
	int			i;

	i = -1;
	size = data -> howmanyphilos;
	data -> pids = malloc(sizeof(pid_t) * size);
	if (!data -> pids)
		p_error(ALLO_ERROR, ERR_NO);
	while (++i < size)
	{
		data -> pids[i] = fork();
		if (!data -> pids[i])
			qosos(&data -> philos[i]);
		else if (data -> pids[i] < 0)
			p_error("fork func error", ERR_NO);
	}
}

int	main(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (p_error(ALLO_ERROR, ERR_NO));
	data = making_philos(data, ac, av);
	if (!data)
		return (p_error(INIT_ERR, ERR_NO));
	processes_forking(data);
}
