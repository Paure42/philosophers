/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:16:10 by paure             #+#    #+#             */
/*   Updated: 2021/01/27 11:16:11 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct			s_philo_values
{
	int					nphilo;
	int					timetodie;
	int					timetoeat;
	int					timetosleep;
	int					neating;
	struct timeval		sim_start_time;
	sem_t				*sem_speak;
	sem_t				*sem_forks;
	sem_t				*sem_death;
	sem_t				*sem_check_death;
	sem_t				*sem_fork_checking;
	sem_t				*sem_eat_count_all;
	pid_t				pid_check_neating;
}						t_values;

typedef struct			s_philo_tab
{
	t_values			*values;
	pid_t				philosopher;
	pthread_t			death_t;
	struct timeval		eat_start_time;
	struct timeval		sleep_start_time;
	long int			eat_timer;
	int					current_philo;
	int					eat_count;
	long int			sim_time_death;
	sem_t				*sem_eating;
	char				*str_philo;
	bool				exit;
}						t_philo;

typedef struct			s_thread_monitor
{
	t_philo				**philo;
}						t_monitor;

int						main(int argc, char **argv);
int						ft_atoi(const char *str);
int						ft_philo_three(t_values *values);
int						exit_failure(int exit);
long int				get_timer(struct timeval start_time);
long int				get_sim_time(t_philo *philo);
void					print_state(t_philo *philo, char *str_philo, int state);
void					taking_forks(t_philo *philo);
void					drop_fork(t_philo *philo);
void					is_eating(t_philo *philo);
void					is_sleeping(t_philo *philo);
void					is_thinking(t_philo *philo);
void					*is_starving(void *args);
void					print_death(t_philo *philo, char *str_philo,
							long int death_time);
int						clear_philo(t_philo **philo, int nphilo);
int						exit_failure(int exit);
int						init_values(t_values *values);
t_philo					**init_philosophers(t_philo **philo, t_values *values);
int						close_semaphore(t_values *values);
char					*sem_name(int count);
char					*ft_itoa(int n);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlen(const char *s);
char					*ft_strcat(char *s1, char *s2);
void					ft_putstr_fd(char *s, int fd);
#endif
