/* 
Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Vous devez rendre une fonction nommée `ft_printf` qui reproduira une petite partie du comportement du vrai printf avec les contraintes suivantes : 

- Vous devez gérer uniquement les conversions suivantes : s,d et x
- Vous devez gérer la taille de champ minimal. (Nous ne testerons jamais votre programme avec une taille de champ minimal de 0)
- Vous devez gérer uniquement le flag de précision `.`.

Votre fonction devra être prototypée de la façon suivante :

int ft_printf(const char *, ... ); 
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

#ifndef REAL
# define F	r += ft_printf
#else
# define F	r += printf
#endif

typedef struct s_flag
{
	int dot;
	int width;
	int star;
	int conversion;
	int no_flag;
}				t_flag;

char *ft_strdup(const char *str);
size_t ft_strlen(const char *str);
int ft_putchar(char c);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
char	*ft_itoa(long n);

t_flag init_flag(void);
int	ft_dot_flag(const char *str, int i, t_flag *flag, va_list arg);
t_flag ft_flag_width(va_list arg, t_flag flag);
int ft_parsing_flag(t_flag *flag, const char *str, int i, va_list args);
int	ft_treat_width(int width, int len, int zero);

int read_str(const char *str, va_list args, int char_counter);
int ft_conversion_type(int c, t_flag flag, va_list arg);
int ft_printf(const char *str_format, ...);

int	ft_print_s(char *str, t_flag flag);
int	ft_print_d(long nb, t_flag flag);
int ft_print_x(unsigned int u_nb, t_flag flag);
int	ft_treat_int_flag(char *str, int nbr, t_flag flag);
char *ft_put_str_hexa(unsigned long long nb);

int	ft_printf(const char *str_format, ...)
{
	va_list args;
	int	char_counter;
	const char *str;

	char_counter = 0;
	str = ft_strdup(str_format);
	va_start(args, str_format);
	char_counter += read_str(str, args, char_counter);
	va_end(args);
	free((char *)str);
	return(char_counter);
}

int read_str(const char *str, va_list args, int char_counter)
{
	int	i;
	t_flag flag;

	i = 0;
	char_counter = 0;
	while(str[i] && (size_t)i < ft_strlen(str))
	{
		flag = init_flag();
		if (str[i] == '%')
		{
			i = ft_parsing_flag(&flag, str, i+ 1, args);
			if(str[i] == 's' || str[i] == 'd' || str[i] == 'x')
				char_counter += ft_conversion_type((char)flag.conversion, flag, args);
			else
				char_counter += ft_putchar(str[i]);

		}
		else if (str[i] != '%')
			char_counter += ft_putchar(str[i]);
		i++;
	}
	return(char_counter);
}

int ft_conversion_type(int c, t_flag flag, va_list arg)
{
	int char_counter;

	char_counter = 0;
	if (c == 's')
		char_counter += ft_print_s(va_arg(arg, char *), flag);
	if (c == 'd')
		char_counter += ft_print_d(va_arg(arg, int), flag);
	if (c == 'x')
		char_counter += ft_print_x(va_arg(arg, unsigned int), flag);
	return(char_counter);
}

int ft_print_x(unsigned int u_nb, t_flag flag)
{
	int char_counter;
	char *str_hexa;

	char_counter = 0;
	u_nb = (unsigned int)(UINT32_MAX + 1 + u_nb);
	if (flag.dot == 0 && u_nb == 0)
	{
		char_counter += ft_treat_width(flag.width, 0, 0);
		return (char_counter);
	}
	str_hexa = ft_put_str_hexa((unsigned long long)u_nb);
	char_counter += ft_treat_int_flag(str_hexa, 0, flag);
	free(str_hexa);
	return(char_counter);
}


char	*ft_put_str_hexa(unsigned long long nb)
{
	char		*str_hexa;
	long long	nb_unsigned;
	int			len;

	len = 0;
	nb_unsigned = nb;
	if (nb == 0)
		return (ft_strdup("0"));
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	str_hexa = malloc(sizeof(char) * (len + 1));
	if (str_hexa == NULL)
		return (0);
	str_hexa[len] = '\0';
	while (nb_unsigned != 0)
	{
		if ((nb_unsigned % 16) < 10)
			str_hexa[len - 1] = (nb_unsigned % 16) + '0';
		else
			str_hexa[len - 1] = (nb_unsigned % 16) + ('a' - 10);
		nb_unsigned /= 16;
		len--;
	}
	return (str_hexa);
}

int	ft_print_d(long nb, t_flag flag)
{
	int char_counter;
	int nbr;
	char *str_nb;

	char_counter = 0;
	nbr = nb;
	if (flag.dot == 0 && nb == 0)
	{
		char_counter += ft_treat_width(flag.width, 0, 0);
		return(char_counter);
	}
	if (nb < 0 && flag.dot >= 0)
	{
		nb *= -1;
		flag.width--;
	}
	str_nb = ft_itoa(nb);
	char_counter += ft_treat_int_flag(str_nb, nbr, flag);
	free(str_nb);
	return(char_counter);

}

int	ft_treat_int_flag(char *str, int nbr, t_flag flag)
{
	int counter_char;
	int i;

	i = 0;
	counter_char = 0;
	if( flag.dot >= 0 && (size_t)flag.dot < ft_strlen(str))
		flag.dot = ft_strlen(str);
	if (flag.dot >= 0)
	{
		flag.width -= flag.dot;
		counter_char += ft_treat_width(flag.width, 0, 0);
	}
	else
		counter_char += ft_treat_width(flag.width, ft_strlen(str), 0);
	if (nbr < 0 && flag.dot > 0)
		counter_char += ft_putchar('-');
	if (flag.dot >= 0)
		counter_char += ft_treat_width(flag.dot, ft_strlen(str), 1);
	while (str[i])
	{
		counter_char += ft_putchar(str[i]);
		i++;
	}
	return(counter_char);
}

int	ft_print_s(char *str, t_flag flag)
{
	int char_counter;
	int i;

	i = 0;
	char_counter = 0;
	if (!str)
		str = "(null)";
	if (flag.dot >= 0 && (size_t)flag.dot > ft_strlen(str))
		flag.dot = ft_strlen(str);
	if (flag.dot >= 0)
		char_counter += ft_treat_width(flag.width, flag.dot, 0);
	else
		char_counter += ft_treat_width(flag.width, ft_strlen(str), 0);
	if (flag.no_flag == 0)
	{
		if (flag.dot >= 0)
		{
			char_counter += ft_treat_width(flag.dot, ft_strlen(str), 0);
			while(str[i] && i < flag.dot)
			{
				char_counter += ft_putchar(str[i]);
				i++;
			}
		}
		else
		{
			while(str[i])
			{
				char_counter += ft_putchar(str[i]);
				i++;
			}
		}
	}
	return(char_counter);
	
}

int	ft_treat_width(int width, int len, int zero)
{
	int char_counter;

	char_counter = 0;
	while( width - len > 0)
	{
		if (zero == 1)
			char_counter += ft_putchar('0');
		else
			char_counter += ft_putchar(' ');
		width--;
	}
	return (char_counter);
}

int	ft_atoi(const char *str)
{
	int i;
	int nb;
	int is_neg;

	i = 0;
	is_neg = 1;
	nb = 0;
	while(str[i] >= 9 && str[i]<= 13 || str[i] == ' ')
		i++;
	if(str[i] == '-'|| str[i] == '+')
	{
		if(str[i] == '-')
			is_neg *= -1;
		i++;
	}
	while(str[i] >= '0'&& str[i]<= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return(nb * is_neg);
}

char	*ft_itoa(long n)
{
	char	*str;
	long	nb;
	int		len;
	int		is_neg;

	nb = n;
	len = 0;
	is_neg = 0;
	if (nb == 0)
		len = 1;
	if (nb < 0)
		len++;
	while(nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	str = (char *)malloc(sizeof (char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	if (n < 0)
	{
		is_neg = 1;
		n *= -1;
	}
	while(--len != '\0')
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	if (is_neg == 1)
		str[0] = '-';
	else
		str[0] = (n % 10) + '0';
	return(str);
}

int ft_parsing_flag(t_flag *flag, const char *str, int i, va_list args)
{
	while (str[i])
	{
		if(str[i] == '.')
			i = ft_dot_flag(str, i + 1, flag, args);
		if(str[i] == '*')
			*flag = ft_flag_width(args, *flag);
		if(ft_isdigit(str[i]) && flag->width == 0)
			flag->width = ft_atoi(&str[i]);
		if( str[i] == 's'|| str[i] == 'd'|| str[i] == 'x')
		{
			flag->conversion = str[i];
			break ;
		}
		i++;
	}
	return (i);
}

t_flag ft_flag_width(va_list arg, t_flag flag)
{
	flag.star = 1;
	flag.width = va_arg(arg, int);
	if (flag.width < 0)
		flag.width *= -1;
	return(flag);

}
int	ft_dot_flag(const char *str, int i, t_flag *flag, va_list arg)
{
	if(str[i] == '*')
	{
		flag->dot = va_arg(arg, int);
		i++;
	}
	else
	{
		flag->dot = 0;
		if (ft_isdigit(str[i]))
		{
			flag->dot = ft_atoi(&str[i]);
			while(ft_isdigit(str[i]))
				i++;
		}
		if (flag->dot < 0)
			flag->dot = -1;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	return(c >= '0'&& c<= '9');
}

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

t_flag init_flag(void)
{
	t_flag flag;

	flag.dot = -1 ;
	flag.width = 0;
	flag.conversion = 0;
	flag.star = 0;
	flag.no_flag = 0;
	return(flag);
}

size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *ft_strdup(const char *str)
{
	int i;
	char *copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (copy == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int main (void)
{
	char *str = "salut";
	printf("\n\nTEST %%s\n\n");
	printf("\n___TEST %%s___\n");
	printf("No original - %d\n", ft_printf("|%s|\n", str));
	printf("Original - %d\n", printf("|%s|\n", str));

	printf("\n___TEST %%ss___\n");
	printf("No original - %d\n", ft_printf("|%ss|\n", str));
	printf("Original - %d\n", printf("|%ss|\n", str));

	printf("\n___TEST %%20s___\n");
	printf("No original - %d\n", ft_printf("|%20s|\n", str));
	printf("Original - %d\n", printf("|%20s|\n", str));

	printf("\n___TEST %%2s___\n");
	printf("No original - %d\n", ft_printf("|%2s|\n", str));
	printf("Original - %d\n", printf("|%2s|\n", str));

	printf("\n___TEST %%.2s___\n");
	printf("No original - %d\n", ft_printf("|%.2s|\n", str));
	printf("Original - %d\n", printf("|%.2s|\n", str));

	printf("\n___TEST %%.20s___\n");
	printf("No original - %d\n", ft_printf("|%.20s|\n", str));
	printf("Original - %d\n", printf("|%.20s|\n", str));

	printf("\n___TEST %%2.20s___\n");
	printf("No original - %d\n", ft_printf("|%2.20s|\n", str));
	printf("Original - %d\n", printf("|%2.20s|\n", str));

	printf("\n___TEST %%22.20s___\n");
	printf("No original - %d\n", ft_printf("|%22.20s|\n", str));
	printf("Original - %d\n", printf("|%22.20s|\n", str));

	printf("\n___TEST %%12.20s___\n");
	printf("No original - %d\n", ft_printf("|%12.20s|\n", str));
	printf("Original - %d\n", printf("|%12.20s|\n", str));

	printf("\n___TEST %%12.s___\n");
	printf("No original - %d\n", ft_printf("|%12.s|\n", str));
	printf("Original - %d\n", printf("|%12.s|\n", str));

	printf("\n___TEST %%.s___\n");
	printf("No original - %d\n", ft_printf("|%.s|\n", str));
	printf("Original - %d\n", printf("|%.s|\n", str));

	printf("\n___TEST %%20.s___\n");
	printf("No original - %d\n", ft_printf("|%20.s|\n", str));
	printf("Original - %d\n", printf("|%20.s|\n", str));

	printf("\n___TEST %%2.s___\n");
	printf("No original - %d\n", ft_printf("|%2.s|\n", str));
	printf("Original - %d\n", printf("|%2.s|\n", str));

	printf("\n\nTEST %%d\n\n");
	int num = 985467893;
	printf("\n___TEST %%d___\n");
	printf("No original - %d\n", ft_printf("|%d|\n", num));
	printf("Original - %d\n", printf("|%d|\n", num));

	printf("\n___TEST %%dd___\n");
	printf("No original - %d\n", ft_printf("|%dd|\n", num));
	printf("Original - %d\n", printf("|%dd|\n", num));

	printf("\n___TEST %%20d___\n");
	printf("No original - %d\n", ft_printf("|%20d|\n", num));
	printf("Original - %d\n", printf("|%20d|\n", num));

	printf("\n___TEST %%2d___\n");
	printf("No original - %d\n", ft_printf("|%2d|\n", num));
	printf("Original - %d\n", printf("|%2d|\n", num));

	printf("\n___TEST %%.2d___\n");
	printf("No original - %d\n", ft_printf("|%.2d|\n", num));
	printf("Original - %d\n", printf("|%.2d|\n", num));

	printf("\n___TEST %%.20d___\n");
	printf("No original - %d\n", ft_printf("|%.20d|\n", num));
	printf("Original - %d\n", printf("|%.20d|\n", num));

	printf("\n___TEST %%2.20s___\n");
	printf("No original - %d\n", ft_printf("|%2.20d|\n", num));
	printf("Original - %d\n", printf("|%2.20d|\n", num));

	printf("\n___TEST %%22.20d___\n");
	printf("No original - %d\n", ft_printf("|%22.20d|\n", num));
	printf("Original - %d\n", printf("|%22.20d|\n", num));

	printf("\n___TEST %%12.20d___\n");
	printf("No original - %d\n", ft_printf("|%12.20d|\n", num));
	printf("Original - %d\n", printf("|%12.20d|\n", num));

	printf("\n___TEST %%12.d___\n");
	printf("No original - %d\n", ft_printf("|%12.d|\n", num));
	printf("Original - %d\n", printf("|%12.d|\n", num));

	printf("\n___TEST %%.d___\n");
	printf("No original - %d\n", ft_printf("|%.d|\n", num));
	printf("Original - %d\n", printf("|%.d|\n", num));

	printf("\n___TEST %%20.d___\n");
	printf("No original - %d\n", ft_printf("|%20.d|\n", num));
	printf("Original - %d\n", printf("|%20.d|\n", num));

	printf("\n___TEST %%2.d___\n");
	printf("No original - %d\n", ft_printf("|%2.d|\n", num));
	printf("Original - %d\n", printf("|%2.d|\n", num));

	printf("\n\nTEST %%x\n\n");
	unsigned int un = INT32_MIN;
	printf("\n___TEST %%x___\n");
	printf("No original - %d\n", ft_printf("|%x|\n", un));
	printf("Original - %d\n", printf("|%x|\n", un));

	printf("\n___TEST %%xx___\n");
	printf("No original - %d\n", ft_printf("|%xx|\n", un));
	printf("Original - %d\n", printf("|%xx|\n", un));

	printf("\n___TEST %%20x___\n");
	printf("No original - %d\n", ft_printf("|%20x|\n", un));
	printf("Original - %d\n", printf("|%20x|\n", un));

	printf("\n___TEST %%2x___\n");
	printf("No original - %d\n", ft_printf("|%2x|\n", un));
	printf("Original - %d\n", printf("|%2x|\n", un));

	printf("\n___TEST %%.2x___\n");
	printf("No original - %d\n", ft_printf("|%.2x|\n", un));
	printf("Original - %d\n", printf("|%.2x|\n", un));

	printf("\n___TEST %%.20x___\n");
	printf("No original - %d\n", ft_printf("|%.20x|\n", un));
	printf("Original - %d\n", printf("|%.20x|\n", un));

	printf("\n___TEST %%2.20x___\n");
	printf("No original - %d\n", ft_printf("|%2.20x|\n", un));
	printf("Original - %d\n", printf("|%2.20x|\n", un));

	printf("\n___TEST %%22.20x___\n");
	printf("No original - %d\n", ft_printf("|%22.20x|\n", un));
	printf("Original - %d\n", printf("|%22.20x|\n", un));

	printf("\n___TEST %%12.20x___\n");
	printf("No original - %d\n", ft_printf("|%12.20x|\n", un));
	printf("Original - %d\n", printf("|%12.20x|\n", un));

	printf("\n___TEST %%12.x___\n");
	printf("No original - %d\n", ft_printf("|%12.x|\n", un));
	printf("Original - %d\n", printf("|%12.x|\n", un));

	printf("\n___TEST %%.x___\n");
	printf("No original - %d\n", ft_printf("|%.x|\n", un));
	printf("Original - %d\n", printf("|%.x|\n", un));

	printf("\n___TEST %%20.x___\n");
	printf("No original - %d\n", ft_printf("|%20.x|\n", un));
	printf("Original - %d\n", printf("|%20.x|\n", un));

	printf("\n___TEST %%2.x___\n");
	printf("No original - %d\n", ft_printf("|%2.x|\n", un));
	printf("Original - %d\n", printf("|%2.x|\n", un));

	printf("\n___TEST %%2.x___\n");
	printf("No original - %d\n", ft_printf("|%2.x|\n", un));
	printf("Original - %d\n", printf("|%2.x|\n", un));

	return (0);

}