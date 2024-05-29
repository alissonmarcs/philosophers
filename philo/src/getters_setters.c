#include <philo.h>

bool	getter_bool(pthread_mutex_t *mtx, bool *ptr)
{
	bool	tmp;

	pthread_mutex_lock(mtx);
	tmp = *ptr;
	pthread_mutex_unlock(mtx);
	return (tmp);
}

long	getter_long(pthread_mutex_t *mtx, long *ptr)
{
	long	tmp;

	pthread_mutex_lock(mtx);
	tmp = *ptr;
	pthread_mutex_unlock(mtx);
	return (tmp);
}

void	setter_bool(pthread_mutex_t *mtx, bool *ptr, bool value)
{
	pthread_mutex_lock(mtx);
	*ptr = value;
	pthread_mutex_unlock(mtx);
}

void	setter_long(pthread_mutex_t *mtx, long *ptr, long value)
{
	pthread_mutex_lock(mtx);
	*ptr = value;
	pthread_mutex_unlock(mtx);
}
