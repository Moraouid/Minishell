/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:31 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/12/12 19:17:40 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_join(int fd, char *rem)
{
	char	*buffer;
	ssize_t	b_read;

	b_read = 1;
	if (BUFFER_SIZE < 0)
		return (NULL);
	while (b_read > 0 && !ft_strchr1(rem, '\n'))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (free(rem), NULL);
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
			return (free(rem), free(buffer), NULL);
		if (b_read == 0)
			return (free(buffer), rem);
		buffer[b_read] = '\0';
		rem = ft_strjoin_r(rem, buffer);
		free(buffer);
	}
	return (rem);
}

static char	*line_extra(char	**rem)
{
	char	*line;
	char	*new_line;
	char	*tmp;

	new_line = ft_strchr1(*rem, '\n');
	if (!new_line)
		return (NULL);
	line = ft_substr1(*rem, 0, new_line - *rem + 1);
	if (!line)
		return (NULL);
	tmp = ft_strdup1(new_line + 1);
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	free(*rem);
	*rem = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rem)
		rem = ft_strdup1("");
	rem = read_join(fd, rem);
	if (!rem)
		return (NULL);
	line = line_extra(&rem);
	if (line)
		return (line);
	if (ft_strlen1(rem) > 0)
	{
		line = ft_strdup1(rem);
		free(rem);
		rem = NULL;
		return (line);
	}
	return (free(rem), rem = NULL, NULL);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
//     int fd = open("test.txt", O_RDONLY); 
//      if (fd < 0)
//      {
//          printf("Error: Could not open file.\n");
//          return (1);
//      }

//     char *line;
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
// 		//line = NULL;
//     }

//     close(fd);
//     return (0);
// }
