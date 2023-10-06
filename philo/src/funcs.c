/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:05:29 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/06 17:26:23 by pviegas          ###   ########.fr       */
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
void	print_msg(t_Philosopher *philo, char *message, int sim_lock)
{
	if (sim_lock)
		pthread_mutex_lock(&philo->sim->simulation_lock);
	pthread_mutex_lock(&philo->sim->print_lock);
	if (philo->sim->simulation_running == 1)
	{
		printf("%ld %d %s\n", (get_time_ms() - philo->sim->start_time),
			philo->id, message);
	}
	pthread_mutex_unlock(&philo->sim->print_lock);
	if (sim_lock)
		pthread_mutex_unlock(&philo->sim->simulation_lock);
}

/**
 * Returns the current time in milliseconds.
 * Uses gettimeofday() function to get the current time.
 * 
 * @return The current time in milliseconds.
 */
long int	get_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/**
 * Checks if a philosopher has died by comparing the time elapsed since 
 * their last meal to the time_to_die value of the simulation.
 * If the philosopher has died, it sets their state to DEAD, 
 * stops the simulation, and returns 1.
 * Otherwise, it returns 0.
 * 
 * @param philo A pointer to the philosopher to check for death.
 * @return 1 if the philosopher has died, 0 otherwise.
 */
int	died(t_Philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->simulation_lock);
	if ((get_time_ms() - philo->last_meal_time) >= philo->sim->time_to_die)
	{
		if (philo->sim->simulation_running == 1)
		{
			print_msg(philo, "died", 0);
		}
		philo->sim->simulation_running = 0;
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->sim->simulation_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->sim->simulation_lock);
		return (0);
	}
}

/**
 * @brief This function performs the action of a philosopher for a given time,
 * and checks if the philosopher has died during that time.
 * 
 * @param time The time for which the philosopher performs the action.
 * @param philo The philosopher for whom the action is performed.
 */
void	action_philo(long int time, t_Philosopher *philo)
{
	long int	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time)
	{
		if (died(philo))
		{
			return ;
		}
		usleep(10);
	}
}

/**
 * @brief Destroys all mutexes used in the simulation.
 * 
 * @param sim Pointer to the simulation struct.
 */
void	destroy_mutexes(t_Simulation *sim)
{
	int	i;

	pthread_mutex_destroy(&sim->simulation_lock);
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->meals_lock);
	pthread_mutex_destroy(&sim->time_lock);
	pthread_mutex_destroy(&sim->start_time_lock);
	i = 0;
	while (i < sim->num_philosophers)
		pthread_mutex_destroy(&sim->forks[i++].lock);
}
