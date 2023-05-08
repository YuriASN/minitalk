#include "minitalk.h"

/* Return TRUE if PID is all digits or FALSE if anything else is found. */
static int	check_pid(char *str, int *pid)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit((int)str[i]))
		{
			write(1, "PID must be only numbers.\n", 26);
			return (0);
		}
	}
	*pid = ft_atoi(str);
	if (*pid < 2)
	{
		write(1, "PID isn't a valid process.\n", 27);
		return (0);
	}
	return (1);
}

/* Sends a int via SIGUSR1 (bit 0) and SIGUSR2 (bit 1). */
static int	send_int(int pid, int nbr)
{
	int	i;

	i = 32;
	while (--i >= 0)
	{
		if (!((nbr >> i) & 1))
		{
			if ((kill(pid, SIGUSR1)) == -1)
			{
				write(1, "Kill function returned an error.\n", 33);
				return (0);
			}
		}
		else
		{
			if ((kill(pid, SIGUSR2)) == -1)
			{
				write(1, "Kill function returned an error.\n", 33);
				return (0);
			}
		}
		usleep(100);
	}
	return (1);
}

/* Sends a string via SIGUSR1 (bit 0) and SIGUSR2 (bit 1). */
static int	send_str(int pid, char *str)
{
	unsigned char	c;
	int				i;
	int				j;

	j = -1;
	while (str[++j])
	{
		i = 8;
		c = (unsigned char)str[j];
		while (--i >= 0)
		{
			if (!((c >> i) & 1))
			{
				if ((kill(pid, SIGUSR1)) == -1)
					return (0);
			}
			else
			{
				if ((kill(pid, SIGUSR2)) == -1)
					return (0);
			}
			usleep(100);
		}
	}
	return (1);
}

/* Print msg received and close client. */
static void	msg_received(int x)
{
	if (x == SIGUSR1)
	{
		write(1, "Server received your message!\n", 30);
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sas;

	sas.sa_handler = &msg_received;
	if (argc != 3)
	{
		write(1, "Invalid number of arguments.\n", 29);
		exit (1);
	}
	if (!check_pid(argv[1], &pid))
		exit (1);
	if (!send_int(pid, ft_strlen(argv[2])))
		exit (1);
	if (!send_int(pid, getpid()))
		exit (1);
	if (!send_str(pid, argv[2]))
	{
		write(1, "Kill function returned an error.\n", 33);
		exit (1);
	}
	while (1)
		sigaction(SIGUSR1, &sas, NULL);
	exit (0);
}
