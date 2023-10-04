/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:05:29 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/04 13:05:57 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief Prints a message with the philosopher's ID and 
 * the current simulation time.
 * 
 * @param philo Pointer to the philosopher struct.
 * @param message The message to be printed.
 */
void	print_msg(t_Philosopher *philo, char *message)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	pthread_mutex_lock(&philo->sim->simulation_lock);
	if (philo->sim->simulation_running == 1 || philo->state == DEAD)
	{
		printf("%ld %d %s\n", (get_time_ms() - philo->sim->start_time), philo->id, message);
	}
	pthread_mutex_unlock(&philo->sim->print_lock);
	pthread_mutex_unlock(&philo->sim->simulation_lock);
}

long int	get_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/**
 * Determines if a philosopher should die based 
 * on the time elapsed since their last meal.
 * 
 * @param philo The philosopher to check.
 * @return 1 if the philosopher should die, 0 otherwise.
 */
int	died(t_Philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->died_lock);
	if ((get_time_ms() - philo->last_meal_time)
		>= philo->sim->time_to_die)
	{
		if (philo->sim->simulation_running == 1)
		{
			print_msg(philo, "died");
		}
		philo->sim->simulation_running = 0;
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->sim->died_lock);
		return (1);
	}
	else
	{
	pthread_mutex_unlock(&philo->sim->died_lock);
		return (0);
	}
}

void	action_philo(long int time, t_Philosopher *philo)
{
	long int	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time)
	{
		if (died(philo))
			return ;
	}
}