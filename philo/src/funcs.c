/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:06:36 by paulo             #+#    #+#             */
/*   Updated: 2023/09/16 20:39:51 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

/**
 * @brief Prints a message with the philosopher's ID and 
 * the current simulation time.
 * 
 * @param philo Pointer to the philosopher struct.
 * @param message The message to be printed.
 */
void	print_message(t_Philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%ld %d %s\n", total_time(philo->sim), philo->id, message);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

/**
 * Calculates the total time elapsed since the start of the simulation.
 * 
 * @param sim Pointer to the simulation struct.
 * @return The total time elapsed in milliseconds.
 */
long	total_time(t_Simulation *sim)
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - sim->start_time.tv_sec) * 1000 +
			(current_time.tv_usec - sim->start_time.tv_usec) / 1000);
}

/**
 * Determines if a philosopher should die based on the time elapsed since their last meal.
 * @param philo The philosopher to check.
 * @return 1 if the philosopher should die, 0 otherwise.
 */
int should_die(t_Philosopher *philo)
{
	return (total_time(philo->sim) - philo->last_meal_time) > philo->sim->time_to_die;
}
