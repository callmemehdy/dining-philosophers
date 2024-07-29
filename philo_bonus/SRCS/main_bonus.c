/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:31:01 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/26 15:19:29 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

static int	stop_cooking(t_philo *philo)
{
	if (philo -> isfull == 1)
		return (1337);
	return (0);
}

static void	qosos(t_philo *philo)
{
	pthread_create(&philo -> monithread, NULL, monitoring_stuff, philo);
	pthread_detach(philo -> monithread);
	while (!stop_cooking(philo))
	{
		sem_wait(philo -> lfork);
		printing(philo, TFORK);
		sem_wait(philo -> rfork);
		printing(philo, TFORK);
		printing(philo, EAT);
		ft_usleep(philo -> data -> etime);
		philo -> meals_eaten++;
		philo -> last_meal_t = get_time();
		sem_post(philo -> lfork);
		sem_post(philo -> rfork);
		printing(philo, SLEEP);
		ft_usleep(philo -> data -> stime);
		printing(philo, THINK);
	}
	return ;
}

static void	ft_wait(t_data *data, int *status)
{
	int		i;

	i = -1;
	while (waitpid(-1, status, 0) != -1)
	{
		if (WEXITSTATUS(*status) == 42)
		{
			while (++i < data -> howmanyphilos)
				kill(data -> pids[i], SIGKILL);
			return ;
		}
	}
}

static void	processes_forking(t_data *data)
{
	size_t		size;
	int			status;
	int			i;

	i = -1;
	size = data -> howmanyphilos;
	data -> pids = malloc(sizeof(pid_t) * size);
	if (!data -> pids)
		p_error(ALLO_ERROR, ERR_NO);
	data -> simul_beg = get_time();
	while (++i < data -> howmanyphilos)
	{
		data -> pids[i] = fork();
		if (!data -> pids[i])
		{
			qosos(&data -> philos[i]);
			exit(EXIT_SUCCESS);
		}
		else if (data -> pids[i] < 0)
			p_error("fork func error", ERR_NO);
		usleep(100);
	}
	ft_wait(data, &status);
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
	if (!data -> mealsnum)
		return (EXIT_SUCCESS);
	processes_forking(data);
}
