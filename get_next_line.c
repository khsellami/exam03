
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*ft_strchr(const char *string, int searchedChar)
{
	int	i;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] != '\0')
	{
		if (string[i] == searchedChar)
			return ((char *)(string + i));
		i++;
	}
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count += 1;
		str += 1;
	}
	return (count);
}

char	*ft_strdup(char *s1)
{
	char	*p;
	int		l;
	int		i;

	i = 0;
	l = ft_strlen(s1) + 1;
	p = (char *) malloc (l);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*k;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = (char *) malloc (i + j + 1);
	if (!k)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		k[j++] = s1[i++];
	i = 0;
	while (s2[i])
		k[j++] = s2[i++];
	k[j] = '\0';
	free(s1);
	s1 = NULL;
	return (k);
}
static char	*ft_read(int fd, char *str)
{
	int		byteread;
	char	*buffer;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byteread = 1;
	while (byteread)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread == 0)
			break ;
		if (byteread == -1)
			return (free(str), str = NULL, free(buffer), buffer = NULL, NULL);
		buffer[byteread] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_strchr(str, '\n') != NULL)
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (str);
}

static char	*getthisline(char *t)
{
	char	*line;
	int		n;
	int		i;

	n = 0;
	i = 0;
	if (!t)
		return (NULL);
	while (t[n] && t[n] != '\n')
		n++;
	if (t[n] == '\n')
		n++;
	line = malloc(n + 1);
	if (!line)
		return (NULL);
	while (i < n)
	{
		line[i] = t[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*rest(char *tmp)
{
	char	*newline_pos;
	char	*rst;

	newline_pos = ft_strchr(tmp, '\n');
	if (!newline_pos)
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	newline_pos++;
	rst = ft_strdup(newline_pos);
	if (!rst)
		return (NULL);
	free(tmp);
	tmp = NULL;
	return (rst);
}

char	*get_next_line(int fd)
{
	char		*ln;
	static char	*str;

	if (read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX
		|| fd < 0 || fd > INT_MAX)
	{
		if (str != NULL)
			return (free(str), str = NULL, NULL);
		return (NULL);
	}
	str = ft_read(fd, str);
	if (!str || !*str)
		return (free(str), str = NULL, NULL);
	ln = getthisline(str);
	if (!ln)
		return (free(str), str = NULL, NULL);
	str = rest(str);
	return (ln);
}
