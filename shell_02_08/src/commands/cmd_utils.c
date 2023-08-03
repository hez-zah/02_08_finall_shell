#include "../../headers/minishell.h"

static int	charcheck(char tch, char *check)
{
	if (!(*check))
		return (0);
	if (tch == *check)
		return (1);
	return (charcheck(tch, check + 1));
}

static int	ft_not_an_int(int base, int addition, int plus)
{
	if (base < 214748364)
		return (0);
	if (plus == 1 && addition > 7)
		return (1);
	if (plus == -1 && addition > 8)
		return (1);
	if (base > 214748364)
		return (1);
	return (0);
}

static int	exit_atoi_construct(const char *ptr, int *error, int plus)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (charcheck(ptr[i], "0123456789"))
	{
		if (ft_not_an_int(result, ptr[i] - 48, plus))
			*error = -1;
		if (*error == -1)
			return (0);
		result = result * 10 + ptr[i] - 48;
		i++;
	}
	if (ptr[i])
	{
		*error = -1;
		return (0);
	}
	return (result);
}

int	exit_atoi(const char *nptr, int *error)
{
	int		i;
	int		plus;

	i = 0;
	plus = 1;
	while (charcheck(nptr[i], " \t\v\r\f\n"))
		i++;
	if (nptr[i] == '-')
	{
		plus = -1;
		i++;
	}
	return (plus * exit_atoi_construct(&(nptr[i]), error, plus));
}
