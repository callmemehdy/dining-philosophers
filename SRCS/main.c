#include "../headers/philosophers.h"


t_data  *stuffing(char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->howmanyphilos = ft_atoi(av[1]);
	data->dtime = ft_atoi(av[2]);
	data->etime = ft_atoi(av[3]);
	data->stime = ft_atoi(av[4]);
	data->mealsnum = ft_atoi(av[5]);
	data->isend = 0;
	return (data);
}

void	forking(t_philo *philo, t_fork *forks, int pos)
{
	int round;


	round = philo->data->howmanyphilos;
	if (!(pos % 2))
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

void	creating_philosophers(t_data *data)
{
	int		i;
	t_philo *philo;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * data->howmanyphilos);
	if (!data->philos)
		ft_error(data, EXIT_FAILURE, "philos's failing!");
	while (++i < data->howmanyphilos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->isfull = 0;
		philo->meals = data->mealsnum;
		philo->meals_eaten = 0;
		forking(&philo[i], data->forks, i);
	}
	philo->data = data;
}

void	creating(t_data *data)
{
	int i;

	i = -1;
	data->forks = malloc(sizeof(t_fork) * data->howmanyphilos);
	if (!data->forks)
		ft_error(data, EXIT_FAILURE, "forkalloc!");
	while (++i < data->howmanyphilos)
	{
		if(pthread_mutex_init(&data->forks[i].fork, NULL))
			ft_error(data, EXIT_FAILURE, "mutex init failed");
		data->forks[i].fork_id = i;
	}
	creating_philosophers(data);
}

void	eating(t_philo *philo)
{
	if (philo->isfull)
		return ;
	if (pthread_mutex_lock(&philo->rfork->fork))
		ft_error(philo->data, 1 >> 0, "...some issues locking forks mutexes...");
	printf("%d\thas taken a fork\n", philo->id);
	if (pthread_mutex_lock(&philo->lfork->fork))
		ft_error(philo->data, 1 >> 0, "...some issues locking forks mutexes...");
	printf("%d\thas taken a fork\n", philo->id);
	printf("%d\tis eating\n", philo->id);
	ft_usleep(philo->data->etime);
	philo->meals_eaten++;
	philo->lastmeal_time = get_time();
	if (philo->meals_eaten == philo->meals)
		philo->isfull = 1;
	if (pthread_mutex_unlock(&philo->rfork->fork))
		ft_error(philo->data, 1 >> 0, "...some issues unlocking forks mutexes...");
	if (pthread_mutex_unlock(&philo->lfork->fork))
		ft_error(philo->data, 1 >> 0, "...some issues unlocking forks mutexes...");

}

void	*sum_func(void *p)
{
	// int 	i;
	t_philo *philo;

	philo = (t_philo *)p;
	// i = -1;
	while (!philo->data->isend)
	{
		// i should implement the eating function so that the philos take the forks ... release ite
		eating(philo);
	}
	// I SHOULD COMPLETE SIMUL TODAY... AND MAKE MY FT_USLEEP...
	// simuuuuulations
	return (NULL);
}

void	simulation(t_data *data)
{
	int i;

	i = -1;
	if (!data->mealsnum)
		return ;
	else if (data->howmanyphilos == 1)
	{
		// hello world!
	}
	else
	{
		data->simul_beg = get_time();
		while (++i < data->howmanyphilos)
		{
			data->philos[i].lastmeal_time = get_time();
			if (pthread_create(&data->philos->thread_id, NULL, sum_func, &data->philos[i]))
				ft_error(data, EXIT_FAILURE, "...while creating threads...");
		}
	}
	i = -1;
	while (++i < data->howmanyphilos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			ft_error(data, EXIT_FAILURE, "...while joining threads...");
	}
}

int main(int ac, char **av)
{
	t_data *data;

	if (ac != 6)
		return (1);
	data = stuffing(av);
	data->philos = NULL;
	if (!data)
		ft_error(NULL, EXIT_FAILURE, "Error 001");
	data->philos = malloc(sizeof(pthread_t) * data->howmanyphilos);
	if (!data->philos)
		ft_error(NULL, EXIT_FAILURE, "Error 002");
	creating(data);

}
