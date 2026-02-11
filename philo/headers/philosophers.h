
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <sys/time.h>
# define RED "\033[0;31m"
# define YLW "\033[0;33m"
# define MS 1000

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				isloner;
	int				id;
	int				meals;
	int				meals_eaten;
	_Atomic long	lastmeal_time;
	_Atomic int		isfull;
	_Atomic int		isdead;

	t_mtx			*rfork;
	t_mtx			*lfork;

	t_data			*data;

	int				end;
}			t_philo;

struct s_data
{
	int				howmanyphilos;
	_Atomic long	dtime;
	size_t			etime;
	size_t			stime;
	int				mealsnum;
	_Atomic int		isend;
	int				allfull;
	_Atomic int		allin;
	size_t			simul_beg;
	t_mtx			*forks;
	t_philo			*philos;
	pthread_t		monitor;

	t_mtx			lock;
};

void	ft_error(t_data *data, char *message);
int		ft_atoi(char *s);
long	get_time(void);
void	ft_usleep(long micros, t_philo *philo);

t_data	*stuffing(char **av, int ac);
void	forking(t_philo *philo, t_mtx *forks, int pos);
int		creating_philosophers(t_data *data);
int		creating(t_data *data);

int		caniprint(t_data *data, t_philo *philo, char *s);
int		simulation(t_data *data);

int		waiting(t_data *data);
void	f_a_r(t_data *data);
int		init_m(t_data *data);
int		destroying(t_data *data);
int		preventing_headache(t_data *data);

int		monitoring(t_data *data);
int		qosos_ending(t_data *data);

#endif
