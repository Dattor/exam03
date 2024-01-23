#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>	//open(), define O_RDONLY


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 6
#endif


size_t ft_strlen(char *s)
{
	int i = 0;
	while(s[i])
		i++;

	//printf("strlen> %d\n", i);
	
	return(i);
}

char *ft_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			{return (s);}
		s++;
	}
	return (NULL);
}



void ft_strcpy(char *dst, char *src)
{

	while (*src)
	{
		*dst = *src;
		dst++; src++;
	}
	*dst = '\0';
}

char *ft_strdup(char *src)
{
	size_t len = ft_strlen(src);
	char *dst = malloc(len * sizeof(char));
	return(ft_strcpy(dst, src), dst);
}

char *ft_strjoin(char *str1, char *str2)
{
	char *join = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	ft_strcpy(join, str1);
	ft_strcpy((join + ft_strlen(str1)), str2);
	free(str1);		// because of: current_line = ft_strjoin(current_line, buf);

		printf("join> %s\n", join);
	
	return(join);
}

char * get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];

	char *current_line = ft_strdup(buf);		// copy reminder
	char *next_line;
	int count_read; //= read(fd, buf, BUFFER_SIZE);
	int current_line_size;

	while( !(ft_strchr(current_line,'\n')) && (count_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[count_read] = '\0';
		current_line = ft_strjoin(current_line, buf);
		//count_read = read(fd, buf, BUFFER_SIZE);
		//write(1, "l\n", 2);
	}
	if(ft_strlen(current_line) == 0)
		{printf("___exit: \n"); return(free(current_line), NULL);}
	if((next_line = ft_strchr(current_line, '\n')))		// when nextline is not empty
	{
		printf("next_line: %s\n", next_line);
	
		current_line_size = next_line - current_line + 1;

		printf("current_line_size: %i\n", current_line_size);

		ft_strcpy(buf, next_line + 1);

		printf("buf: %s\n", buf);
	}
	else 
		ft_strcpy(buf, "");	// if nextline is empty, then buf must be also
	current_line[current_line_size] = '\0';
	return(current_line);
}

int main()
{
	write(1, "test std_input\n", ft_strlen("test std_input\n"));
	char *line = get_next_line(STDIN_FILENO);
	printf("_output:  %s", line);
	free(line);

	int fd = open("test.txt", O_RDONLY);
	int i = 0;
	while(i++ < 9)
		printf("_output:  %s\n",line = get_next_line(fd));
}