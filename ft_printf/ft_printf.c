#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int		ft_strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	if (count)
		(*count)++;
}

void    ft_putstr(char *str, int *count)
{
	int	i = 0;
	if (!str)
		return ;
	while (str[i])
		ft_putchar(str[i++], count);
}

void	ft_putnbr(int nb, int *count)
{
	if (nb == -2147483648)
		ft_putstr("-2147483648", count);
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

void	ft_display_int(va_list lst_param, int *count)
{
	int nb = va_arg(lst_param, int);
    ft_putnbr(nb, count);
}

void	ft_display_str(va_list lst_param, int *count)
{
	char *str = va_arg(lst_param, char *);
	if (!str)
		str = "(null)";
	ft_putstr(str, count);
}

void	ft_display_hex(va_list lst_param, int *count)
{
	(void)lst_param;
	(void)count;
}

int ft_printf(char *line, ...)
{
	int i = 0;
	int count = 0;
	va_list	lst_param;

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
				return (va_end(lst_param), ft_putstr("parsing error\n", NULL), -1);
		}
		else
			ft_putchar(line[i], &count);
		i++;
	}
	return (va_end(lst_param), count);
}

int main(void)
{
	char *str = "HelloWorld";
	ft_printf("%s\n", str);
	// int ret2 = printf("%s\n", str);
	// printf("my_return: %d\noffReturn: %d\n", ret1, ret2);
}