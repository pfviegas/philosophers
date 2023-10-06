/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:54:27 by pviegas           #+#    #+#             */
/*   Updated: 2023/10/06 18:14:00 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

// Enumeração para estados dos filósofos
enum e_PhilosopherState {
	THINKING,
	WAITING,
	EATING,
	SLEEPING,
	DEAD
};

// Estrutura de dados para um garfo
typedef struct s_Fork
{
	pthread_mutex_t	lock;
	int				is_available;
}	t_Fork;

// Estrutura de dados para a simulação
typedef struct s_Simulation
{
	long int		start_time;
	t_Fork			*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	time_lock;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meals;
	int				simulation_running;
	pthread_mutex_t	simulation_lock;
	pthread_mutex_t	start_time_lock;
}	t_Simulation;

// Estrutura de dados para um filósofo
typedef struct s_Philosopher
{
	int						id;
	enum e_PhilosopherState	state;
	long					last_meal_time;
	long					start_time;
	int						meals_left;
	t_Simulation			*sim;
	pthread_t				thread;
}	t_Philosopher;

void	check_args(int argc, char *argv[]);
void	check_argc(int argc, char *argv[]);
void	check_argv(char *argv[]);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	init_var_sim(t_Simulation *sim, int argc, char *argv[]);
int		init_mutexes(t_Simulation *sim);
void	create_philos(t_Simulation *sim, t_Philosopher *philosopher);
void	run_simulation(t_Simulation *sim, t_Philosopher *philosophers);
void	*philosopher_life(void *arg);
void	eat_philo(t_Philosopher *philo);
int		died(t_Philosopher *philo);
void	print_msg(t_Philosopher *philo, char *message, int sim_lock);
long	get_time_ms(void);
void	think_philo(t_Philosopher *philo);
void	sleep_philo(t_Philosopher *philo);
void	action_philo(long int time, t_Philosopher *philo);
void	destroy_mutexes(t_Simulation *sim);
int		one_philo(t_Philosopher *philo);
void	grab_left_fork(t_Philosopher *philo, int left_fork, int right_fork);
void	grab_right_fork(t_Philosopher *philo, int left_fork, int right_fork);
#endif
