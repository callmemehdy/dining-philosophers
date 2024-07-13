#include "../headers/philosophers.h"

void	printing(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->print))
		ft_error(philo->data, EXIT_FAILURE, "mutexLock error in print");
	printf("%zu %d has taken a fork\n", get_time() - philo->data->simul_beg, philo->id);
	if (pthread_mutex_unlock(&philo->data->print))
		ft_error(philo->data, EXIT_FAILURE, "mutexUNlock error in print");
}

void	eating(t_philo *philo)
{
	if (philo->isfull)
		return ;
	if (get_time() - philo->lastmeal_time > philo->data->dtime)
		philo->isdead = 1;
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

}

void	*sum_func(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	pthread_mutex_init(&philo->setting, NULL);
	pthread_mutex_lock(&philo->setting);
	philo->lastmeal_time = get_time();
	pthread_mutex_lock(&philo->setting);
	while (!philo->data->isend)
	{
		// i should implement the eating function so that the philos take the forks ... release ite
		eating(philo);
		pthread_mutex_lock(&philo->thinking);
		printf("%zu %d is thinking\n", get_time() - philo->data->simul_beg, philo->id);
		pthread_mutex_unlock(&philo->thinking);
		pthread_mutex_destroy(&philo->setting);
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

int	philo_is_dead(t_philo *philo)
{
	size_t	elapsed;
	size_t	lastmeal;

	lastmeal = philo->lastmeal_time;
	elapsed = get_time() - lastmeal;
	if (elapsed >= philo->data->dtime)
		return (1);
	return (0);
}

void	*monitoring_threads(void *dt)
{
	int			i;
	t_data		*data;

	data = (t_data *)dt;
	while (!data->isend)
	{
		i = -1;
		while (++i < data->howmanyphilos)
		{
			if (philo_is_dead(&data->philos[i]))
			{
				printf("%zu %d died\n", get_time() - data->simul_beg, data->philos[i].id);
				data->isend = 1;
			}
		}
	}
	return NULL;
}

int main(int ac, char **av)
{
	t_data *data;

	if (ac != 6)
		ft_error(NULL, EXIT_FAILURE, "Usage: ./program [] [] [] [] []");
	data = stuffing(av);
	if (!data)
		ft_error(NULL, EXIT_FAILURE, "Error 001");
	data->philos = NULL;
	if (pthread_mutex_init(&data->print, NULL))
		ft_error(data, EXIT_FAILURE, "printMutex error");
	creating(data);
	simulation(data);
	// pthread_create(&data->monitor, NULL, monitoring_threads, data);
	// pthread_join(data->monitor, NULL);
}
