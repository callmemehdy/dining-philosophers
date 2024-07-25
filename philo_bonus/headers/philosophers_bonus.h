/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:34:54 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/24 17:31:03 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/time.h>
# define RED "\033[0;31m"
# define YLW "\033[0;33m"
# define MS 1000
# define ALLO_ERROR "ERROR: allocation failed"
# define INIT_ERR "ERROR: making philos failed"
# define ARG_ERR  "Invalid arguments"
# define ERR_NO 1337
# define AH 1;
# define LA 0;

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wdeprecated-declarations"

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	pthread_t	monithread;
	int			id;
	int			meals_eaten;
	size_t		last_meal_t;
	int			isfull;
	int			isdead;
	// semaphores
	sem_t		*rfork;
	sem_t		*lfork;
	t_data		*data;
}			t_philo;

struct s_data
{
	int				howmanyphilos;
	pid_t			*pids;
	size_t			dtime;
	size_t			etime;
	size_t			stime;
	int				mealsnum;
	int				isend;
	size_t			simul_beg;
	sem_t			*forks; 
	t_philo			*philos;
};
// utils
int			p_error(char *message, int status);
int			ft_atoi(char *s);
size_t		get_time(void);
void		ft_usleep(size_t micros);
// creating
sem_t		*phalloc(t_data *data);
void		assign_forks(t_philo *philo, int pos);
t_philo		*init_philo(t_data *data);
t_data		*making_philos(t_data *data, int ac, char **av);


#endif