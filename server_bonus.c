/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-moun <eel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:50:11 by eel-moun          #+#    #+#             */
/*   Updated: 2022/04/21 15:52:45 by eel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int	ft_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*str;
	int			j;
	long int	num;

	num = n;
	j = ft_size(num);
	str = (char *)malloc((j + 1) * sizeof(char));
	i = j - 1;
	while (i >= 0)
	{
		str[i] = (num % 10) + 48;
		i--;
		num = num / 10;
	}
	str[j] = '\0';
	return (str);
}

void	sig_handler(int signum, siginfo_t *info, void *tst)
{
	static int	client_pid;
	static char	c;
	static int	bit;

	(void)tst;
	if (info->si_pid != client_pid || bit == 0)
	{
		c = 0xFF;
		bit = 0;
	}
	if (signum == SIGUSR2)
		c ^= 128 >> bit;
	else
		c |= 128 >> bit;
	bit++;
	if (bit == 8)
	{
		bit = 0;
		write(1, &c, 1);
		if (!c)
			kill(info->si_pid, SIGUSR1);
		c = 0xFF;
	}
	client_pid = info->si_pid;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	write(1, ft_itoa(getpid()), ft_size(getpid()));
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
