/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livsauze <livsauze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:44:12 by livsauze          #+#    #+#             */
/*   Updated: 2024/02/14 19:04:00 by livsauze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"

int	g_bit = 0;

void	ft_handle_bit(siginfo_t *sinfo, int *bit_num)
{
	if (kill(sinfo->si_pid, 0) < 0)
		ft_error("Impossible to send signal to client\n");
	if (*bit_num < 0)
	{
		if (g_bit)
			*bit_num = 7;
		else
			*bit_num = 31;
	}
}

void	ft_print_str(char **str, int *i, siginfo_t *sinfo)
{
	(*str)[*i] = '\0';
	ft_printf("\nMessage received : \n%s\n", *str);
	free(*str);
	*str = NULL;
	g_bit = 0;
	*i = 0;
	kill(sinfo->si_pid, SIGUSR2);
}

void	ft_malloc_str(char **str, int len, int bit_num)
{
	if (!bit_num)
	{
		*str = malloc(sizeof(char) * len + 1);
		g_bit = 1;
	}
}

void	ft_handler(int signum, siginfo_t *sinfo, void *context)
{
	static char *str;
	static char c;
	static int	bit_num = -1;
	static int len = 0;
	static int i = 0;

	(void) context;
	ft_handle_bit(sinfo, &bit_num);
	if (g_bit)
		ft_decode(signum == SIGUSR1, &c, bit_num);
	else
		ft_decode_int(signum == SIGUSR1, &len, bit_num);
	if (g_bit)
	{
		if (bit_num == 0 && c)
			str[i++] = c;
		else if (!bit_num && !c)
			ft_print_str(&str, &i, sinfo);
	}
	else
		ft_malloc_str(&str, len, bit_num);
	bit_num--;
	kill(sinfo->si_pid, SIGUSR1);
}

int	main(void)
{
	init_sig(SIGUSR1, &ft_handler);
	init_sig(SIGUSR2, &ft_handler);
	ft_printf("PID Server : %d\n", getpid());
	while (1)
		sleep(1);
	return (0);
}