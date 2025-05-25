# LIBFT

## todo asap
- atoa_base is wrong, only need itoa(nbr, base) and atoa(nbr, srcB, dstB)
- ft_printf needs atoa reworked
- understand unit test
- ftscript, execute from anywhere to anywhere?
- ftscript, source, setup, toomanyargs, old makefile stuff,

## remove

## add
- `ft_strprintf`
- `ft_putnbr_base`
- linked list
- tree
- graph
- math

## review
- `ft_printf`, try without so many strdup
- `ft_strnjoin` so many strdup
- remove `ft_strjoin_free` if printf doesnt need it anymore
- stress test for printf, random, split
- makefile too heavy, create test folder with txt
- `ft_numcmp(void *a, void *b)` and `lst_sort` family

## classic libc inspiration

look through open source code, add and modify for needs

write better doc, descriptions, lists

headache everytime i have to change/check something, how to make easier??

### mem
- chr, cmp, cpy, move, set, bzero, calloc
- malloc, free
- realloc_str, swap, dup, join

### str
- len, nlen, lcpy, lcat, chr, rchr, cmp, ncmp, nstr
- join, dup
- strtrim, substr
- ndup, strsep, strprefix, strspn, strcspn, strtok, strpbrk, count, rev, replace

### split
- split, split_set, split_free, split_len, isquoted, split_quotes
- splittrim_quotes, strtrim_quotes, isquoted_closed

### nbr
- atoi, itoa, itoa_base and REVIEW
- math stuff

### write
- sprintf, fprintf, REVIEW printf

### other stuff
- strerror, basename, dirname, env_get, env_set
- isdigit_base

# haha

resume

something with chess

somethin gwith rubik

something with factorio

--

polish libft

polish minishell with nice libft
