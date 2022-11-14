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

char	*get_splited_line(char **save, const int fd);
void	save_splited_line(char **save, int fd);
int		get_raw_line(char **save, int fd);

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*line;

	if (fd < 0 || 1024 < fd)
		return (NULL);
	get_raw_line(save, fd);
	line = get_splited_line(save, fd);
	if (save[fd] != NULL)
		save_splited_line(save, fd);
	return (line);
}

int	get_raw_line(char **save, int fd)
{
	int		loop_flag;
	char	*tmp;
	char	*line;
	int		read_count;

	loop_flag = 1;
	if (ft_strnchr(save[fd], '\n', ft_strlen(save[fd])))
		loop_flag = 0;
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (loop_flag)
	{
		ft_memset(tmp, '\0', BUFFER_SIZE + 1);
		read_count = read(fd, tmp, BUFFER_SIZE);
		if (0 >= read_count)
			break ;
		if (ft_strnchr(tmp, '\n', BUFFER_SIZE))
			loop_flag = 0;
		line = ft_strjoin(save[fd], tmp);
		free(save[fd]);
		save[fd] = line;
	}
	free(tmp);
	return (0);
}

char	*get_splited_line(char **save, const int fd)
{
	char	*line;
	size_t	len;

	len = 0;
	if (save[fd] == NULL)
		return (NULL);
	if (save[fd][0] == '\0')
		return (NULL);
	while (1)
	{
		if (save[fd][len] == '\n')
		{
			len++;
			break ;
		}
		if (save[fd][len] == '\0')
			break ;
		len++;
	}
	line = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(line, save[fd], len + 1);
	return (line);
}

void	save_splited_line(char **save, int fd)
{
	char	*line;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (1)
	{
		if (save[fd][i] == '\n')
		{
			i++;
			break ;
		}
		if (save[fd][i] == '\0')
		{
			free(save[fd]);
			save[fd] = NULL;
			return ;
		}
		i++;
	}
	while (save[fd][i + len] != '\0')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(line, &save[fd][i], len + 1);
	free(save[fd]);
	save[fd] = line;
}
