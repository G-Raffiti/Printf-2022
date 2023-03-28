#include "../includes/libftprintf.h"

char	*ft_strndup(const char *s, int n)
{
	size_t	i;
	size_t	l;
	char	*str;

	i = 0;
	l = ft_strlen(s) + 1;
	str = malloc(sizeof(char) * l);
	if (str = NULL)
		return (NULL);
	while (i < l - 1)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
