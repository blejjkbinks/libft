# LIBFT

## remove
- `ft_split_remove`
- `ft_split_realloc`, only needed by `split_quotes`, can make its own

## add
- `ft_random()`
- ~~`quotes` category~~ done
- `ft_strprintf`
- `ft_putnbr_base`

## review
- main function at the top, statics in order
- `split_quotes` is all wrong
- `ft_printf`, try without so many strdup
- remove `ft_strjoin_free` if printf doesnt need it anymore
- stress test for printf, random, split
