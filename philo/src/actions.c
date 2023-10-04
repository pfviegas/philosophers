/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:51:44 by paulo             #+#    #+#             */
/*   Updated: 2023/10/04 16:32:20 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

#include "../includes/philosophers.h"

void	think_philo(t_Philosopher *philo)
{
	philo->state = THINKING;
	print_msg(philo, "is thinking");
}

void	sleep_philo(t_Philosopher *philo)
{
	philo->state = SLEEPING;
	print_msg(philo, "is sleeping");
	action_philo(philo->sim->time_to_sleep, philo);
}

void	eat_philo(t_Philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->sim->num_philosophers;
	if (philo->id % 2)
	{
//		pthread_mutex_lock(&philo->sim->meals_lock);
		pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
		if (!philo->sim->forks[left_fork].is_available)
		{
			philo->state = THINKING;
//			pthread_mutex_unlock(&philo->sim->meals_lock);
			pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
			print_msg(philo, "is thinking");
			return ;
		}
		pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
		if (!philo->sim->forks[right_fork].is_available) 
		{
			philo->state = THINKING;
//			pthread_mutex_unlock(&philo->sim->meals_lock);
			pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
			print_msg(philo, "is thinking");
			return ;
		}
		print_msg(philo, "has taken a fork");
		print_msg(philo, "has taken a fork");
	}
	else
	{
//		pthread_mutex_lock(&philo->sim->meals_lock);
		pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
		if (!philo->sim->forks[right_fork].is_available) 
		{
			philo->state = THINKING;
//			pthread_mutex_unlock(&philo->sim->meals_lock);
			pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
			print_msg(philo, "is thinking");
			return ;
		}
		pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
		if (!philo->sim->forks[left_fork].is_available)
		{
			philo->state = THINKING;
//			pthread_mutex_unlock(&philo->sim->meals_lock);
			pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
			print_msg(philo, "is thinking");
			return ;
		}
		print_msg(philo, "has taken a fork");
		print_msg(philo, "has taken a fork");
	}
	philo->sim->forks[left_fork].is_available = 0;
	philo->sim->forks[right_fork].is_available = 0;
	pthread_mutex_lock(&philo->sim->meals_lock);
	philo->last_meal_time = get_time_ms();
	philo->state = EATING;
	philo->meals_left--;
	pthread_mutex_unlock(&philo->sim->meals_lock);
	print_msg(philo, "is eating");
	action_philo(philo->sim->time_to_eat, philo);
	philo->sim->forks[left_fork].is_available = 1;
	philo->sim->forks[right_fork].is_available = 1;
	pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
	pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
}

void *philosopher_life(void *arg) 
{
	t_Philosopher *philo;

	philo = (t_Philosopher *)arg;
	if (philo->sim->num_philosophers == 1)
	{
		print_msg(philo, "is thinking");
		usleep(philo->sim->time_to_die * 1000);
		print_msg(philo, "died");
		return ((void *)0);
	}
	if (!(philo->id % 2))
		usleep(100);
	while (philo->meals_left != 0 && philo->sim->simulation_running == 1)
	{
		if (died(philo))
			break ;
		if (philo->state == THINKING)
			eat_philo(philo);
		else if (philo->state == EATING)
			sleep_philo(philo);
		else if (philo->state == SLEEPING)
			think_philo(philo);
	}
	return (NULL);
}
