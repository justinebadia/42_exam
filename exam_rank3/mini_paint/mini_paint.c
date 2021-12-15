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
	float	xh;
	float	yv;
	float	radius;
	char	c;
	char	form;

}				t_paint;

int	write_stdout(char *str, int ret)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (ret);
}

int	print_exit(int ret, t_paint *paint, FILE *fp)
{
	int	i;

	i = 0;
	if (ret == 1)
		write(2, "Error: Operation file corrupted\n", 32);
	else
	{
		while (i < paint->H)
		{
			write(1, paint->tab[i], paint->W);
			write(1, "\n", 1);
			i++;
		}
	}
	if (fp)
		fclose(fp);
	return (ret);
}

void draw(t_paint *paint)
{
	int	i;
	int	j;
	float	sq;

	i = 0;
	while (i < paint->H)
	{
		j = 0;
		while (j < paint->W)
		{
			sq = sqrtf(powf(i - paint->yv, 2.0) + powf(j - paint->xh, 2.0));
			//(((i - paint->yv) * (i - paint->yv)) + ((j - paint->xh) * (j - paint->xh)));
			if (sq <= paint->radius)
			{
				if (paint->form == 'C' || ((paint->form == 'c' ) && paint->radius - sq < 1.00000000))
					paint->tab[i][j] = paint->c;
			}
			// square formule =  racin carrée
			// powf = puissance carré
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	FILE *fp;
	int	i;
	t_paint	*paint;
	int	ret;

	ret = 0;
	i = 0;
	fp = NULL;
	paint = calloc(1, sizeof(t_paint));
	if (argc != 2)
		return (write_stdout("Error: argument", 1));
	if ((fp = fopen(argv[1], "r")))
	{
		if ((ret = fscanf(fp, "%d %d %c", &paint->W, &paint->H, &paint->BG)) == 3)
		{
			if ((paint->H > 0 && paint->H <= 300) && (paint->W > 0 && paint->W <= 300))
			{
				paint->tab = calloc(paint->H, sizeof(char *));
				while (i < paint->H)
				{
					paint->tab[i] = calloc(paint->W, sizeof(char));	
					memset(paint->tab[i], paint->BG, paint->W);
					i++;
				}
				while (1)
				{
					ret = fscanf(fp, "\n%c %f %f %f %c", &paint->form, &paint->xh, &paint->yv, &paint->radius, &paint->c);
					if (ret == -1)
						return(print_exit(0, paint, fp));
					else if (ret != 5 || paint->radius <= 0 || (paint->form !='c' && paint->form!='C'))
						break ;
					draw(paint);
				}
			}
		}
	}
	return(print_exit(1, paint, fp));
	
}