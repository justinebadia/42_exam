#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_paint
{
	int		W;
	int		H;
	char	BG;
	char	**tab;
	float	x;
	float	y;
	float	Xbr;
	float	Ybr;
	float	width;
	float	height;
	char	c;
	char	form;

}				t_paint;


int	write_stdout(char *str, int ret);
t_paint	*init_struct(t_paint *paint);
int		print_exit(int ret, t_paint *paint, FILE *fp);

t_paint *init_struct(t_paint *paint)
{
	paint = calloc(1, sizeof(t_paint));
	paint->tab = NULL;
	paint->W = 0;
	paint->H = 0;
	paint->BG = '0';
	return (paint);
}

int is_in_rect(float Xa, float Ya, t_paint *paint)
{
	
	if ((Xa - paint->x < 1.00000000 || paint->Xbr - Xa < 1.00000000 || 
		(Ya - paint->y < 1.00000000 || paint->Ybr - Ya < 1.00000000)))
		return (1);
	return (0);
}

void	draw(t_paint *paint)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = 0;
	paint->Xbr = paint->x + paint->width;
	paint->Ybr = paint->y + paint->height;
	while (i < paint->H)
	{
		j = 0;
		while (j < paint->W)
		{
			ret = is_in_rect(j, i, paint);
			if ( i >= paint->y && i <= paint->Ybr && j >= paint->x && j <= paint->Xbr)
			{
				if ((paint->form == 'r' && ret == 1) || (paint->form == 'R'))
					paint->tab[i][j] = paint->c;
			}
			j++;
		}
		i++;
	}
}

int		print_exit(int ret, t_paint *paint, FILE *fp)
{
	int	i;

	i = 0;
	if (ret == 1)
		write(2, "Error: Operation file corrupted\n", 32);
	else
		while (i < paint->H)
		{
			write(1, paint->tab[i], paint->W);
			write(1, "\n", 1);
			i++;
		}
	if (fp)
		fclose(fp);
	i = 0;
	// if (paint->tab)
	// {
	// 	while (paint->tab[i])
	// 	{
	// 		free(paint->tab[i]);
	// 		i++;
	// 	}
	// 	free(paint->tab);
	//}
	// if (paint)
	// 	free(paint);
	return (ret);
}

int main(int argc, char **argv)
{
	FILE	*fp;
	t_paint	*paint;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	fp = NULL;
	paint = NULL;
	if (argc != 2)
		return (write_stdout("Error: argument", 1));
	if ((fp = fopen(argv[1], "r")))
	{
		paint = init_struct(paint);
		if ((ret = fscanf(fp, "%d %d %c", &paint->W, &paint->H, &paint->BG) == 3))
		{
			if ((paint->H > 0 && paint->H <= 300) && (paint->W > 0 && paint->W <= 300))
			{
				paint->tab = calloc(paint->H, sizeof(char*));
				while (i < paint->H)
				{
					paint->tab[i] = calloc(paint->W, sizeof(char));
					memset(paint->tab[i], paint->BG, paint->W);
					i++;
				}
				while (1)
				{
					ret = fscanf(fp, "\n%c %f %f %f %f %c", &paint->form, &paint->x, &paint->y, &paint->width, &paint->height, &paint->c);
					if (ret == EOF)
						return (print_exit(0, paint, fp));
					else if ((paint->form != 'R' && paint->form != 'r') || paint->width <= 0 || paint->height <= 0 || ret != 6)
						break ;
					draw(paint);
				}
			}
		}
	}	
	return (print_exit(1, paint, fp));

}

int	write_stdout(char *str, int ret)
{
	int	i;

	i = 0;
	while(str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	return (ret);
}