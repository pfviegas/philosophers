
// Função para imprimir mensagens
void print_message(Philosopher *philo, char *message) {
    pthread_mutex_lock(&philo->sim->print_lock);
    printf("%ld %d %s\n", total_time(philo->sim), philo->id, message);
    pthread_mutex_unlock(&philo->sim->print_lock);
}

// Função para calcular o tempo total decorrido
long total_time(Simulation *sim) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return ((current_time.tv_sec - sim->start_time.tv_sec) * 1000 +
            (current_time.tv_usec - sim->start_time.tv_usec) / 1000);
}

// Função para verificar se um filósofo deve morrer
int should_die(Philosopher *philo) {
    return (total_time(philo->sim) - philo->last_meal_time) > philo->sim->time_to_die;
}

// Função para realizar a ação de comer
void eat(Philosopher *philo) {
    if (should_die(philo)) {
        philo->state = DEAD;
        print_message(philo, "died");
        return;
    }

    philo->meals_left--;

    pthread_mutex_lock(&philo->sim->forks[philo->id]);
    print_message(philo, "has taken a fork");

    pthread_mutex_lock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);
    print_message(philo, "has taken a fork");

    philo->last_meal_time = total_time(philo->sim);
    philo->state = EATING;
    print_message(philo, "is eating");

    usleep(philo->sim->time_to_eat * 1000);

    pthread_mutex_unlock(&philo->sim->forks[philo->id]);
    pthread_mutex_unlock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);

    philo->state = SLEEPING;
}

// Função para realizar a ação de dormir
void sleep(Philosopher *philo) {
    if (should_die(philo)) {
        philo->state = DEAD;
        print_message(philo, "died");
        return;
    }

    philo->state = SLEEPING;
    print_message(philo, "is sleeping");
    usleep(philo->sim->time_to_sleep * 1000);
}

// Função para realizar a ação de pensar
void think(Philosopher *philo) {
    if (should_die(philo)) {
        philo->state = DEAD;
        print_message(philo, "died");
        return;
    }

    philo->state = THINKING;
    print_message(philo, "is thinking");
}

// Função que define o ciclo de vida de um filósofo
void *philosopher_life(void *arg) {
    Philosopher *philo = (Philosopher *)arg;

    while (philo->meals_left != 0) {
        think(philo);
        eat(philo);
        sleep(philo);
    }

    return NULL;
}

// Função para criar e iniciar a simulação
void run_simulation(Simulation *sim, Philosopher *philosophers) {
    pthread_mutex_init(&sim->print_lock, NULL);

    // Inicialização dos garfos
    for (int i = 0; i < sim->num_philosophers; i++) {
        pthread_mutex_init(&sim->forks[i], NULL);
    }

    gettimeofday(&sim->start_time, NULL);

    // Criação das threads para os filósofos
    for (int i = 0; i < sim->num_philosophers; i++) {
        pthread_create(&philosophers[i].thread, NULL, philosopher_life, &philosophers[i]);
    }

    // Aguarda o término das threads
    for (int i = 0; i < sim->num_philosophers; i++) {
        pthread_join(philosophers[i].thread, NULL);
    }
}

```

Esta versão do código é mais legível e modular, tornando mais fácil entender as ações de cada filósofo e a lógica da simulação. Além disso, foram adicionados comentários explicativos para ajudar na compreensão do código.