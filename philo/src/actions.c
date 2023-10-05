/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:33:38 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/05 15:08:43 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	think_philo(t_Philosopher *philo)
{
	philo->state = THINKING;
	print_msg(philo, "is thinking", 1);
}

void	sleep_philo(t_Philosopher *philo)
{
	philo->state = SLEEPING;
	print_msg(philo, "is sleeping", 1);
	action_philo(philo->sim->time_to_sleep, philo);
	usleep(100);
}

void	eat_philo(t_Philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->sim->num_philosophers;
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
		if (!philo->sim->forks[left_fork].is_available)
		{
			philo->state = WAITING;
			pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
			if (philo->state != WAITING)
				print_msg(philo, "is thinking", 1);
			return ;
		}
		pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
		if (!philo->sim->forks[right_fork].is_available) 
		{
			philo->state = WAITING;
			pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
			pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
			if (philo->state != WAITING)
				print_msg(philo, "is thinking", 1);
			return ;
		}
		print_msg(philo, "has taken a fork", 1);
		print_msg(philo, "has taken a fork", 1);
	}
	else
	{
		pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
		if (!philo->sim->forks[right_fork].is_available) 
		{
			philo->state = WAITING;
			pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
			if (philo->state != WAITING)
				print_msg(philo, "is thinking", 1);
			return ;
		}
		pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
		if (!philo->sim->forks[left_fork].is_available)
		{
			philo->state = WAITING;
			pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
			pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
			if (philo->state != WAITING)
				print_msg(philo, "is thinking", 1);
			return ;
		}
		print_msg(philo, "has taken a fork", 1);
		print_msg(philo, "has taken a fork", 1);
	}
	philo->sim->forks[left_fork].is_available = 0;
	philo->sim->forks[right_fork].is_available = 0;
	pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
	pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
	
	pthread_mutex_lock(&philo->sim->meals_lock);
	philo->last_meal_time = get_time_ms(&philo->sim->time_lock);
	philo->state = EATING;
	philo->meals_left--;
	pthread_mutex_unlock(&philo->sim->meals_lock);
	print_msg(philo, "is eating", 1);
	action_philo(philo->sim->time_to_eat, philo);
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

void *philosopher_life(void *arg) 
{
	t_Philosopher *philo;

	philo = (t_Philosopher *)arg;
	if (philo->sim->num_philosophers == 1)
	{
		print_msg(philo, "is thinking", 1);
		usleep(philo->sim->time_to_die * 1000);
		print_msg(philo, "died", 1);
		return ((void *)0);
	}
	if (!(philo->id % 2))
		usleep(100);
//	while (philo->meals_left != 0 && philo->sim->simulation_running == 1)
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
