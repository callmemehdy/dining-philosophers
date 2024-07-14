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
	if (elapsed >= philo->data->dtime ||
		philo->data->allfull == philo->data->mealsnum)
		return (1);
	return (0);
}

void	*monitoring(void *dt)
{
	int			i;
	t_data		*data;

	data = (t_data *)dt;
	while (data->isend == 0)
	{
		i = -1;
		while (++i < data->howmanyphilos && !data->isend)
		{
			if (philo_is_dead(&data->philos[i]))
			{
				printf("%zu %d died\n", get_time() - data->simul_beg, data->philos[i].id);
				data->isend = 1;
			}
			if (data->philos[i].isfull)
				data->allfull++;
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
	if (pthread_mutex_destroy(&data->print))
		ft_error(data, EXIT_FAILURE, "printMutex error");
}
