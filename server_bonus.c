#include "minitalk.h"

/* Transforms the first 32 bits on a int that contains the string size.
When done, it restore index and value after atrributing it to nbr. */
static void	get_nbr(int sig, int *nbr)
{
	static int	i;
	static int	value;
	//write(2, "*nbr = ", 7);	ft_putnbr_fd(*nbr, 2);	write(2, "\n", 1);
	if (sig == SIGUSR2)		{//	write(2, "1", 1);
		value |= 1;}
//	else
//			write(2, "0", 1);
	if (i == 31)
	{
//		write(2, "\n", 1);
//		write(2, "*b4 nbr = ", 9);	ft_putnbr_fd(*nbr, 2);	write(2, "\n", 1);
		*nbr = value;
		i = 0;
		value = 0;
//		write(2, "*nbr = ", 6);	ft_putnbr_fd(*nbr, 2);	write(2, "\n", 1);
//		write(2, "value = ", 8);	ft_putnbr_fd(value, 2);	write(2, "\n", 1);
//		write(2, "i = ", 4);	ft_putnbr_fd(i, 2);	write(2, "\n\n", 2);
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

	if (sig == SIGUSR2)		{//write(2, "1", 1);
		c |= 1;}
//	else
//		write(2, "0", 1);
	if (i == 7)
	{
//		write(2, "\n", 1);
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
	else if (!pid_c)
		get_nbr(sig, &pid_c);
	if (pid_c && !str)
	{
//		write(2, "Malloc using leng = ", 20);	ft_putnbr_fd(leng, 2);	write(2, "\n", 1);
		str = ft_calloc(sizeof(char *), leng + 1);
		if (!str)
			exit (1);
	}
	else if (pid_c && i < leng)
	{
		if (get_str(sig, &str[i]))
			++i;
	}
	if (pid_c && leng && i == leng)
	{
		usleep(100);
		if (kill(pid_c, SIGUSR1) == -1)
			write(1, "Failed to send signal back.", 27);
//		write(2, "pid_c = ", 8);	ft_putnbr_fd(pid_c, 2);	write(2, "\n", 1);
//		write(2, "Malloc = ", 9);	ft_putnbr_fd(leng, 2);	write(2, "\n", 1);
		ft_putstr_fd(str, 1);
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
