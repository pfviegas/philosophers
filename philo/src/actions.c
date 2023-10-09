/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:33:38 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/09 11:32:37 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * Changes the state of the philosopher to thinking.
 * 
 * @param philo The philosopher to change the state of.
 */
void	think_philo(t_Philosopher *philo)
{
	philo->state = THINKING;
}

/**
 * Sleeps the philosopher for a certain amount of time.
 * 
 * @param philo The philosopher to put to sleep.
 */
void	sleep_philo(t_Philosopher *philo)
{
	philo->state = SLEEPING;
	print_msg(philo, "is sleeping", 1);
	action_philo(philo->sim->time_to_sleep, philo);
	usleep(100);
}

/**
 * This function represents the action of a philosopher eating.
 * Takes a pointer to a Philosopher struct as argument.
 * Calculates the index of the left and right forks of the philosopher.
 * Grabs the forks and locks the meals mutex.
 * Updates the last meal time, state and meals left of the philosopher.
 * Unlocks the meals mutex and prints a message that the philosopher is eating.
 * Calls action_philo to simulate the time the philosopher spends eating.
 * It drops the forks.
 */
void	eat_philo(t_Philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->sim->num_philosophers;
	if (grab_forks(philo, left_fork, right_fork) == 1)
		return ;
	pthread_mutex_lock(&philo->sim->meals_lock);
	philo->last_meal_time = get_time_ms();
	philo->state = EATING;
	philo->meals_left--;
	pthread_mutex_unlock(&philo->sim->meals_lock);
	print_msg(philo, "is eating", 1);
	action_philo(philo->sim->time_to_eat, philo);
	drop_forks(philo, left_fork, right_fork);
}

/**
 * The philosopher_life function is the main function 
 * that controls the life cycle of a philosopher.
 * 
 * @param arg A pointer to a t_Philosopher struct that 
 * contains information about the philosopher.
 * @return void* Returns a null pointer when the function is finished.
 */
void	*philosopher_life(void *arg)
{
	t_Philosopher	*philo;

	philo = (t_Philosopher *)arg;
	if (one_philo(philo) == 1)
		return ((void *)0);
	while (philo->meals_left != 0)
	{
		pthread_mutex_lock(&philo->sim->simulation_lock);
		if (philo->sim->simulation_running == 0)
		{
			pthread_mutex_unlock(&philo->sim->simulation_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->sim->simulation_lock);
		if (died(philo) == 1)
			break ;
		if (philo->state == THINKING || philo->state == WAITING)
			eat_philo(philo);
		else if (philo->state == EATING)
			sleep_philo(philo);
		else if (philo->state == SLEEPING)
			think_philo(philo);
	}
	return (NULL);
}
