#include <unistd.h> //write, read
#include <stdlib.h>	// malloc, free
#include <stdio.h>
#include <fcntl.h>	//open, O_RDONLY


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 6
#endif


size_t ft_strlen(char *s)
{
	int i = 0;
	while(s[i])
		i++;
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
		*dst++ = *src++;
		//dst++; src++;
	}
	*dst = '\0';
}

char *ft_strdup(char *src)
{
	//size_t len = ft_strlen(src);
	char *dst = malloc((ft_strlen(src) + 1)* sizeof(char) );
	return(ft_strcpy(dst, src), dst);
}

char *ft_strjoin(char *str1, char *str2)
{
	char *join = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	ft_strcpy(join, str1);
	ft_strcpy((join + ft_strlen(str1)), str2);
	free(str1);		// because of: current_line = ft_strjoin(current_line, buf);
	
	return(join);
}

char *get_next_line(int fd)
{
	static char	buf[2048][BUFFER_SIZE + 1];		//static! to read multiple fd, 2D array, 2048 is max fd in unix.
	
	char *current_line = ft_strdup(buf[fd]);		// copy reminder
	char *next_line;
	int count_read = 1; //= read(fd, buf, BUFFER_SIZE);
	int current_line_size = 0;

	while( !(ft_strchr(current_line,'\n')) && (count_read /*= read(fd, buf[fd], BUFFER_SIZE)*/) > 0)
	{
		count_read = read(fd, buf[fd], BUFFER_SIZE);
		buf[fd][count_read] = '\0';																//put end of string (because strjoin -> strcpy)
		current_line = ft_strjoin(current_line, buf[fd]);
	}
	if(ft_strlen(current_line) == 0)
		{//printf("___exit: \n");
		 return(free(current_line), NULL);
		}
	if((next_line = ft_strchr(current_line, '\n')))		// when nextline is not empty
	{
		//printf("next_line: %s\n", next_line);
	
		current_line_size = next_line - current_line + 1;

		//printf("current_line_size: %i\n", current_line_size);

		ft_strcpy(buf[fd], next_line + 1);														// next_line start at \n, so (next + 1) is ok.

		//printf("buf: %s\n", buf);
	}
	else 
	{
		ft_strcpy(buf[fd], "");	// if nextline is empty, then buf must be also
		current_line_size = ft_strlen(current_line);
	}
	current_line[current_line_size] = '\0';
	return(current_line);
}

int main()
{
	//write(1, "test std_input\n", ft_strlen("test std_input\n"));
	//char *line = get_next_line(STDIN_FILENO);
	//printf("_output:  %s", line);
	//free(line);

	char *line;

	int fd = open("test.txt", O_RDONLY);
	int fd1 = open("test3.txt", O_RDONLY);

	do {printf("_output1:  %s\n",line = get_next_line(fd));}
	while(line);  //i++ < 9

	free(line);
	fd = open("test.txt", O_RDONLY);

	int i = 14;
	while(i--)
	{
		printf("_output1:  %s\n",line = get_next_line(fd));
		free(line);
		printf("_output2:  %s\n",line = get_next_line(fd1));
		free(line);
	}
		return(1);

}
