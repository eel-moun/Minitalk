/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-moun <eel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:50:00 by eel-moun          #+#    #+#             */
/*   Updated: 2022/04/21 16:10:31 by eel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str >= 48 && *str <= 57)
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	return (res);
}

void	sig_sender(char *str, pid_t pid)
{
	int	bitshift;

	bitshift = -1;
	while (1)
	{
		while (++bitshift < 8)
		{
			if (*str & (128 >> bitshift))
			{	
				if (kill(pid, SIGUSR1) == -1)
					exit(1);
				usleep(400);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(1);
				usleep(400);
			}
		}
		if (*str == '\0')
			break ;
		str++;
		bitshift = -1;
	}
}

void	success_msg(int signum)
{
	(void)signum;
	write(1, "ok", 2);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	pid_t	pid ;

	if (argc != 3)
		return (0);
	signal(SIGUSR1, success_msg);
	if (!(argv[1][0] >= '0' && argv[1][0] <= '9'))
		return (0);
	if (!argv[2])
		return (0);
	pid = ft_atoi(argv[1]);
	sig_sender(argv[2], pid);
	return (0);
}
