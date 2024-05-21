#include <philo.h>

static void	init_forks(t_data *data);
static void	init_philos(t_data *data);
static void	save_argv(t_data *data, char **argv);

void	init_data(t_data *data, char **argv)
{
	save_argv(data, argv);
	data->philos = malloc(sizeof (t_philo) * data->philo_nbr);
	data->forks = malloc(sizeof (t_fork) * data->fork_nbr);
	init_forks(data);
	init_philos(data);
}

static void	init_forks(t_data *data)
{
	int			i;
	t_fork		*current;

	i = -1;
	while (++i < data->fork_nbr)
	{
		current = data->forks + i;
		current->id = i + 1;
		pthread_mutex_init(&current->mtx, NULL);
	}
}

static void	save_argv(t_data *data, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	data->fork_nbr = data->philo_nbr;
	data->die_time = ft_atol(argv[2]) * 1000;
	data->eat_time = ft_atol(argv[3]) * 1000;
	data->sleep_time = ft_atol(argv[4]) * 1000;
	if (argv[5])
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
}

static void	init_philos(t_data *data)
{
	int			i;
	t_philo		*current;

	i = -1;
	while (++i < data->philo_nbr)
	{
		current = data->philos + i;
		current->id = i + 1;
		current->data = data;
	}
}
