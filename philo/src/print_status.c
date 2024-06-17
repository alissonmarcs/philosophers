/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:19:16 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/17 07:19:31 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static long	get_time_since_init(t_data *data)
{
	return (get_time() - data->start_time);
}

void	print_status(t_philo *philo, t_status status)
{
	long	time;

	if (getter_bool(&philo->philo_mtx, &philo->full))
		return ;
	pthread_mutex_lock(&philo->data->print_mtx);
	time = get_time_since_init(philo->data);
	if (status == DIED && simulation_status(philo->data))
		printf("%-6li" "%d" " %s\n", time, philo->index, RED "died" RESET);
	else if (status == TAKEN_FORK && !simulation_status(philo->data))
		printf("%-6li" "%d" " %s\n", time, philo->index,
			CYAN "has taken a fork" RESET);
	else if (status == EATING && !simulation_status(philo->data))
		printf("%-6li" "%d" " %s\n", time, philo->index,
			WHITE "is eating" RESET);
	else if (status == SLEEPING && !simulation_status(philo->data))
		printf("%-6li" "%d" " %s\n", time, philo->index,
			BLUE "is sleeping" RESET);
	else if (status == THINKING && !simulation_status(philo->data))
		printf("%-6li" "%d" " %s\n", time, philo->index,
			YELLOW "is thinking" RESET);
	pthread_mutex_unlock(&philo->data->print_mtx);
}
