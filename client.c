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
			ft_printf("PID must be only numbers.\n");
			return (0);
		}
	}
	*pid = ft_atoi(str);
	if (*pid < 2)
	{
		ft_printf("PID isn't a valid process.\n");
		return (0);
	}
	return (1);
}

/* Sends a int via SIGUSR1 (bit 0) and SIGUSR2 (bit 1). */
static int	send_int(int pid, int str_size)
{
	int	i;

	i = 32;
	while (--i >= 0)
	{
		if (!((str_size >> i) & 1))
		{
			if ((kill(pid, SIGUSR1)) == -1)
			{
				ft_printf("Kill function returned an error.\n");
				return (0);
			}
		}
		else
		{
			if ((kill(pid, SIGUSR2)) == -1)
			{
				ft_printf("Kill function returned an error.\n");
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

int	main(int argc, char **argv)
{
	int	pid;
	int	str_size;

	if (argc != 3)
	{
		ft_printf("Invalid number of arguments.\n");
		exit (1);
	}
	if (!check_pid(argv[1], &pid))
		exit (1);
	str_size = ft_strlen(argv[2]);
	if (!send_int(pid, str_size))
		exit (1);
	if (!send_str(pid, argv[2]))
	{
		ft_printf("Kill function returned an error.\n");
		exit (1);
	}
	exit (0);
}
