#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 6
#endif

char * get_next_line(int fd)
{
	static char buf[2048][BUFFER_SIZE + 1];
	char *curr_ln = ft_strdup(buf);
	char *nxt_line;
	int c_read = 1;
	int curr_l_size = 0;

	while (!ft_strchr(curr_ln, '\n') && c_read > 0)
	{
		c_read = read(fd, buf, BUFFER_SIZE);
		buf[fd][c_read] = '\0';
		curr_ln = ft_strjoin(curr_ln, buf[fd]);
	}

	if(ft_strlen(curr_ln == 0))
		return(free(curr_ln), NULL);

	if (nxt_line = ft_strchr(curr_ln, '\n'))
	{
		curr_l_size = nxt_line - curr_ln + 1;
		ft_strcpy(buf[fd], nxt_line + 1);
	}	
	
	else 
	{
		ft_strcpy(buf[fd], "");
		curr_l_size = ft_strlen(curr_ln);
	}

	curr_ln[curr_l_size] = '\0';
	return(curr_ln);
}

size_t ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}

char *ft_strchr(char *s, char c)
{
	while(*s)
	{	if(*s == c)
			return(s);
		s++;
	}
	return(NULL);
}

void ft_strcpy(char *dst, char *src)
{
	while(*src)
		*dst++ = *src++;
	*dst = '\0';
}

char *ft_strdup(char *src)
{
	char *dst = malloc(ft_strlen(src) * sizeof(char));
	return(ft_strcpy(dst, src), dst);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *join = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1 * sizeof(char));
	ft_strcpy(join, s1);
	ft_strcpy(join + ft_strlen(s1), s2);
	free(s1);
	
	return(join);
}

