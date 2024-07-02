/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akar <mel-akar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:45:40 by mel-akar          #+#    #+#             */
/*   Updated: 2024/07/01 16:50:07 by mel-akar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include  <stdio.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define YLW "\033[0;33m"

typedef	enum s_ops
{
	lock = 1,
	unlock = 2,
	destroy = 3,
	init = 4
}			t_ops;

typedef struct s_forks
{
	pthread_mutex_t *rfork;
	pthread_mutex_t *lfork;
		
}			t_forks;

typedef struct s_data
{
	pthread_t   *philos;
	int         philon;
	int         dtime;
	int         etime;
	int         stime;
	int         eatn;
}       t_data;

typedef struct s_philo
{
	pthread_t id;
	t_data *data;
}             t_philo;

void    ft_error(t_data *data, int status, char *message);
int     ft_atoi(char *s);
#endif
