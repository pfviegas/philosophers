/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:51:44 by paulo             #+#    #+#             */
/*   Updated: 2023/09/25 16:23:06 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

/**
 * Changes the philosopher's state to THINKING and prints a message indicating 
 * that the philosopher is thinking.
 * If the philosopher should die, changes the philosopher's state to DEAD and 
 * prints a message indicating that the philosopher died.
 * 
 * @param philo The philosopher to perform the action on.
 */
void	think_philo(t_Philosopher *philo)
{
	if (!died(philo))
	{
		philo->state = THINKING;
		print_msg(philo, "is thinking");
	}
}

/**
 * The function sleep_philo makes the philosopher sleep for a certain 
 * amount of time.
 * If the philosopher should die while sleeping, the function sets the 
 * philosopher's state to DEAD, prints a message indicating that the 
 * philosopher died, and exits the program.
 * Otherwise, the function sets the philosopher's state to SLEEPING, 
 * prints a message indicating that the philosopher is sleeping, 
 * and sleeps for the specified amount of time.
 *
 * @param philo A pointer to the philosopher that will sleep.
 */
void	sleep_philo(t_Philosopher *philo)
{
	if (!will_die(philo))
	{
		philo->state = SLEEPING;
		print_msg(philo, "is sleeping");
		precise_sleep((philo->sim->time_to_sleep));
	}
}

/**
 * This function represents the action of a philosopher eating. 
 * It takes a pointer to a Philosopher struct as argument.
 * If the philosopher should die, it sets its state to DEAD 
 * and prints a message indicating that it died.
 * Otherwise, it tries to acquire the left and right forks, 
 * represented by mutex locks. 
 * If any of the forks is not available, it releases the acquired fork 
 * and sets its state to THINKING.
 * If both forks are available, it marks them as not available, 
 * sets its state to EATING, prints a message indicating that it is eating, 
 * sleeps for the specified time to eat, decreases the number of meals left, 
 * marks the forks as available again and sets its state to SLEEPING.
 * 
 * @param philo A pointer to a Philosopher struct representing 
 * the philosopher that is eating.
 */
void	eat_philo(t_Philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	if (!died(philo))
	{
		left_fork = philo->id - 1;
		right_fork = (philo->id) % philo->sim->num_philosophers;
		if (philo->id % 2)
		{
			pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
			if (!philo->sim->forks[left_fork].is_available)
			{
				pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
				philo->state = THINKING;
				print_msg(philo, "is thinking");
				return ;
			}
			pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
			if (!philo->sim->forks[right_fork].is_available) 
			{
				pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
				philo->state = THINKING;
				print_msg(philo, "is thinking");
				return ;
			}
			print_msg(philo, "has taken a fork");
			print_msg(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
			if (!philo->sim->forks[right_fork].is_available) 
			{
				pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
				philo->state = THINKING;
				print_msg(philo, "is thinking");
				return ;
			}
			pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
			if (!philo->sim->forks[left_fork].is_available)
			{
				pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
				philo->state = THINKING;
				print_msg(philo, "is thinking");
				return ;
			}
			print_msg(philo, "has taken a fork");
			print_msg(philo, "has taken a fork");
		}
		philo->sim->forks[left_fork].is_available = 0;
		philo->sim->forks[right_fork].is_available = 0;
		philo->last_meal_time = get_time_ms();
		philo->state = EATING;
		print_msg(philo, "is eating");
		precise_sleep((philo->sim->time_to_eat));
		philo->meals_left--;
		philo->sim->forks[left_fork].is_available = 1;
		philo->sim->forks[right_fork].is_available = 1;
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
		philo->state = SLEEPING;
	}
}

/**
 * @brief The function that represents the life of a philosopher.
 * 
 * @param arg A pointer to a t_Philosopher struct that contains the philosopher's information.
 * @return void* 
 */
void *philosopher_life(void *arg) 
{
	t_Philosopher *philo;

	philo = (t_Philosopher *)arg;
	if (philo->sim->num_philosophers == 1)
	{
		usleep(philo->sim->time_to_die * 1000);
		print_msg(philo, "died");
		return ((void *)0);
	}

	while (philo->meals_left != 0 && philo->sim->simulation_running == 1)
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}
