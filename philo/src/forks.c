/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:27:41 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/09 12:09:58 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * This function is responsible for a philosopher to grab two forks 
 * (left and right) to start eating.
 * If the philosopher's id is odd, it tries to grab the left fork first, 
 * otherwise it tries to grab the right fork first.
 * If the philosopher successfully grabs both forks, 
 * it sets the forks as unavailable and unlocks the mutex locks.
 * 
 * @param philo A pointer to the philosopher struct.
 * @param left_fork The index of the left fork in the forks array.
 * @param right_fork The index of the right fork in the forks array.
 * @return Returns 0 if the philosopher successfully grabs both forks, 
 *         otherwise returns 1.
 */
int	grab_forks(t_Philosopher *philo, int left_fork, int right_fork)
{
	if (philo->id % 2)
	{
		if (grab_left_fork(philo, left_fork, right_fork) == 1)
			return (1);
	}
	else
	{
		if (grab_right_fork(philo, left_fork, right_fork) == 1)
			return (1);
	}
	philo->sim->forks[left_fork].is_available = 0;
	philo->sim->forks[right_fork].is_available = 0;
	pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
	pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
	return (0);
}

/**
 * This function is responsible for an odd philosopher to grab 
 * first the left fork and then the right fork.
 * If the left fork is not available, the philosopher will wait and return 1.
 * If the right fork is not available, 
 * the philosopher will release the left fork, wait and return 1.
 * If both forks are available, 
 * the philosopher will take both forks and return 0.
 * 
 * @param philo A pointer to the philosopher struct.
 * @param left_fork The index of the left fork in the forks array.
 * @param right_fork The index of the right fork in the forks array.
 * 
 * @return 0 if both forks are available and taken by the philosopher, 
 *         1 otherwise.
 */
int	grab_left_fork(t_Philosopher *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
	if (!philo->sim->forks[left_fork].is_available)
	{
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		if (philo->state != WAITING)
			print_msg(philo, "is thinking", 1);
		philo->state = WAITING;
		return (1);
	}
	pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
	if (!philo->sim->forks[right_fork].is_available) 
	{
		pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		if (philo->state != WAITING)
			print_msg(philo, "is thinking", 1);
		philo->state = WAITING;
		return (1);
	}
	print_msg(philo, "has taken a fork", 1);
	print_msg(philo, "has taken a fork", 1);
	return (0);
}

/**
 * This function is responsible for grabbing the right fork of a philosopher.
 * It takes as input a pointer to a Philosopher struct, 
 * the index of the left fork, and the index of the right fork. 
 * It locks the mutex of the right fork and checks if it is available. 
 * If it is not available, it releases the lock and returns 1.
 * If available, it locks the left fork mutex and checks if it's available.
 * If it is not available, it releases both locks and returns 1. 
 * If both forks are available, prints a message indicating that the 
 * philosopher has taken both forks and returns 0.
 */
int	grab_right_fork(t_Philosopher *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
	if (!philo->sim->forks[right_fork].is_available) 
	{
		pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
		if (philo->state != WAITING)
			print_msg(philo, "is thinking", 1);
		philo->state = WAITING;
		return (1);
	}
	pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
	if (!philo->sim->forks[left_fork].is_available)
	{
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
		if (philo->state != WAITING)
			print_msg(philo, "is thinking", 1);
		philo->state = WAITING;
		return (1);
	}
	print_msg(philo, "has taken a fork", 1);
	print_msg(philo, "has taken a fork", 1);
	return (0);
}

/**
 * @brief Drops the forks held by the philosopher and makes 
 * them available for other philosophers to use.
 * 
 * @param philo Pointer to the philosopher struct.
 * @param left_fork Index of the left fork in the forks array.
 * @param right_fork Index of the right fork in the forks array.
 */
void	drop_forks(t_Philosopher *philo, int left_fork, int right_fork)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
		pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
	}
	else
	{
		pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
		pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
	}
	philo->sim->forks[left_fork].is_available = 1;
	philo->sim->forks[right_fork].is_available = 1;
	pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
	pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
}
