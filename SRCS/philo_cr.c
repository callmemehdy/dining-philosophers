
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
		philo->isdead = 0;
		philo->data = data;
		philo->lastmeal_time = get_time();
		forking(philo, data->forks, i);
	}
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