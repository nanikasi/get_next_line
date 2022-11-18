/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanakani <nanakani@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:04:03 by nanakani          #+#    #+#             */
/*   Updated: 2022/11/14 16:28:44 by nanakani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	get_raw_line(char **save, int fd);
static char	*get_splited_line(char **save, int fd, int *e_flag, size_t *len);
static void	save_splited_line(char **save, int fd, int *e_flag, size_t i);

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*line;
	int			e_flag;
	size_t		i;

	if (fd < 0 || 1024 < fd)
		return (NULL);
	e_flag = 0;
	get_raw_line(save, fd);
	line = get_splited_line(save, fd, &e_flag, &i);
	if (line == NULL || e_flag)
	{
		free(save[fd]);
		return (NULL);
	}
	if (save[fd] == NULL)
		return (line);
	save_splited_line(save, fd, &e_flag, i);
	if (e_flag)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	get_raw_line(char **save, int fd)
{
	int		loop_flag;
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	int		read_count;

	loop_flag = 1;
	if (ft_strnchr(save[fd], '\n', ft_strlen(save[fd])))
		loop_flag = 0;
	while (loop_flag)
	{
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (0 >= read_count)
			break ;
		if (ft_strnchr(buffer, '\n', BUFFER_SIZE))
			loop_flag = 0;
		tmp = ft_strjoin(save[fd], buffer);
		free(save[fd]);
		save[fd] = tmp;
	}
	return (0);
}

static char	*get_splited_line(char **save, int fd, int *e_flag, size_t *len)
{
	char	*line;

	(void) e_flag;
	*len = 0;
	if (save[fd] == NULL || save[fd][0] == '\0')
		return (NULL);
	while (save[fd][*len] != '\n')
	{
		if (save[fd][*len] == '\0')
			break ;
		(*len)++;
	}
	(*len)++;
	line = (char *)malloc(sizeof(char) * (*len + 1));
	if (line == NULL)
	{
		*e_flag = 1;
		return (NULL);
	}
	ft_strlcpy(line, save[fd], *len + 1);
	return (line);
}

static void	save_splited_line(char **save, int fd, int *e_flag, size_t i)
{
	char	*line;
	size_t	len;

	(void) e_flag;
	len = 0;
	if (save[fd][i - 1] == '\0')
	{
		free(save[fd]);
		save[fd] = NULL;
		return ;
	}
	while (save[fd][i + len] != '\0')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (line == NULL)
	{
		*e_flag = 1;
		return ;
	}
	ft_strlcpy(line, &save[fd][i], len + 1);
	free(save[fd]);
	save[fd] = line;
}
