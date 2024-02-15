/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livsauze <livsauze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:20:39 by livsauze          #+#    #+#             */
/*   Updated: 2024/02/15 13:11:00 by livsauze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"

static int	g_bit;

void	ft_send_strlen(char *str, pid_t pid)
{
	int	len;
	int	bit_num;

	len = ft_strlen(str);
	bit_num = 31;
	while (bit_num >= 0)
	{
		if (kill(pid, 0) < 0)
			ft_printf("Can't send sig to pid server");
		g_bit = 0;
		if (len & (1 << bit_num))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit_num--;
		while (g_bit != 1)
			usleep(1000000);
	}
}

void	ft_send_char(char c, pid_t pid)
{
	int	bit_num;

	bit_num = 7;
	while (bit_num >= 0)
	{
		if (kill(pid, 0) < 0)
			ft_error("Can't send sig to pid server");
		g_bit = 0;
		if (c & (1 << bit_num))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit_num--;
		while (g_bit != 1)
			usleep(100);
	}
}

void	ft_send_string(char *str, pid_t pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_send_char(str[i], pid);
		i++;
	}
	ft_send_char('\0', pid);
}

void	ft_handler(int sig)
{
	if (sig == SIGUSR1)
		g_bit = 1;
	else if (sig == SIGUSR2)
	{
		ft_printf("\n Message sent !\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	pid_t	serv_pid;

	if (ac != 3)
		ft_error("Wrong parameters please use : ./client <pid> <text>\n");
	signal(SIGUSR1, &ft_handler);
	signal(SIGUSR2, &ft_handler);
	serv_pid = ft_atoi(av[1]);
	if (!serv_pid)
		ft_error("Invalid PID");
	ft_send_strlen(av[2], serv_pid);
	ft_send_string(av[2], serv_pid);
	while (1)
		sleep (1);
}
