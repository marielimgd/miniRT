/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:28:25 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/02 15:48:08 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

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