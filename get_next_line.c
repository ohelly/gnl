/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:59:48 by ohelly            #+#    #+#             */
/*   Updated: 2019/01/17 19:26:31 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clr(char *buf, int i)
{
	int		j;
	char	*p;

	if (i < 0)
	{
		ft_strclr(buf);
		return (buf);
	}
	i = i + 1;
	j = ft_strlen(buf) - i;
	if (!(p = ft_strsub(buf, i, j)))
		return (0);
	ft_memdel((void**)&buf);
	return (p);
}

int		ft_workwline(char **line, char **arr, char *dis, int bytes)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (ft_strcmp(arr[j], dis) != 0)
		j++;
	i = ft_strlenc(arr[j + 1], '\n');
	if (!bytes && !ft_strlen(arr[j + 1]))
		return (-1);
	if (i >= 0)
	{
		*line = ft_strsub(arr[j + 1], 0, i);
		arr[j + 1] = ft_clr(arr[j + 1], i);
		return (0);
	}
	if (!ft_strrchr(arr[j + 1], '\n') && bytes == 0)
	{
		tmp = ft_strdup(arr[j + 1]);
		*line = tmp;
		arr[j + 1] = ft_clr(arr[j + 1], i);
		return (0);
	}
	return (1);
}

char	**ft_new_arr(char **p, char **arr, char *dis, char *buf)
{
	int i;

	i = 0;
	if (arr)
		while (arr[i] != 0)
		{
			if (!(p[i] = ft_strdup(arr[i])))
				return (0);
			ft_memdel((void**)&arr[i++]);
		}
	ft_memdel((void**)arr);
	if (!(p[i++] = ft_strdup(dis)))
		return (0);
	if (!(p[i++] = ft_strdup(buf)))
		return (0);
	p[i] = 0;
	return (p);
}

char	**ft_check_arr(char **arr, char *dis, char *buf)
{
	int		i;
	char	**p;
	char	*tmp;

	i = 0;
	p = 0;
	if (arr)
		while (arr[i] != 0 && arr)
			if (ft_strcmp(arr[i++], dis) == 0)
			{
				tmp = arr[i];
				if (!(arr[i] = ft_strjoin(tmp, buf)))
					return (0);
				ft_memdel((void**)&tmp);
				return (arr);
			}
	if (!(p = (char**)ft_memalloc(sizeof(char*) * (i + 3))))
		return (0);
	return (ft_new_arr(p, arr, dis, buf));
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static char		**arr = 0;
	char			*dis;
	int				bytes;
	int				i;

	if ((read(fd, buf, 0) < 0 || fd < 0 || line == NULL))
		return (-1);
	if (!(dis = ft_itoa(fd)))
		return (-1);
	i = 1;
	while (i == 1)
	{
		bytes = read(fd, buf, BUFF_SIZE);
		buf[bytes] = '\0';
		if (!(arr = ft_check_arr(arr, dis, buf)))
			return (-1);
		i = ft_workwline(line, arr, dis, bytes);
	}
	ft_memdel((void**)&dis);
	if (i == -1)
		return (0);
	return (1);
}
