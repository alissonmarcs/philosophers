/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:19:11 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/17 07:19:12 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_argv(argc, argv))
		return (EXIT_FAILURE);
	init_data(&data, argv);
	dinner(&data);
	clear(&data);
	return (42);
}
