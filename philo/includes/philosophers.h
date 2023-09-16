/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:20:16 by paulo             #+#    #+#             */
/*   Updated: 2023/09/16 15:35:26 by paulo            ###   ########.fr       */
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

// Definições de constantes
# define MAX_PHILOSOPHERS 200

// Enumeração para estados dos filósofos
enum e_PhilosopherState {
	THINKING,
	EATING,
	SLEEPING,
	DEAD
};

// Estrutura de dados para a simulação
typedef struct s_Simulation {
	struct timeval	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	pthread_t		checker;
}	t_Simulation;

// Estrutura de dados para um filósofo
typedef struct s_Philosopher {
	int						id;
	int						meals_left;
	enum e_PhilosopherState	state;
	long					last_meal_time;
	t_Simulation			*sim;
	pthread_t				thread;
}	t_Philosopher;

// Função para imprimir a mensagem de erro e sair
void	quit(char *s, int exit_code);

// Função para converter char em int
int		ft_atoi(const char *str);

// Função para verificar se um caractere é um dígito decimal.
int		ft_isdigit(int c);

// Função para inicializar as variaveis da simulação
void init_var_sim(t_Simulation *simulation, int argc, char *argv[]);

// Função para inicializar os filósofos
void create_philisophers(t_Simulation *simulation, t_Philosopher *philosopher);
/*
// Função para imprimir mensagens
void	print_message(t_Philosopher *philo, char *message);

// Função para calcular o tempo total decorrido
long	total_time(t_Simulation *sim);

// Função para verificar se um filósofo deve morrer
int		should_die(t_Philosopher *philo);

// Função para realizar a ação de comer
void	eat(t_Philosopher *philo);

// Função para realizar a ação de dormir
void	sleep(t_Philosopher *philo);

// Função para realizar a ação de pensar
void	think(t_Philosopher *philo);

// Função que define o ciclo de vida de um filósofo
void	*philosopher_life(void *arg);

// Função para criar e iniciar a simulação
void	run_simulation(t_Simulation *sim, t_Philosopher *philosophers);

*/
#endif
