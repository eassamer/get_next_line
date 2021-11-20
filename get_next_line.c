/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassamer <eassamer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:10:02 by eassamer          #+#    #+#             */
/*   Updated: 2021/11/20 18:12:51 by eassamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"get_next_line.h"

char	*ft_change_text(char *text)
{
	size_t	len;
	char *ntext;
	size_t i;

	i = 0;
	len = 0;
	while(text[len] != '\n' && text[len] != '\0')
		len++;
	if(text[len] == '\n')
		len++;
	ntext = (char *)malloc(sizeof(char) * (ft_strlen(text) - len + 1));
	if (!ntext)
	{
		free(ntext);
		return (NULL);
	}
	while (len < ft_strlen(text))
	{
		ntext[i] = text[len];
		i++;
		len++;
	}
	ntext[i] = '\0';
	free(text);
	return (ntext);
}
char	*ft_just_a_line(char *text)
{
	size_t	len;
	size_t	i;
	char	*buff;

	i = 0;
	len = 0;
	while (text[len] != '\n' && text[len] != '\0')
		len++;
	if(text[len] == '\n')
		len++;
	buff = (char *)malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	while(i < len)
	{
		buff[i] = text[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

char	*ft_read(char *text,int fd)
{
	char	*buff;
	int l;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	l = 1;
	while (!(ft_strchr(text, '\n')) && l != 0)
	{
		l = read(fd, buff, BUFFER_SIZE);
		if (l == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[l] = '\0';
		text = ft_strjoin(text,buff);
	}
	free(buff);
	return (text);
}

char	*get_next_line(int fd)
{
	static char *text;
	char *line;
	if (!text || !fd)
		return (NULL);
	text = ft_read(text,fd);
	if (text == NULL)
		return (NULL);
	line = ft_just_a_line(text);
	text = ft_change_text(text);
	return (line);
}