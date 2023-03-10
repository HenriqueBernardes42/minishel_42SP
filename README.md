# minishell

## Bugs
- [ ] norm && leaks
- [x] :
```
echo ~
```
- [x] :
```
< non-existing echo hello | grep hello
```
- [x] issue with expansions 
```
echo "    $HOME       $PATH  "
```
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