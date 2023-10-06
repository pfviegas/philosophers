/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:27:41 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/06 18:14:47 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	grab_left_fork(t_Philosopher *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
	if (!philo->sim->forks[left_fork].is_available)
	{
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		if (philo->state != WAITING)
			print_msg(philo, "is thinking", 1);
		philo->state = WAITING;
		return ;
	}
	pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
	if (!philo->sim->forks[right_fork].is_available) 
	{
		pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		if (philo->state != WAITING)
			print_msg(philo, "is thinking", 1);
		philo->state = WAITING;
		return ;
	}
	print_msg(philo, "has taken a fork", 1);
	print_msg(philo, "has taken a fork", 1);
}

void	grab_right_fork(t_Philosopher *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->sim->forks[right_fork].lock);
	if (!philo->sim->forks[right_fork].is_available) 
	{
		pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
		if (philo->state != WAITING)
			print_msg(philo, "is thinking", 1);
		philo->state = WAITING;
		return ;
	}
	pthread_mutex_lock(&philo->sim->forks[left_fork].lock);
	if (!philo->sim->forks[left_fork].is_available)
	{
		pthread_mutex_unlock(&philo->sim->forks[left_fork].lock);
		pthread_mutex_unlock(&philo->sim->forks[right_fork].lock);
		if (philo->state != WAITING)
			print_msg(philo, "is thinking", 1);
		philo->state = WAITING;
		return ;
	}
	print_msg(philo, "has taken a fork", 1);
	print_msg(philo, "has taken a fork", 1);
}
