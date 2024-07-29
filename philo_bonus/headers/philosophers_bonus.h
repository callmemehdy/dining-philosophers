/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:34:54 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/26 15:17:03 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# define _GNU_SOURCE
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# define RED "\033[0;31m"
# define YLW "\033[0;33m"
# define MS 1000
# define ALLO_ERROR "ERROR: allocation failed\n"
# define INIT_ERR "ERROR: making philos failed\n"
# define ARG_ERR  "Invalid arguments\n"
# define FREE_ERR  "Resources cleaning error\n"
# define ERR_NO 1337
# define AH 1
# define LA 0
# define TFORK "has taken a fork\n"
# define EAT "is eating\n"
# define DIED "died\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define SAMAM_LAMAN 0

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	pthread_t				monithread;
	int						id;
	_Atomic int				meals_eaten;
	_Atomic size_t			last_meal_t;
	_Atomic int				isfull;
	_Atomic int				isdead;
	_Atomic int				isloner;
	// semaphores
	sem_t					*fork;
	t_data					*data;
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
	// sems ...  
	sem_t			*print;
	sem_t			*stop;
	t_philo			*philos;
};
// utils
int			p_error(char *message, int status);
int			ft_atoi(char *s);
size_t		get_time(void);
void		ft_usleep(size_t milliseconds);
void		printing(t_philo *philo, char *message);
// creating
t_data		*making_philos(t_data *data, int ac, char **av);
// monitor
void		*monitoring_stuff(void *data);
void		destroying_sem(t_data *data);

#endif