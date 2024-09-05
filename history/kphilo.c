long long get_current_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}

void print_status(t_list *philo, char *message) {
    long long time_stamp = get_current_time();
    pthread_mutex_lock(philo->output_lock);
    printf("%lld %d %s\n", time_stamp, philo->id, message);
    pthread_mutex_unlock(philo->output_lock);
}

void *monitor(void *arg) {
    t_list *philo = (t_list *)arg;
    
    while (1) {
        usleep(1000);  // Check every 1 ms
        if (get_current_time() - philo->last_meal_time > philo->time_to_die) {
            print_status(philo, "died");
            return (NULL);  // Immediately stop the program on death
        }
    }
    return NULL;
}

void *philosopher_lifecycle(void *arg) {
    t_list *philo = (t_list *)arg;

    pthread_create(&philo->monitor_thread, NULL, monitor, philo);

    while (1) {
        // Think
        print_status(philo, "is thinking");

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

        // Sleep
        print_status(philo, "is sleeping");
        usleep(philo->time_to_sleep * 1000);  // Convert ms to us

        // Check if the philosopher has eaten enough
        if (philo->times_must_eat != -1 && philo->times_eaten >= philo->times_must_eat) {
            break;
        }
    }

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
    int i = 0;

    pthread_mutex_init(&output_lock, NULL);
    while (i < num_philo) {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }

    i = 0;
    while (i < num_philo) {
        philo[i].id = i + 1;
        philo[i].time_to_die = time_to_die;
        philo[i].time_to_eat = time_to_eat;
        philo[i].time_to_sleep = time_to_sleep;
        philo[i].times_must_eat = time_must_eat;
        philo[i].times_eaten = 0;
        philo[i].left_fork = &forks[i];
        philo[i].right_fork = &forks[(i + 1) % num_philo];
        philo[i].last_meal_time = get_current_time();
        philo[i].output_lock = &output_lock;
        pthread_create(&th[i], NULL, philosopher_lifecycle, &philo[i]);
        i++;
    }

    i = 0;
    while (i < num_philo) {
        pthread_join(th[i], NULL);
        pthread_join(philo[i].monitor_thread, NULL);
        i++;
    }

    i = 0;
    while (i < num_philo) {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }

    pthread_mutex_destroy(&output_lock);

    return 0;
}
