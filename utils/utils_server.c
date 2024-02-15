/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livsauze <livsauze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:17:42 by livsauze          #+#    #+#             */
/*   Updated: 2024/02/14 19:02:08 by livsauze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minitalk.h"

void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	susr;

	susr.sa_sigaction = handler;
	susr.sa_flags = SA_SIGINFO;
	sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}

void	ft_decode(int is_SIGUSR1, char *c, int bit_num)
{
	if (is_SIGUSR1)
		*c |= 1 << bit_num;
	else
		*c &= ~(1 << bit_num);
}

void	ft_decode_int(int is_SIGUSR1, int *len, int bit_num)
{
	if (is_SIGUSR1)
		*len |= 1 << bit_num;
	else
		*len &= ~(1 << bit_num);
}
