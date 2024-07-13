#include "../headers/philosophers.h"


int	philo_is_dead(t_philo *philo)
{
	size_t	elapsed;
	size_t	lastmeal;

	if (philo->meals_eaten == philo->data->mealsnum)
		philo->isfull = 1;
	if (philo->isfull)
		return (0);
	lastmeal = philo->lastmeal_time;
	elapsed = get_time() - lastmeal;
	if (elapsed >= philo->data->dtime)
		return (1);
	return (0);
}

void	*monitoring_threads(void *dt)
{
	int			i;
	int			alldone;
	t_data		*data;

	data = (t_data *)dt;
	alldone = 0;
	while (!data->isend)
	{
		i = -1;
		while (++i < data->howmanyphilos && !data->isend)
		{
			if (philo_is_dead(&data->philos[i]))
			{
				printf("%zu %d died\n", get_time() - data->simul_beg, data->philos[i].id);
				data->isend = 1;
			}
			if (!data->philos[i].isfull)
				alldone = 1;
		}
		if(!alldone)
		{
			exit(0);
			data->isend = 1;
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
	if (pthread_mutex_init(&data->thinking, NULL))
		ft_error(data, EXIT_FAILURE, "printMutex error");
	creating(data);
	simulation(data);
}
