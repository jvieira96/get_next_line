/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:03:15 by jpedro-f          #+#    #+#             */
/*   Updated: 2024/11/15 17:03:17 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;
char	*get_next_line(int fd);
void	append_list(t_list **list, char *buf);
int		found_newline(t_list *list);
int		len_list(t_list *list);
void	copy_str(t_list *list, char *new_str);
t_list	*find_last_node(t_list *list);
char	*get_line(t_list *list);
void	list_add(t_list **list, int fd);
void	list_prep(t_list **list);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
#endif
