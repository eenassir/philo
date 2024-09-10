
long long get_current_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}

void print_status(t_list *philo, char *message) {
    long long time_stamp = get_current_time() - philo->start;
    pthread_mutex_lock(philo->output_lock);
    if (*(philo->simulation_running)) {
        printf("%lld %d %s\n", time_stamp, philo->id, message);
        if (strcmp(message, "died") == 0) {
            *(philo->simulation_running) = 0;  // Stop the simulation when a philosopher dies
        }
    }
    pthread_mutex_unlock(philo->output_lock);
}

void *monitor(void *arg) {
    t_list *philo = (t_list *)arg;

    while (*(philo->simulation_running)) {
        usleep(1000);  // Check every 1 ms
        if (get_current_time() - philo->last_meal_time > philo->time_to_die) {
            print_status(philo, "died");
            return NULL;
        }
    }
    return NULL;
}

void *philosopher_lifecycle(void *arg) {
    t_list *philo = (t_list *)arg;

    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor, philo);

    while (*(philo->simulation_running)) {
        print_status(philo, "is thinking");

        if (philo->num_philo == 1) {
            // Single philosopher case
            print_status(philo, "has taken a fork");
            usleep(philo->time_to_die * 1000);  // Wait for the philosopher to "die"
            print_status(philo, "died");
            break;
        }

        // Pick up forks (mutex lock)
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");

        // Eat
        philo->last_meal_time = get_current_time();
        print_status(philo, "is eating");
        usleep(philo->time_to_eat * 1000);  // Convert ms to us
        philo->times_eaten++;

        // Put down forks (mutex unlock)
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Check if the philosopher has eaten enough
        if (philo->times_must_eat != -1 && philo->times_eaten >= philo->times_must_eat) {
            break;
        }

        // Sleep
        print_status(philo, "is sleeping");
        usleep(philo->time_to_sleep * 1000);  // Convert ms to us
    }

    pthread_join(monitor_thread, NULL);

    return NULL;
}

int main(int ac, char **av) {
    if (ac < 5 || ac > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]);
        return 1;
    }

    int num_philo = atoi(av[1]);
    int time_to_die = atoi(av[2]);
    int time_to_eat = atoi(av[3]);
    int time_to_sleep = atoi(av[4]);
    int time_must_eat = (ac == 6) ? atoi(av[5]) : -1;

    if (num_philo < 1 || time_to_die < 60 || time_to_eat < 60 || time_to_sleep < 60) {
        printf("Error: Invalid input values. Please ensure all times are >= 60 ms.\n");
        return 1;
    }

    pthread_t th[num_philo];
    pthread_mutex_t forks[num_philo];
    pthread_mutex_t output_lock;
    t_list philo[num_philo];
    int simulation_running = 1;
    int i;

    pthread_mutex_init(&output_lock, NULL);
    for (i = 0; i < num_philo; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    long long start_time = get_current_time();
    for (i = 0; i < num_philo; i++) {
        philo[i].id = i + 1;
        philo[i].num_philo = num_philo;
        philo[i].time_to_die = time_to_die;
        philo[i].time_to_eat = time_to_eat;
        philo[i].time_to_sleep = time_to_sleep;
        philo[i].times_must_eat = time_must_eat;
        philo[i].times_eaten = 0;
        philo[i].left_fork = &forks[i];
        philo[i].right_fork = &forks[(i + 1) % num_philo];
        philo[i].last_meal_time = start_time;
        philo[i].start = start_time;
        philo[i].output_lock = &output_lock;
        philo[i].simulation_running = &simulation_running;
        pthread_create(&th[i], NULL, philosopher_lifecycle, &philo[i]);
    }

    for (i = 0; i < num_philo; i++) {
        pthread_join(th[i], NULL);
    }

    for (i = 0; i < num_philo; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    pthread_mutex_destroy(&output_lock);

    return 0;
}

