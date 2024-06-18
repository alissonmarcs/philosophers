/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:18:29 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/17 07:18:30 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef enum e_status	t_status;

enum					e_status
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

struct					s_data
{
	int					philo_nbr;
	int					fork_nbr;
	int					max_meals;
	long				start_time;
	long				die_time;
	long				eat_time;
	long				sleep_time;
	long				philos_running_cont;
	pthread_mutex_t		print_mtx;
	pthread_mutex_t		data_mtx;
	pthread_t			monitor;
	bool				philo_died;
	bool				monitor_run;
	t_philo				*philos;
	t_fork				*forks;
};

struct					s_philo
{
	int					index;
	long				eat_count;
	long				last_eat;
	bool				full;
	t_status			status;
	t_fork				*own;
	t_fork				*additional;
	t_data				*data;
	pthread_t			th_id;
	pthread_mutex_t		philo_mtx;
};

struct					s_fork
{
	int					id;
	pthread_mutex_t		mtx;
};

void					print_status(t_philo *philo, t_status status);
long					get_time(void);
long					ft_atol(const char *str);
bool					check_argv(int argc, char **argv);
void					init_data(t_data *data, char **argv);
void					debug(t_data *data);
void					clear(t_data *data);
void					dinner(t_data *data);
void					simulate_single_philosopher(t_data *data);
bool					simulation_status(t_data *data);
bool					get_bool(pthread_mutex_t *mtx, bool *ptr);
long					get_long(pthread_mutex_t *mtx, long *ptr);
void					set_bool(pthread_mutex_t *mtx, bool *ptr,
							bool value);
void					set_long(pthread_mutex_t *mtx, long *ptr,
							long value);
void					increase_long(pthread_mutex_t *mtx, long *ptr);
void					eat(t_philo *philo);
void					*philosopher(void *param);

# define YELLOW "\001\033[1;33m\002"
# define GREEN "\001\033[1;32m\002"
# define RED "\001\033[1;31m\002"
# define BLUE "\001\033[1;94m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[1;37m\002"
# define RESET "\001\033[0m\002"

#endif
