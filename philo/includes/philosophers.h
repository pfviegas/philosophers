/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/25 16:08:42 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atualizar cabeçalho

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
	pthread_mutex_t	simulation_lock;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meals;
	int				simulation_running;
}	t_Simulation;

// Estrutura de dados para um filósofo
typedef struct s_Philosopher
{
	int						id;
	int						meals_left;
	enum e_PhilosopherState	state;
	long					last_meal_time;
	t_Simulation			*sim;
	pthread_t				thread;
}	t_Philosopher;

int		check_argc(int argc);

int		check_argv(char *argv[]);

// Função para converter char em int
int		ft_atoi(const char *str);

// Função para verificar se um caractere é um dígito decimal.
int		ft_isdigit(int c);

// Função para inicializar as variaveis da simulação
void	init_var_sim(t_Simulation *simulation, int argc, char *argv[]);

// Função para inicializar os filósofos
void	create_philisophers(t_Simulation *simulation, t_Philosopher *philosopher);

// Função para criar e iniciar a simulação
void	run_simulation(t_Simulation *sim, t_Philosopher *philosophers);

// Função que define o ciclo de vida de um filósofo
void	*philosopher_life(void *arg);

// Função para realizar a ação de comer
void	eat_philo(t_Philosopher *philo);

// Função para verificar se um filósofo deve morrer
int			died(t_Philosopher *philo);

// Função para verificar se um filósofo vai morrer durante o sono
int	will_die(t_Philosopher *philo);

// Função para imprimir mensagens
void		print_msg(t_Philosopher *philo, char *message);

// Função para calcular o tempo total decorrido
long int	get_time_ms(void);

// Função para realizar a ação de pensar
void		think_philo(t_Philosopher *philo);

// Função para realizar a ação de dormir
void		sleep_philo(t_Philosopher *philo);

void	precise_sleep(long int miliseconds);
#endif
