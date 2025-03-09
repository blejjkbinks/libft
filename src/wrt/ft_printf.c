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

//flg[0] ->
//flg["%-+ '#"]
//flg[1] -> "width"
//flg[2] -> ".precision"
//flg[3] -> precision bool
//flg[4] -> "%cspdiuxXobfFgG"
//flg["%cspdiuxXobfFgG"]
//flg[5] -> base
//flg[6] -> sign
//flg[7] -> elem.len
//flg[8] -> diff'0'		((001234) len=4, w=6, d=2)
//flg[9] -> diff' '
//flg[10]-> ft_strlen(e) or ft_strlen('c')

void	ft_printf_debug(char *elem, int *flg)
{
	char	**n;
	int		i;

	n = ft_split("width,precision,p_bool,type,base,sign,len,diff0,diff", ',');
	printf("{");
	i = 0;
	while (n[i])
	{
		if (flg[i + 1] && i != 3 && ft_strcmp(n[i], "sign"))
			printf("[%s:%d]", n[i], flg[i + 1]);
		if (flg[i + 1] && !ft_strcmp(n[i], "sign"))
			printf("[%s:%c]", n[i], flg[i + 1]);
		i++;
	}
	while (i < 128)
	{
		if (ft_isprint(i) && flg[i])
			printf("[%c]", i);
		i++;
	}
	printf("->|%s|}\n", elem);
	ft_split_free(n);
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
			ft_printf_debug(elem, flg);
			if (!elem)
				break ;
			len += flg[7] + 0 * write(1, elem, flg[7]) + (long)ft_free(elem);
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
		flg[1] = (flg[1] * 10) + (*((*fmt)++) - '0');
	if (!flg[1] && **fmt == '*' && *(++(*fmt)))
		flg[1] = va_arg(*a, int);
	if (**fmt == '.' && ++flg[3] && ft_isdigit(*(++(*fmt))))
		while (ft_isdigit(**fmt))
			flg[2] = (flg[2] * 10) + (*((*fmt)++) - '0');
	if (!flg[2] && flg[3] && **fmt == '*' && *(++(*fmt)))
		flg[2] = va_arg(*a, int);
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
		return ((char *)(0 * write(1, "invalid_printf_flag\n", 20)));
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
	return (ft_printf_trns(e, flg));
}

static char	*ft_printf_trns(char *e, int *flg)
{
	if (flg[3] && flg['s'] && ft_strlen(e) > (size_t)flg[2])
		e[flg[2]] = 0;
	flg[8] = flg[2] - ft_strlen(e);
	if (flg[3] && !flg['s'] && ft_strlen(e) < (size_t)flg[2])
		e = ft_memmove(ft_memset(ft_calloc(flg[2] + 1, 1), '0', flg[2]) + \
			flg[8], e, ft_strlen(e)) - flg[8] + (long)ft_free(e);
	if (flg['p'] || (flg['#'] && ft_strchr("xX", flg[4])))
		e = ft_strjoin("0x", e) + (long)ft_free(e);
	if (flg[6])
		e = ft_strjoin((char [2]){flg[6], 0}, e) + (long)ft_free(e);
	flg[10] = ft_strlen(e) * !flg['c'] + flg['c'];
	flg[9] = !flg['-'] * (flg[1] - flg[10]);
	if ((flg[1] > (int)ft_strlen(e) && !flg['c']) || (flg[1] > 1 && flg['c']))
		e = ft_memmove(ft_memset(ft_calloc(flg[1] + 1, 1), ' ', flg[1]) + \
			flg[9], e, flg[10]) - flg[9] + (long)ft_free(e);
	flg[7] = flg[1] + !flg[1] * flg['c'] + !flg[1] * !flg['c'] * ft_strlen(e);
	return (e);
}

//!flg['-'] * (w - (ft_strlen(e) * !flg['c']) + flg['c'])

/*
while (flg[3] && !flg['s'] && ft_strlen(e) < p)
	e = ft_strjoin("0", e) + (long)ft_free(e);
*/

/*
	while (w > ft_strlen(e) && !flg['-'] && !flg['c'])
		e = ft_strjoin(" ", e) + (long)ft_free(e);
	while (w > ft_strlen(e) && flg['-'] && !flg['c'])
		e = ft_strjoin(e, " ") + (long)ft_free(e);
*/

/*
if (w > 1 && flg['c'])
e = ft_memset(ft_memset(ft_calloc(w + 1, 1), ' ', w) + (!flg['-'] * \
	(w - 1)), *e, 1) - (!flg['-'] * (w - 1)) + (long)ft_free(e);
*/

/*
	if (w > 1 && flg['c'])
	{
		p = (size_t)ft_memset(ft_calloc(w + 1, 1), ' ', w);
		((char *)p)[!flg['-'] * (w - 1)] = *e;
		free(e);
		e = (char *)p;
	}
*/
