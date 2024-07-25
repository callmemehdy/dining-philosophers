/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:31:01 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/24 20:20:59 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers_bonus.h"

void f()
{
	system("lsof -c philo_bonus");
}

int	dead(t_philo *philo)
{
	if (get_time() - philo -> last_meal_t > philo -> data -> dtime)
		return AH;
	return LA;
}

int	full(t_philo *philo)
{
	int n_meal;

	n_meal = philo -> data -> mealsnum;
	if (philo -> meals_eaten == n_meal)
		return AH;
	return LA;
}

void	*monitoring_stuff(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (dead(philo))
		{
			printf("%zu %d died\n", get_time() - philo -> data -> simul_beg, philo -> id);
			exit(12);
		}
		// if (full(philo))
		// {
		// 	printf("kilo kilo hh\n");	
		// 	while (++i < philo -> data -> howmanyphilos)
		// 		(getpid() != philo -> data -> pids[i]) && (kill(philo -> data -> pids[i], SIGTERM));
		// 	return (0);
		// }
	}
	return (NULL);
}

void	qosos(t_philo *philo)
{
	if (!(philo -> id % 2))
		ft_usleep(5);
	pthread_create(&philo -> monithread, NULL, monitoring_stuff, philo);
	while (1)
	{
		sem_wait(philo -> lfork);
		printf("%zu %d has taken a fork\n", get_time() - philo -> data -> simul_beg , philo ->id);
		sem_wait(philo -> rfork);
		printf("%zu %d has taken a fork\n", get_time() - philo -> data -> simul_beg , philo ->id);
		printf("%zu %d is eating\n", get_time() - philo -> data -> simul_beg, philo->id);
		philo -> last_meal_t = get_time();
		philo -> meals_eaten++;
		ft_usleep(philo -> data -> etime);
		sem_post(philo -> lfork);
		sem_post(philo -> rfork);
		printf("%zu %d is sleeping\n", get_time() - philo -> data -> simul_beg, philo->id);
		ft_usleep(philo -> data -> stime);
		printf("%zu %d is thinking\n", get_time() - philo -> data -> simul_beg, philo->id);
	}
	pthread_join(philo -> monithread, NULL);
	return ;
}

void	processes_forking(t_data *data)
{
	size_t		size;
	int			i;
	int			status;

	i = -1;
	size = data -> howmanyphilos;
	data -> pids = malloc(sizeof(pid_t) * size);
	if (!data -> pids)
		p_error(ALLO_ERROR, ERR_NO);
	data -> simul_beg = get_time();
	while (++i < data -> howmanyphilos)
		data -> philos[i].last_meal_t = data -> simul_beg;
	i = -1;
	while (++i < data -> howmanyphilos)
	{
		data -> pids[i] = fork();
		if (!data -> pids[i])
			qosos(&data -> philos[i]);
		else if (data -> pids[i] < 0)
			p_error("fork func error", ERR_NO);
	}
	i = 0;
	while (i < data -> howmanyphilos && waitpid(data -> pids[i], &status, 0))
	{
		if (WEXITSTATUS(status))
		{
			i = -1;
			while (++i < data -> howmanyphilos)
				kill(data -> pids[i], SIGKILL);
			break ;
		}
		i++;
	}
	// while (waitpid(-1, NULL, 0))
	// 	{};
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
