#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

#define HEXA	"0123456789abcdef"

void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	if (count)
		(*count)++;
}

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		ft_putchar(str[i++], count);
}

void	ft_putnbr(int nb, int *count)
{
	if (nb == -2147483648)
		return (ft_putstr("-2147483648", count), (void)0);
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-', count);
	}
	if (nb < 10)
		ft_putchar(nb + '0', count);
	else
	{
		ft_putnbr(nb / 10, count);
		ft_putnbr(nb % 10, count);
	}
}

void	ft_putnbr_hex(long nbr, int *count)
{
	if (nbr >= 16)
	{
		ft_putnbr_hex(nbr / 16, count);
		ft_putnbr_hex(nbr % 16, count);
	}
	else
		ft_putchar(HEXA[nbr], count);
}

void	ft_display_int(va_list lst_param, int *count)
{
	int	nb;

	nb = va_arg(lst_param, int);
	ft_putnbr(nb, count);
}

void	ft_display_str(va_list lst_param, int *count)
{
	char	*str;

	str = va_arg(lst_param, char *);
	if (!str)
		str = "(null)";
	ft_putstr(str, count);
}

void	ft_display_hex(va_list lst_param, int *count)
{
	long	nbr;

	nbr = va_arg(lst_param, long);
	ft_putnbr_hex(nbr, count);
}

int	ft_printf(const char *line, ...)
{
	va_list	lst_param;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(lst_param, line);
	while (line[i])
	{
		if (line[i] == '%')
		{
			i++;
			if (line[i] == 's')
				ft_display_str(lst_param, &count);
			else if (line[i] == 'x')
				ft_display_hex(lst_param, &count);
			else if (line[i] == 'd')
				ft_display_int(lst_param, &count);
			else if (line[i] == '%')
				ft_putchar('%', &count);
			else
				return (va_end(lst_param), ft_putstr("error\n", NULL), -1);
		}
		else
			ft_putchar(line[i], &count);
		i++;
	}
	return (va_end(lst_param), count);
}

int	main(void)
{
	char	*str;
	char	*nul;
	int		ret1;
	int		ret2;

	str = "Hello%s%World \t ";
	(void)str;
	nul = NULL;
	(void)nul;
	ret1 = ft_printf(" %s\\ar%d\n", str, INT_MIN);
	ret2 = printf(" %s\\ar%d\n", str, INT_MIN);
	printf("my_return: %d\noffReturn: %d\n", ret1, ret2);
}
