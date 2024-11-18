/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:00:34 by jpedro-f          #+#    #+#             */
/*   Updated: 2024/11/15 17:00:35 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (clean_node->str[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

void	list_prep(t_list **list)
{
	int		i;
	int		x;
	t_list	*last_node;
	t_list	*clean_node;
	char	*buf;

	x = 0;
	i = 0;
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = find_last_node(*list);
	while (last_node->str[i] && last_node->str[i] != '\n')
		i++;
	while (last_node->str[i] && last_node->str[++i])
	{
		buf[x] = last_node->str[i];
		x++;
	}
	buf[x] = '\0';
	clean_node->str = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

void	list_add(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append_list(list, buf);
	}
}

char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_list(list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	t_list	*list;
	char	*next_line;

	list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	list_add(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	list_prep(&list);
	return (next_line);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("file.txt", O_RDWR | O_CREAT);
// 	if (fd < 0)
// 		printf("error open");
// 	printf("%s", get_next_line(fd));
// 	return (0);
// }