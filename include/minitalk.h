/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livsauze <livsauze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:20:23 by livsauze          #+#    #+#             */
/*   Updated: 2024/02/14 19:01:53 by livsauze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include "../utils/printf/ft_printf.h"

void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *));
void    ft_error(char *str);
void	ft_decode(int is_SIGUSR1, char *c, int bit_num);
void	ft_decode_int(int is_SIGUSR1, int *len, int bit_num);
int ft_get_len(int is_SIGUSR1);
int	ft_strlen(char *str);
int	ft_atoi(const char *str);

#endif