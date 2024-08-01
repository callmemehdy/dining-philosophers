/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:31:01 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/30 16:05:08 by mel-akar         ###   ########.fr       */
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
	pthread_create(&philo -> monithread, NULL, monitoring_stuff, (void *)philo);
	pthread_detach(philo -> monithread);
	while (!stop_cooking(philo))
	{
		printing(philo, THINK, LA);
		sem_wait(philo -> fork);
		printing(philo, TFORK, LA);
		sem_wait(philo -> fork);
		printing(philo, TFORK, LA);
		printing(philo, EAT, LA);
		philo -> meals_eaten++;
		philo -> last_meal_t = get_time();
		ft_usleep(philo -> data -> etime);
		sem_post(philo -> fork);
		sem_post(philo -> fork);
		printing(philo, SLEEP, LA);
		ft_usleep(philo -> data -> stime);
		printing(philo, THINK, LA);
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
	long		size;
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
		data -> philos[i].last_meal_t = data -> simul_beg;
		data -> pids[i] = fork();
		if (data -> pids[i] == 0)
		{
			qosos(&data -> philos[i]);
			exit(EXIT_SUCCESS);
		}
		else if (data -> pids[i] < 0)
			p_error("fork func error", ERR_NO);
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
	if (preventing_headache(data))
		return (p_error(ARG_ERR, AH));
	processes_forking(data);
	destroying_sem(data);
}
