/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 06:34:54 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/21 11:24:54 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# define RED "\033[0;31m"
# define YLW "\033[0;33m"
# define MS 1000
# define ALLO_ERROR "ERROR: allocation failed"
# define INIT_ERR "ERROR: making philos failed"
# define ARG_ERR  "Invalid arguments"
# define ERR_NO 1337

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
}			t_philo;

struct s_data
{
	int				howmanyphilos;
	size_t			dtime;
	size_t			etime;
	size_t			stime;
	int				mealsnum;
	int				isend;
	size_t			simul_beg;
	t_philo			*philos;
};
// utils
void	ft_error(t_data *data, char *message);
int		ft_atoi(char *s);
size_t	get_time(void);
void	ft_usleep(size_t micros);
// creating

#endif