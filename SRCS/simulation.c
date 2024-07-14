
#include "../headers/philosophers.h"

void	printing(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->print))
		ft_error(philo->data, EXIT_FAILURE, "mutexLock error in print");
	printf("%zu %d has taken a fork\n", get_time() - philo->data->simul_beg, philo->id);
	if (pthread_mutex_unlock(&philo->data->print))
		ft_error(philo->data, EXIT_FAILURE, "mutexUNlock error in print");
}

int	eating(t_philo *philo)
{
	// if (philo->isfull)
	// 	return (1);
	if (pthread_mutex_lock(&philo->rfork->fork))
		ft_error(philo->data, 1 >> 0, "...some issues locking forks mutexes...");
	printing(philo);
	if (pthread_mutex_lock(&philo->lfork->fork))
		ft_error(philo->data, 1 >> 0, "...some issues locking forks mutexes...");
	printing(philo);
	printf("%zu %d is eating\n", get_time() - philo->data->simul_beg, philo->id);
	ft_usleep(philo->data->etime * 1000);
	philo->meals_eaten++;
	philo->lastmeal_time = get_time();
	if (pthread_mutex_unlock(&philo->rfork->fork))
		ft_error(philo->data, 1 >> 0, "...some issues unlocking forks mutexes...");
	if (pthread_mutex_unlock(&philo->lfork->fork))
		ft_error(philo->data, 1 >> 0, "...some issues unlocking forks mutexes...");
	return (0);

}

void	*sum_func(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	pthread_mutex_init(&philo->setting, NULL);
	pthread_mutex_lock(&philo->setting);
	philo->lastmeal_time = get_time();
	pthread_mutex_unlock(&philo->setting);
	while (philo->data->isend == 0)
	{
		// i should implement the eating function so that the philos take the forks ... release it
		eating(philo);
		pthread_mutex_lock(&philo->setting);
		printf("%zu %d is sleeping\n", get_time() - philo->data->simul_beg, philo->id);
		ft_usleep(philo->data->stime * 1000);
		printf("%zu %d is thinking\n", get_time() - philo->data->simul_beg, philo->id);
		pthread_mutex_unlock(&philo->setting);
	}
	// I SHOULD COMPLETE SIMUL TODAY... AND MAKE MY FT_USLEEP...
	// simuuuuulations
	return (NULL);
}

void	simulation(t_data *data)
{
	int i;

	i = -1;
	if (!data->mealsnum || !data->howmanyphilos)
		ft_error(data, EXIT_SUCCESS, "meals or philo number's invalid");
	else if (data->howmanyphilos == 1)
	{
		// hello world!
	}
	else
	{
		data->simul_beg = get_time();
		while (++i < data->howmanyphilos)
		{
			if (pthread_create(&data->philos->thread_id, NULL, sum_func, &data->philos[i]))
				ft_error(data, EXIT_FAILURE, "...while creating threads...");
		}
		if (pthread_create(&data->monitor, NULL, monitoring, data))
			ft_error(data, EXIT_FAILURE, "...while creating monitor...");

	}
	i = -1;
	while (++i < data->howmanyphilos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			ft_error(data, EXIT_FAILURE, "...while joining threads...");
	}
	if (pthread_join(data->monitor, NULL))
		ft_error(data, EXIT_FAILURE, "...while joining monitor...");
}
