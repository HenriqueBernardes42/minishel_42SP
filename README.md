# minishell

## Bugs
- [ ] issue with expansions 
```
echo "    $HOME       $PATH  "
```
- [ ] leaks
- [x] pipes && redirs (test further)
- [x] child minishell
- [x] prompt on cmd paste
- [x] forbidden readline funcs at SIGNINT handling
- [x] forbidden readline funcs in assert_not_finished history
- [x] awk 
- [x] syntax error handling special chars between quotes (ls "(")
- [x] signals

## Docs
### Redirections
https://www.gnu.org/software/bash/manual/html_node/Redirections.html

### GNU History Library
https://tiswww.case.edu/php/chet/readline/history.html


// remove last in history = clear history + add history til last


<!-- void	ft_remove_last_history(t_data *data)
{
	struct _hist_entry	*entry;

	ft_assert_not_null(data, data);
	if (where_history () >= 0)
	{
		entry = remove_history (where_history () - 1);
		if (entry != NULL)
		{
			free (entry->line);
			free (entry->data);
			free (entry);
		}
	}
	add_history (data->line);
} -->