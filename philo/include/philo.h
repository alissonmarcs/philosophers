#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

typedef struct		s_data t_data;
typedef struct		s_fork t_fork;
typedef struct		s_philo t_philo;
typedef enum		e_status t_status;

enum e_status
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

struct s_data
{
	int							philo_nbr;
	int							fork_nbr;
	bool						philo_died;
	const int					max_meals;
	const long					start_time;
	const long					die_time;
	const long					eat_time;
	const long					sleep_time;
	pthread_mutex_t				print_mtx;
	pthread_mutex_t				data_mtx;
	pthread_t					monitor;
	t_philo 					*philos;
	t_fork						*forks;
};

struct s_philo
{
	const int					index;
	long						last_eat_start_time;
	bool						full;
	t_status					status;
	t_fork						*own;
	t_fork						*additional;
	t_data						*data;
	pthread_t					th_id;
	pthread_mutex_t				philo_mtx;
};

struct s_fork
{
	int						id;
	pthread_mutex_t			mtx;
};

void			print_status(t_philo *philo, t_status status);
long			get_time(void);
long			ft_atol(const char *str);
bool			check_argv(int argc, char **argv);
void			init_data(t_data *data, char **argv);
void			debug(t_data *data);
void			clear(t_data *data);
long			 get_time_since_init(t_data *data);
void			*philosopher(void *param);
void			dinner(t_data *data);

# define YELLOW "\001\033[1;33m\002"
# define GREEN "\001\033[1;32m\002"
# define RED "\001\033[1;31m\002"
# define BLUE "\001\033[1;94m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[1;37m\002"
# define RESET "\001\033[0m\002"

#endif
