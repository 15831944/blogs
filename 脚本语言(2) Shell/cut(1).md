# Synopsis

cut OPTION... [FILE]...

# Optoins

| short | long                      | meaning |
| ----- | ------------------------- | ------- |
| -b    | --bytes=LIST              | select only these bytes
| -c    | --characters=LIST         | select only these characters
| -f    | --fields=LIST             | select only these fields
| -d    | --delimiter=DELIM         | use DELIM instead of TAB for field delimiter
|       | --complement              | complement the set of selected bytes, characters or fields
| -s    | --only-delimited          | do not print lines not containing delimiters
|       | --output-delimiter=STRING | use STRING as the output delimiter the default is to use the input delimiter
| -z    | --zero-terminated         | line delimiter is NUL, not newline

1. 没有分隔符也就无法将一行分为几段, -f 会打印这些行, -s 会忽略这些行
2. Use  one,  and only one of -b, -c or -f.
3. Each LIST is made up of one range, or many ranges separated by commas.
4. Selected input is written in the same order that it is read, and is written exactly once.

# Range

Each range is one of:

| range | meaning |
| ----- | ------- |
| N     | N'th byte, character or field, counted from 1
| N-    | from N'th byte, character or field, to end of line
| N-M   | from N'th to M'th (included) byte, character or field
| -M    | from first to M'th (included) byte, character or field


# 参考

1. [linux之cut用法](http://www.cnblogs.com/dong008259/archive/2011/12/09/2282679.html)
