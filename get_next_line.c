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

#include "get_next_line.h"

static char	*get_raw_line(char *save, int fd);
static char	*get_splited_line(char *save, int *error_flag, size_t *len);
static char	*save_splited_line(char *save, int *error_flag, size_t i);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	int			error_flag;
	size_t		i;

	if (fd < 0)
		return (NULL);
	error_flag = 0;
	save = get_raw_line(save, fd);
	line = get_splited_line(save, &error_flag, &i);
	if (line == NULL || error_flag)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = save_splited_line(save, &error_flag, i);
	if (error_flag)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*get_raw_line(char *save, int fd)
{
	int		loop_flag;
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	int		read_count;

	loop_flag = 1;
	if (ft_strnchr(save, '\n', ft_strlen(save)))
		loop_flag = 0;
	while (loop_flag)
	{
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (0 >= read_count)
			break ;
		if (ft_strnchr(buffer, '\n', BUFFER_SIZE))
			loop_flag = 0;
		tmp = ft_strjoin(save, buffer);
		free(save);
		save = tmp;
	}
	return (save);
}

static char	*get_splited_line(char *save, int *error_flag, size_t *len)
{
	char	*line;

	(void) error_flag;
	*len = 0;
	if (save == NULL || save[0] == '\0')
		return (NULL);
	while (save[*len] != '\n')
	{
		if (save[*len] == '\0')
			break ;
		(*len)++;
	}
	(*len)++;
	line = (char *)malloc(sizeof(char) * (*len + 1));
	if (line == NULL)
	{
		*error_flag = 1;
		return (NULL);
	}
	ft_strlcpy(line, save, *len + 1);
	return (line);
}

static char	*save_splited_line(char *save, int *error_flag, size_t i)
{
	char	*line;
	size_t	len;

	(void) error_flag;
	len = 0;
	if (save[i - 1] == '\0')
	{
		free(save);
		return (NULL);
	}
	while (save[i + len] != '\0')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (line == NULL)
	{
		*error_flag = 1;
		return (NULL);
	}
	ft_strlcpy(line, &save[i], len + 1);
	free(save);
	return (line);
}
