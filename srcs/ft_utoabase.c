#include "../includes/libftprintf.h"

static size_t	utoa_nbrlen(size_t n, int base)
{
	size_t	nlen;

	nlen = 1;
	while (n / base)
	{
		n /= base;
		nlen++;
	}
	return (nlen);
}

char		*check_base(int majbase, int base)
{
	char *str;

	if (majbase == 1 && base == 16)
	    str = "0123456789ABCDEF";
    else if (majbase == 0 && base == 16)
	    str = "0123456789abcdef";
	else if (majbase == 0 && base == 10)
		str = "0123456789";
	else
		str = NULL;
	return (str);
}

char		*utoa(size_t n, int base, int majbase)
{
	char    *ret;
	size_t  nlen;
	size_t  i;
	char    *strbase;

    strbase = check_base(majbase, base);
	if (strbase == NULL)
		return (NULL);
	nlen = utoa_nbrlen(n, base);
	ret = (char *)ft_calloc(nlen + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	if (n == 0)
		ret[0] = '0';
	i = nlen - 1;
	while (n)
	{
		ret[i] = strbase[n % base];
		n /= base;
		i--;
	}
	return (ret);
}
