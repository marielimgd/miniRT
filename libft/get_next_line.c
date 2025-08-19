/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:28:25 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/19 15:41:37 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

/* int	ft_search(char *str, char match)
{
	if (!str)
		return (0);
	int len = 0;
	while (str[len])
	{
		if (str[len] == match)
			return (1);
		len++;
	}
	return (0);
}

int	len_count(char *str)
{
	if (!str)
		return (0);

	int	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*join_and_free(char *saved, char *buffer)
{
	char *result = ft_strjoin(saved, buffer);
	if (!result)
	{
		free(saved);
		return (NULL);
	}
	free(saved);
	return (result);
}

char *read_from_input(int fd, char *saved)
{
    if (!saved)
    {
        saved = malloc(1);
        if (!saved)
            return(NULL);
        saved[0] = '\0';
    }
    char *buffer = malloc(BUFFER_SIZE+1);
    if (!buffer)
    {
        free(saved);
        return(NULL);
    } 
    int bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free (saved);
            free (buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        saved = join_and_free(saved, buffer);
        if (!saved)
        {
            free(buffer);
            return (NULL);
        }
        if (ft_search(buffer, '\n'))
            break;
    }
    free(buffer);
    return(saved);

}

char	*extract_line(char *buffer)
{

	if (!buffer || !buffer[0])
		return (NULL);
	int line_len = 0;
	while (buffer[line_len] && (buffer[line_len] != '\n'))
		line_len++;
	char *line = malloc(line_len + 1);
	if (!line)
		return (NULL);
	int char_count = 0;
	while (char_count <= line_len && buffer[char_count])
	{
		line[char_count] = buffer[char_count];
		char_count++;
	}
	line[char_count] = '\0';
	return (line); 
}

char	*save_remainder(char *buffer)
{
	if (!buffer)
		return (NULL);
	int line_len = 0;
	while (buffer[line_len] && (buffer[line_len] != '\n'))
		line_len++;
	if (buffer[line_len] == '\n')
		line_len++; 
	if (!buffer[line_len])
	{
		free(buffer);
		return (NULL);
	}
	char *remainder = malloc(len_count(buffer) - line_len + 2);
	if (!remainder)
	{
		free(buffer);
		return (NULL);
	}
	int char_count = 0;
	while (buffer[line_len])
	{
		remainder[char_count] = buffer[line_len];
		line_len++;
		char_count++;
	}
	remainder[char_count] = '\0'; 
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_from_input(fd, saved);
	if (!saved)
		return (NULL);

	line = extract_line(saved);
	if (!line)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}

	saved = save_remainder(saved);
	return (line);
}
 */

 
 static char *read_and_join(int fd, char *buffer)
{
    char    read_buf[BUFFER_SIZE + 1];
    char    *temp;
    int     bytes_read;

    bytes_read = 1;
    while (!ft_strchr(buffer, '\n') && bytes_read > 0)
    {
        bytes_read = read(fd, read_buf, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            return (NULL);
        }
        read_buf[bytes_read] = '\0';
        temp = ft_strjoin(buffer, read_buf);
        free(buffer);
        buffer = temp;
        if (!buffer)
            return (NULL);
    }
    return (buffer);
}

static char *extract_line(char *buffer)
{
    int     i;
    char    *line;

    i = 0;
    if (!buffer[i])
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    line = ft_substr(buffer, 0, i);
    return (line);
}

static char *get_remainder(char *buffer)
{
    int     i;
    char    *remainder;

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        return (NULL);
    }
    remainder = ft_strdup(&buffer[i + 1]);
    free(buffer);
    return (remainder);
}

char    *get_next_line(int fd)
{
    static char *buffer;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!buffer)
        buffer = ft_strdup("");
    buffer = read_and_join(fd, buffer);
    if (!buffer)
        return (NULL);
    line = extract_line(buffer);
    buffer = get_remainder(buffer);
    return (line);
}