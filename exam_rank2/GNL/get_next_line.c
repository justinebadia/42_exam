/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 11:58:09 by jbadia            #+#    #+#             */
/*   Updated: 2021/08/31 11:58:28 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char	*ft_strnew(int size)
{
	char	*str;

	str = (char *)malloc(sizeof (char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	return (str);
}

size_t ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strjoin_gnl(char const *s1, const char *s2)
{
	char	*str;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i+j] = '\0';
	free((void *)s1);
	return (str);
}

int	get_next_line(char **line)
{
	char 	*buff;
	int		ret;

	ret = 0;
	buff = (char *)malloc(sizeof(char) * 2);
	if (buff == NULL || !line || read(0, buff, 0) < 0)
		return (-1);
	*line = ft_strnew(0);
	while ((ret = read(0, buff, 1)))
	{
		if (buff [0] == '\n')
		{
			free(buff);
			return (1);
		}
		buff[ret] = '\0';
		*line = ft_strjoin_gnl(*line, buff);
	}
	free(buff);
	return (0);
}

