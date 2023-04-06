#include "minitalk.h"

/* Transforms the first 32 bits on a int that contains the string size.
When done, it restore index and value after atrributing it to nbr. */
static void	get_nbr(int sig, int *nbr)
{
	static int	i;
	static int	value;

	if (sig == SIGUSR2)
		value |= 1;
	if (i == 31)
	{
		*nbr = value;
		i = 0;
		value = 0;
		return ;
	}
	value <<= 1;
	++i;
}

/* Transforms the 8 bites into a char.
Returns TRUE if char is complete in order to move to the next. */
static int	get_str(int sig, char *str)
{
	static int				i;
	static unsigned char	c;

	if (sig == SIGUSR2)
		c |= 1;
	if (i == 7)
	{
		str[0] = (char)c;
		i = 0;
		c = 0;
		return (1);
	}
	c <<= 1;
	++i;
	return (0);
}

/* Get data for leng and pid_c. After done it returns the str alloced. */
static char	*get_data(int *leng, int *pid_c, int sig)
{
	char	*str;

	if (!*leng)
		get_nbr(sig, leng);
	else if (!*pid_c)
		get_nbr(sig, pid_c);
	if (*pid_c)
	{
		str = ft_calloc(sizeof(char *), *leng + 1);
		if (!str)
			exit (1);
		return (str);
	}
	return (0);
}

static void	signal_handler(int sig)
{
	static char	*str;
	static int	leng;
	static int	i;
	static int	pid_c;

	if (!leng || !pid_c)
		str = get_data(&leng, &pid_c, sig);
	else if (pid_c && i < leng)
	{
		if (get_str(sig, &str[i]))
			++i;
	}
	if (pid_c && leng && i == leng)
	{
		usleep(100);
		if (kill(pid_c, SIGUSR1) == -1)
			write(1, "Failed to send signal back.\n", 28);
		write(1, str, leng);
		write(1, "\n", 2);
		free(str);
		str = 0;
		pid_c = 0;
		leng = 0;
		i = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sas;

	sas.sa_handler = &signal_handler;
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 2);
	sigaction(SIGUSR1, &sas, NULL);
	sigaction(SIGUSR2, &sas, NULL);
	while (1)
		continue ;
	exit (0);
}
