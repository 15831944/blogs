# Snippets

1. 使用 `alt-shift-S` 查找和执行当前可用的代码段

默认快捷键配置

```
'atom-text-editor:not([mini])':
  'alt-shift-S': 'snippets:available'
```

## Markdown 格式

1. 按下快捷键后，按 tab 键，即可显示出代码段效果

| keystroke | snippets       |
| --------- | -------------- |
| b         | bond text      |
| img       | embedded image |
| legal     | Copyright      |
| i         | italic         |
| l         | link           |
| code      | code           |
| t         | todo list      |
| lorem     | lorem ipsum    |

# CSON

1. CSON is a text format for storing structured data in the form of simple objects made up of key-value pairs.
2. Objects are the backbone of any CSON file, and are delineated by indentation.
3. preprocessors for Javascript

```
key:
  key: value
  key: value
  key: [value, value]
```

# LESS

1.  preprocessors for CSS

# Style Tweaks



# Keybindings

keymap.cson

```
'atom-text-editor':				// contexts:
  'enter': 'editor:newline'		//   key: events

'atom-text-editor[mini] input':
  'enter': 'core:confirm'
```
