# Internal Commands and Builtins

A builtin is a command contained within the Bash tool set, literally built in.

This is either for performance reasons -- builtins execute faster than external commands, which usually require forking off a separate process -- or because a particular builtin needs direct access to the shell internals.

A builtin may be a synonym to a system command of the same name, but Bash reimplements it internally. For example, the Bash echo command is not the same as /bin/echo, although their behavior is almost identical.

A keyword is a reserved word, token or operator. Keywords have a special meaning to the shell, and indeed are the building blocks of the shell's syntax. As examples, for, while, do, and ! are keywords. Similar to a builtin, a keyword is hard-coded into Bash, but unlike a builtin, a keyword is not in itself a command, but a subunit of a command construct.

##　区别

Generally, a Bash builtin does not fork a subprocess when it executes within a script. An external system command or filter in a script usually will fork a subprocess.

# 参考

[Advanced Bash-Scripting Guide Chapter 15. Internal Commands and Builtins](http://www.tldp.org/LDP/abs/html/index.html)
