#include<unistd.h>

/*Assignment name  : inter
Expected files   : inter.c
Allowed functions: write
--------------------------------------------------------------------------------
Write a program that takes two strings and displays, without doubles, the
characters that appear in both strings, in the order they appear in the first
one.

The display will be followed by a \n.

If the number of arguments is not 2, the program displays \n.
*/
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	my_strchr(char *str, char c, int k)
{
	int	i;

	i = 0;
	while (i <= k)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int main (int argc, char **argv)
{
	int	i;
	int j = 0;

	i = 0;
	if (argc != 3)
		ft_putchar('\n');
	else
	{
		while (argv[1][i] != 0)
		{
			if (ft_strchr(argv[2], argv[1][i]))
			{
				if(!(my_strchr(argv[1], argv[1][i], i - 1)))
					ft_putchar(argv[1][i]);
			}
			i++;
		}
		j++;
		ft_putchar('\n');
	}
	return (0);
}