#include "libftprintf.h"

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * n);
	if (str == NULL)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
