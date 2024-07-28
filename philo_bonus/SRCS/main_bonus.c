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

void f()
{
	system("lsof -c philo_bonus");
}

int	dead(t_philo *philo)
{
	if (get_time() - philo -> last_meal_t > philo -> data -> dtime)
		return (AH);
	return (LA);
}

int	full(t_philo *philo)
{
	int n_meal;

	n_meal = philo -> data -> mealsnum;
	if (philo -> meals_eaten == n_meal)
		return (AH);
	return (LA);
}

void	*monitoring_stuff(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (AH)
	{
		if (dead(philo))
		{
			// todo
			philo -> isdead = 1;
			// sem_wait(philo -> data -> print);
			sem_wait(philo -> data -> stop);
			printf("%zu %d died\n", get_time() - philo -> data -> simul_beg, philo -> id);
			exit(42);
			// sem_post(philo -> data -> key);
			break ;
		}
		if (full(philo))
		{
			// exit(EXIT_SUCCESS);
			// sem_wait(philo -> data -> check);
			philo -> isfull = 1;
			// sem_post(philo -> data -> check);
			// sem_post(philo -> data -> key);
			return(NULL);
		}
	}
	return (NULL);
}

int	stop_cooking(t_philo *philo)
{
	// sem_wait(philo -> data -> check);
	if (philo -> isfull == 1)
		return (EXIT_SUCCESS);
	return (0);
	// sem_post(philo -> data -> check);
}

void	printing(t_philo *philo, char *message)
{
	int		id;
	size_t	start;

	sem_wait(philo -> data -> stop);
	start = philo -> data ->simul_beg;
	id = philo -> id;
	printf("%zu %d %s",get_time() - start, id, message);
	sem_post(philo -> data -> stop);
}

void	qosos(t_philo *philo)
{
	pthread_create(&philo -> monithread, NULL, monitoring_stuff, philo);
	pthread_detach(philo -> monithread);
	while (!stop_cooking(philo))
	{
		if (philo -> isfull)
			return ;
		// first fork 
		sem_wait(philo -> lfork);
		printing(philo, TFORK);
		// second fork 
		sem_wait(philo -> rfork);
		printing(philo, TFORK);
		// eating
		printing(philo, EAT);
		ft_usleep(philo -> data -> etime);
		philo -> last_meal_t = get_time();
		philo -> meals_eaten++;
		sem_post(philo -> lfork);
		sem_post(philo -> rfork);

		// sleeping..
		printing(philo, SLEEP);
		ft_usleep(philo -> data -> stime);
		// thinking
		printing(philo, THINK);
	}
	return ;
}

void	processes_forking(t_data *data)
{
	size_t		size;
	int			status;
	int			i;
	// int			j;

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
	i = -1;
	// sem_wait(data -> key);
	while (waitpid(-1, &status, 0))
		if (WEXITSTATUS(status) == 0x2a)
			while (++i < data -> howmanyphilos)
				kill(data -> pids[i], SIGKILL);
	
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
