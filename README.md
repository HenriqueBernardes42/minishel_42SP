# minishell

## Bugs
- [ ] awk **(in progress)**
- [x] syntax error handling special chars between quotes (ls "(")
- [ ] expansions (ft_minishell_split, ft_child ) **(in progress)**
- [ ] signals: double displaying prompt, Ctrl+d exiting with error ...
```
minishell$
exit
make: *** [m] Error 1
```
- [ ] builtins: env vars not in alphabetical order, cd not working

## Awk fix

```
static void	ft_prepare(t_data *data)
{
	char	*trimmed;
	int		i;

	i = -1;
	while (data->tab[++i] != NULL)
	{
		trimmed = NULL;
		if (data->tab[i][0] == '\'')
			trimmed = ft_strtrim (data->tab[i], "'");
		else if (data->tab[i][0] == '"')
			trimmed = ft_strtrim (data->tab[i], "\"");
		if (trimmed != NULL)
		{
			free (data->tab[i]);
			data->tab[i] = trimmed;
		}
	}
}
```

## Docs
### Redirections
https://www.gnu.org/software/bash/manual/html_node/Redirections.html

### GNU History Library
https://tiswww.case.edu/php/chet/readline/history.html
