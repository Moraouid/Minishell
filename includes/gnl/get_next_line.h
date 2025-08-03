/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:29 by sel-abbo          #+#    #+#             */
/*   Updated: 2024/12/12 19:18:02 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_r(char *s1, char *s2);
char	*ft_strchr1(const char *s, int c);
size_t	ft_strlen1(const char *s);
char	*ft_substr1(char const *s, unsigned int start, size_t len);
char	*ft_strdup1(const char *src);

#endif
