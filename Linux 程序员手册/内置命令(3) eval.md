eval arg1 [arg2] ... [argN]

Combines the arguments in an expression or list of expressions and evaluates them. Any variables within the expression are expanded. The net result is to convert a string into a command.

Tip

The eval command can be used for code generation from the command-line or within a script.

```
$ command_string="ps ax"
$ process="ps ax"
$ eval "$command_string" | grep "$process"
26973 pts/3    R+     0:00 grep --color ps ax
26974 pts/3    R+     0:00 ps ax
```

Each invocation of eval forces a re-evaluation of its arguments.

```
a='$b'
b='$c'
c=d

echo $a             # First level.
$b
eval echo $a        # Second level.
$c
eval eval echo $a   # Third level.
d
```
