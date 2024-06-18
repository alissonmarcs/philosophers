/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:18:57 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/17 07:18:58 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	get_bool(pthread_mutex_t *mtx, bool *ptr)
{
	bool	tmp;

	pthread_mutex_lock(mtx);
	tmp = *ptr;
	pthread_mutex_unlock(mtx);
	return (tmp);
}

long	get_long(pthread_mutex_t *mtx, long *ptr)
{
	long	tmp;

	pthread_mutex_lock(mtx);
	tmp = *ptr;
	pthread_mutex_unlock(mtx);
	return (tmp);
}

void	set_bool(pthread_mutex_t *mtx, bool *ptr, bool value)
{
	pthread_mutex_lock(mtx);
	*ptr = value;
	pthread_mutex_unlock(mtx);
}

void	set_long(pthread_mutex_t *mtx, long *ptr, long value)
{
	pthread_mutex_lock(mtx);
	*ptr = value;
	pthread_mutex_unlock(mtx);
}

void	increase_long(pthread_mutex_t *mtx, long *ptr)
{
	pthread_mutex_lock(mtx);
	(*ptr)++;
	pthread_mutex_unlock(mtx);
}
