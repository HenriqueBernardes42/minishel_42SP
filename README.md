# minishell

## ! starting minishell tests on Wednesday, 18th Jan 

## Bugs
- awk + syntax error handling special chars between quotes (ls "(")
- expansions (ft_minishell_split, ft_child )
- signals:
- on Ctrl+d
minishell$ 
exit
make: *** [m] Error 1
- builtins: env vars added in the end, cd not working

## Docs
### Redirections
https://www.gnu.org/software/bash/manual/html_node/Redirections.html

### GNU History Library
https://tiswww.case.edu/php/chet/readline/history.html