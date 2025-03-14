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

void	ft_printf_debug(char *elem, int *flg)
{
	printf("{[type:%c]", flg[1]);
	if (flg[10])
		printf("[base:%d]", flg[10]);
	if (flg[2])
		printf("[width:%d]", flg[2]);
	if (flg[4])
		printf("[precision:%d]", flg[3]);
	if (flg[5] && flg[6])
		printf("[sign:%c%c]", flg[5], flg[6]);
	if (flg[5] && !flg[6])
		printf("[sign:%c]", flg[5]);
	if (flg[7])
		printf("[zeropad:%d]", flg[7]);
	printf("[res.len:%d]", flg[8]);
	for (int i = 12; i < 128; i++)
		if (flg[i])
			printf("(%c)", i);
	printf("->|%s|}\n", elem);
}

static int	*ft_printf_flag(va_list *a, const char **fmt, int *flg);
static char	*ft_printf_elem(va_list *a, const char **fmt, int *flg, char *e);
static char	*ft_printf_trns(char *e, int *flg);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*elem;
	int		len;
	int		flg[128];

	va_start(ap, fmt);
	len = 0;
	while (fmt && *fmt)
	{
		if (*fmt == '%' && *(fmt + 1) && *(++fmt) != '%')
		{
			elem = ft_printf_elem(&ap, &fmt, flg, NULL);
			//ft_printf_debug(elem, flg);
			if (!elem)
				break ;
			len += flg[8] + 0 * write(1, elem, flg[8]) + (long)ft_free(elem);
		}
		else if (*fmt)
			len += 1 + 0 * write(1, fmt++, 1);
	}
	va_end(ap);
	return ((len * (*fmt == 0)) + (-1 * (*fmt != 0)));
}

static int	*ft_printf_flag(va_list *a, const char **fmt, int *flg)
{
	ft_bzero(flg + 1, (128 - 1) * sizeof(int));
	while (ft_strchr("-+ 0'#", **fmt))
		flg[(int)(*((*fmt)++))] = 1;
	while (ft_isdigit(**fmt))
		flg[2] = (flg[2] * 10) + (*((*fmt)++) - '0');
	if (!flg[2] && **fmt == '*' && *(++(*fmt)))
		flg[2] = va_arg(*a, int);
	if (**fmt == '.' && ++flg[4] && ft_isdigit(*(++(*fmt))))
		while (ft_isdigit(**fmt))
			flg[3] = (flg[3] * 10) + (*((*fmt)++) - '0');
	if (!flg[3] && flg[4] && **fmt == '*' && *(++(*fmt)))
		flg[3] = va_arg(*a, int);
	if (**fmt == 'l' && *(++(*fmt)))
		flg['l']++;
	flg[1] = **fmt + (0 * flg[(int)(*((*fmt)++))]++);
	flg[5] = flg['+'] * '+' + flg[' '] * !flg['+'] * ' ';
	flg[5] += (flg['p'] + (flg['#'] * !!ft_strchr("xXo", flg[1]))) * '0';
	flg[6] = (flg[5] == '0') * !flg['o'] * 'x';
	flg[10] = 8 * flg['o'] + 10 * flg['u'] + 16 * !!ft_strchr("xXp", flg[1]);
	if (!ft_strchr("cspdiuxXofFgGeE", flg[1]) || flg[2] < 0 || flg[3] < 0)
		return (NULL);
	if (ft_strchr("xXs", flg[1]) && flg['0'])
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
		return ((char *)(0 * write(2, "invalid_ftprintf_flag\n", 22)));
	if (flg['l'] && flg[10])
		e = ft_itoa_base(va_arg(*a, unsigned long), flg[10]);
	if (flg['l'] && (flg['d'] || flg['i']))
		e = ft_itoa(va_arg(*a, long));
	if (!flg['l'] && flg[10])
		e = ft_itoa_base(va_arg(*a, unsigned int), flg[10]);
	if (!flg['l'] && (flg['d'] || flg['i']))
		e = ft_itoa(va_arg(*a, int));
	if (ft_strchr("fFgGeE", flg[1]))
		e = ft_strdup(":)double to str, F|G|E:)");
	if (flg['p'])
		e = ft_itoa_ulong((unsigned long)va_arg(*a, void *));
	if (flg['s'])
		e = ft_strdup(va_arg(*a, char *));
	if (flg['c'])
		e = ft_strdup((char [2]){(char)va_arg(*a, int), 0});
	return (ft_printf_trns(e, flg));
}

static char	*ft_printf_trns(char *e, int *f)
{
	if (f['s'] && !e)
		e = ft_strdup("(null)");
	if (!f['s'] && *e == '-')
		f[5] = *e + 0 * (long)ft_memmove(e, e + 1, ft_strlen(e));
	if (f[4] && f['s'])
		e[f[3]] = 0;
	f[7] = ft_max((f['0'] * f[2]) - !!f[5] - !!f[6], f[3] * !f['s']);
	while (f[7] > (int)ft_strlen(e))
		e = ft_strjoin("0", e) + (long)ft_free(e);
	e = ft_strjoin((char [3]){f[5], f[6], 0}, e) + (long)ft_free(e);
	while (f[2] > (int)ft_strlen(e) && f['-'] && !f['c'])
		e = ft_strjoin(e, " ") + (long)ft_free(e);
	while (f[2] > (int)ft_strlen(e) && !f['-'] && !f['c'])
		e = ft_strjoin(" ", e) + (long)ft_free(e);
	if (f[2] > 1 && f['c'] && f[2]--)
		e = ft_memset(ft_memset(ft_calloc(f[2] + 2, 1), ' ', f[2] + 1) + \
			!f['-'] * f[2], *e, 1) - !f['-'] * f[2] + (long)ft_free(e);
	f[8] = ft_strlen(e) * !f['c'] + ++f[2] * f['c'];
	if (ft_isalpha_upper(f[1]))
		ft_strtoupper(e);
	return (e);
}
