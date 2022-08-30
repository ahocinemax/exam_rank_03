#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void	ft_putchar(char c, int , *count)
{
	write(1, &c, 1);
	(*count)++;
}

void    ft_putstr(char *str, int *count)
{
	if (!str)
		return ;
	while (str)
		ft_putchar((*str)++, &count);
}

void	ft_display_int(va_list lst_param, &count)
{
	int nb = va_arg(lst_param, int);
	if (nb <)
		str = "(null)";
    ft_putstr(str, count);
}

void	ft_display_str(va_list lst_param, &count)
{
	char *str = va_arg(lst_param, char *);
	if (!str)
		str = "(null)";
    ft_putstr(str, count);
}

int ft_printf(char *line, ...)
{
	int i = 0;
	int count = 0;
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
				return (va_end(lst_param), ft_putstr("parsing error\n"), count);
			i++;
		}
		else
			ft_putchar(line[i], &count);
		i++;
	}
	va_end(lst_param);
	return count;
}

int main(void)
{
	va_list lst_param;

	char *str = "Bonjour";
	ft_putstr("----------------- MY FUNCTION -----------------\n");
	int ret1 = ft_printf("%s\n", str);
	ft_putstr("\n----------------- PRINTF RTRN -----------------\n");
	int ret2 = printf("%s\n", str);
	ft_putstr("\n----------------- RETURNS VAL -----------------\n");
	printf("my_return: %d\noffReturn: %d\n", ret1, ret2);
}