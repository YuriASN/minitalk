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
		i = 0;
		*nbr = value;
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

static void	signal_handler(int sig)
{
	static char	*str;
	static int	leng;
	static int	i;
	static int	pid_c;

	if (!leng)
		get_nbr(sig, &leng);
	else if (leng && !pid_c)
		get_nbr(sig, &pid_c);
	else if (!str)
	{
		str = ft_calloc(sizeof(char *), leng + 1);
		if (!str)
			exit (1);
	}
	if (str && i < leng)
	{
		if (get_str(sig, &str[i]))
			++i;
	}
	if (pid_c && i == leng)
	{
		leng = 0;
		i = 0;
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
		free(str);
		str = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sas;

	sas.sa_handler = &signal_handler;
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sas, NULL);
	sigaction(SIGUSR2, &sas, NULL);
	while (1)
		usleep(100);
	exit (0);
}
