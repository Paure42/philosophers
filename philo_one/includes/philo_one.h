/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:04:13 by paure             #+#    #+#             */
/*   Updated: 2021/01/26 13:04:15 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct			s_philo_values
{
	int					nphilo;
	int					timetodie;
	int					timetoeat;
	int					timetosleep;
	int					neating;
	int					nodd;
	int					neven;
	struct timeval		sim_start_time;
	pthread_mutex_t		speak;
	pthread_mutex_t		fork_mutex_checking;
	pthread_mutex_t		mutex_death;
	pthread_mutex_t		eat_mutex_checking;
	bool				even_checking;
	bool				odd_checking;
	bool				last_checking;
	bool				exit;
	int					count_odd;
	int					count_even;
	int					*list_eat;
}						t_values;

typedef struct			s_philo_tab
{
	t_values			*values;
	pthread_t			philosopher;
	pthread_t			death_t;
	pthread_mutex_t		eat_mutex;
	struct timeval		eat_start_time;
	struct timeval		sleep_start_time;
	struct timeval		counter_time;
	char				*str_philo;
	long int			eat_timer;
	long int			sleep_timer;
	int					hold_fork_right;
	int					hold_fork_left;
	int					current_philo;
	int					is_checking;
	int					is_odd;
	int					is_last;
	int					is_even;
	int					eat_count;
}						t_philo;

int						main(int argc, char **argv);
int						ft_atoi(const char *str);
int						ft_strlen(char *s);
int						ft_philo_one(t_values *values);
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
int						*reinit_list_eat(int *list_eat, int n, int len);
int						clear_values(t_values *values, int ret, int mutex);
int						clear_philo(t_philo **philo, int nphilo);
int						exit_failure(int exit);
int						init_values(t_values *values);
t_philo					**init_philosophers(t_philo **philo, t_values *values);
int						destroy_mutex(t_values *values, int n);
void					ft_putstr_fd(char *s, int fd);
char					*ft_itoa(int n);
char					*ft_strcat(char *s1, char *s2);
#endif
