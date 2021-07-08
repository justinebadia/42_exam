#include<unistd.h>

/*
Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------
Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n.
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	my_strchr(char *str, char c, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int main (int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
		ft_putchar('\n');
	else
	{
		while (argv[1][i] != '\0')
		{
			if (my_strchr(argv[1], argv[1][i], i))
				ft_putchar(argv[1][i]);
			i++;
		}
		i = 0;
		while (argv[2][i] != '\0')
		{
			if (my_strchr(argv[2], argv[2][i], i))
				{
					if (ft_strchr(argv[1], argv[2][i]))
						ft_putchar(argv[2][i]);
				}
			i++;
		}
		ft_putchar('\n');
	}
	return (0);
}