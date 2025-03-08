/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:07:06 by rdomange          #+#    #+#             */
/*   Updated: 2024/09/10 14:59:13 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

void	ft_printf_debug(char *str, int *flg)
{
	printf("{");
	printf("[%d:|%c|]", 4, flg[4]);
	for (int i = 0; i < 128; i++)
	{
		if (i <= 6)
		{
			if (flg[i])
				printf("[%d:|%d|]", i, flg[i]);
		}
		if (ft_isprint(flg[i]))
			printf("[%d:'%c']", i, flg[i]);
	}
	printf("->|%s|}\n", str);
}

static int	*ft_printf_flag(va_list *a, const char **fmt, int *flg);
static char	*ft_printf_elem(va_list *a, const char **fmt, int *flg, char *e);
//static char	*ft_printf_trans(char *e, int *flg, int base);
static char	*ft_printf_trns(char *e, int *flg, size_t w, size_t p);
//static char	*ft_printf_extend(char *e, int *flg, size_t w, size_t p);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*str;
	int		len;
	int		flg[128];

	va_start(ap, fmt);
	len = 0;
	while (fmt && *fmt)
	{
		if (*fmt == '%' && *(fmt + 1) && *(++fmt) != '%')
		{
			str = ft_printf_elem(&ap, &fmt, flg, NULL);
			//ft_printf_debug(str, flg);
			if (!str)
				break ;
			len += flg[7] + 0 * write(1, str, flg[7]) + (long)ft_free(str);
		}
		else if (*fmt)
			len += 1 + 0 * write(1, fmt++, 1);
	}
	va_end(ap);
	return ((len * (*fmt == 0)) + (-1 * (*fmt != 0)));
}

//putstr is wrong because of %c=0, need write for len

//flg[0] ->
//flg["%-+ '#"]
//flg[1] -> "width"
//flg[2] -> ".precision"
//flg[3] -> precision bool
//flg[4] -> "%cspdiuxXobfFgG"
//flg["%cspdiuxXobfFgG"]
//flg[5] -> base
//flg[6] -> sign

static int	*ft_printf_flag(va_list *a, const char **fmt, int *flg)
{
	ft_bzero(flg + 1, (128 - 1) * sizeof(int));
	while (ft_strchr("-+ 0'#", **fmt))
		flg[(int)(*((*fmt)++))] = 1;
	while (ft_isdigit(**fmt))
		flg[1] = (flg[1] * 10) + (*((*fmt)++) - '0');
	if (!flg[1] && **fmt == '*' && *(++(*fmt)))
		flg[1] = va_arg(*a, int);
	if (**fmt == '.' && ++flg[3] && ft_isdigit(*(++(*fmt))) && ++flg[2])
		while (ft_isdigit(**fmt))
			flg[2] = (flg[2] * 10) + (*((*fmt)++) - '0');
	if (!flg[2] && flg[3] && **fmt == '*' && *(++(*fmt)))
		flg[2] = va_arg(*a, int) + 1;
	if (**fmt == 'l' && *(++(*fmt)))
		flg['l']++;
	flg[4] = *((*fmt)++);
	if (!ft_strchr("cspdiuxXobfFgGeE", flg[4]) || flg[1] < 0 || flg[2] < 0)
		return (NULL);
	flg[(int)flg[4]]++;
	flg[5] = (2 * (flg['b'] + 8 * flg['o'] + 10 * flg['u']));
	flg[5] += (16 * (ft_strchr("xXp", flg[4]) != NULL));
	flg[6] = flg['+'] * '+' + flg[' '] * ' ' * !flg['+'];
	if (ft_strchr("xXs", flg[4]) && flg[6])
		return (NULL);
	return (flg);
}

//what types are valid with # | ' ' | +

//(ulong)long cast, test properly
//check behaviour of itoa, ulong_min to ulong_max, long_min to long_max
//no cast here, flg['l']
//(unsigned int)long when negative X

static char	*ft_printf_elem(va_list *a, const char **fmt, int *flg, char *e)
{
	if (!ft_printf_flag(a, fmt, flg))
		return (NULL);
	if (flg['l'] && ft_strchr("uxXob", flg[4]))
		e = ft_itoa_ulong((unsigned int)va_arg(*a, long));
	if (flg['l'] && ft_strchr("di", flg[4]))
		e = ft_itoa(va_arg(*a, long));
	if ((!flg['l']) && ft_strchr("diuxXob", flg[4]))
		e = ft_itoa(va_arg(*a, int));
	if (ft_strchr("fFgGeE", flg[4]))
		e = ft_strdup(":)double to str, F|G|E:)");
	if (flg['p'])
		e = ft_itoa_ulong((unsigned long)va_arg(*a, void *));
	if (flg['s'])
		e = ft_strdup(va_arg(*a, char *));
	if (flg['c'])
		e = ft_strdup((char [2]){va_arg(*a, int), 0});
	if (!flg['s'] && *e == '-')
		flg[6] = '-' + 0 * (long)ft_memmove(e, e + 1, ft_strlen(e));
	if (flg[5])
		e = ft_atoa_base(e, 10, flg[5]) + (long)ft_free(e);
	if (flg['s'] && !e)
		e = ft_strdup("(null)");
	if (ft_isalpha_upper(flg[4]))
		ft_strtoupper(e);
	return (ft_printf_trns(e, flg, (size_t)flg[1], (size_t)flg[2]));
}

static char	*ft_printf_trns(char *e, int *flg, size_t w, size_t p)
{
	if (flg[3] && flg['s'] && p - 1 > 0 && ft_strlen(e) > p - 1)
		e[flg[2] - 1] = 0;
	while (flg[3] && !flg['s'] && p - 1 > 0 && ft_strlen(e) < p - 1)
		e = ft_strjoin("0", e) + (long)ft_free(e);
	if (flg['p'] || (flg['#'] && ft_strchr("xX", flg[4])))
		e = ft_strjoin("0x", e) + (long)ft_free(e);
	e = ft_strjoin((char [2]){flg[6], 0}, e) + (long)ft_free(e);
	while (w > ft_strlen(e) && !flg['-'] && !flg['c'])
		e = ft_strjoin(" ", e) + (long)ft_free(e);
	while (w > ft_strlen(e) && flg['-'] && !flg['c'])
		e = ft_strjoin(e, " ") + (long)ft_free(e);
	if (w > 1 && flg['c'])
	{
		p = (size_t)ft_memset(ft_calloc(w + 1, 1), ' ', w);
		((char *)p)[!flg['-'] * (w - 1)] = *e;
		free(e);
		e = (char *)p;
	}
	flg[7] = w + (!w * flg['c']) + (!w * ft_strlen(e) * !flg['c']);
	//printf("{flg[7]==%d}", flg[7]);
	return (e);
}
