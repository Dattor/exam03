#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char *ft_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *) *s);
		s++;
	}
	return (NULL);
}

size_t ft_strlen(char *s)
{
	int i = 0;
	while(s[i++]);
	return(i);
}

size_t ft_strlcpy(char *dst, char *src)
{
	size_t srcsize = ft_strlen(src);

	while (*src)
	{
		*dst = *src;
		dst++; src++;
	}
	*dst = '\0';
	return (srcsize);
}

char *ft_strdup(char *src)
{
	size_t len = ft_strlen(src);
	char *dst = malloc(len * sizeof(char));
	return(ft_strlcpy(dst, src), len);
}

char *ft_strjoin(char *str1, char *str2)
{
	char *join = malloc(ft_strlen(str1) + ft_strlen(str2) + 1 * sizeof(char));
	join = ft_strlcpy(join, str1);
	join = ft_strlcpy((join + ft_strlen(str1)), str2);
	free(str1);		// because of: line = ft_strjoin(line, buf);
	return(join);
}

char * get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];

	char *line = ft_strdup(buf);		// copy reminder
	char *newline;
	int countread = read(fd, buf, BUFFER_SIZE);
	int to_copy;

	while( !(ft_strchr(line,'\n') ) && (countread > 0) )
	{
		buf[countread] = '\0';
		line = ft_strjoin(line, buf);


	}


}