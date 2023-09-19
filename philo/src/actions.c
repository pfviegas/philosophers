/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:51:44 by paulo             #+#    #+#             */
/*   Updated: 2023/09/19 16:03:40 by pviegas          ###   ########.fr       */
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
	if (!should_die(philo))
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
	if (!should_die(philo))
	{
		philo->state = SLEEPING;
		print_msg(philo, "is sleeping");
		usleep(philo->sim->time_to_sleep * 1000);
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

	if (!should_die(philo))
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
				return ;
			}
			print_msg(philo, "has taken a fork");
			pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
			if (!philo->sim->forks[right_fork].is_available) 
			{
				pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
				philo->state = THINKING;
				return ;
			}
			print_msg(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
			if (!philo->sim->forks[right_fork].is_available) 
			{
				pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
				philo->state = THINKING;
				return ;
			}
			print_msg(philo, "has taken a fork");
			pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
			if (!philo->sim->forks[left_fork].is_available)
			{
				pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
				philo->state = THINKING;
				return ;
			}
			print_msg(philo, "has taken a fork");
		}
		philo->sim->forks[left_fork].is_available = 0;
		philo->sim->forks[right_fork].is_available = 0;
		philo->last_meal_time = total_time(philo->sim);
		philo->state = EATING;
		print_msg(philo, "is eating");
		usleep(philo->sim->time_to_eat * 1000);
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
	while (philo->meals_left != 0)
	{
		pthread_mutex_lock(&philo->sim->print_lock);
		if (philo->sim->simulation_running == 0)
		{
			pthread_mutex_unlock(&philo->sim->print_lock);
			break;
		}
		pthread_mutex_unlock(&philo->sim->print_lock);
		
		eat_philo(philo);
		pthread_mutex_lock(&philo->sim->print_lock);
		if (philo->sim->simulation_running == 0)
		{
			pthread_mutex_unlock(&philo->sim->print_lock);
			break;
		}
		pthread_mutex_unlock(&philo->sim->print_lock);

		sleep_philo(philo);
		pthread_mutex_lock(&philo->sim->print_lock);
		if (philo->sim->simulation_running == 0)
		{
			pthread_mutex_unlock(&philo->sim->print_lock);
			break;
		}
		pthread_mutex_unlock(&philo->sim->print_lock);
		think_philo(philo);
	}
	return (NULL);
}
