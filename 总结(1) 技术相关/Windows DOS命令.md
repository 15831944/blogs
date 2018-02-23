move 移动并重命名文件和目录

要移动的至少一个文件：
move [/y|/-y] [drive:][path]filename1[,...]destination

要重命名一个目录：
move [/y|/-y] [drive:][path]dirname1 dirname2



dir [dirve:] [path] [filename] [/a[[:]attributes]] 
[/b] ;列出每个目录名或文件名,每行一个,但不显示标题信息或摘要
[/c]
[/d] ;与w相同,但文件按列排序
[/l]
[/n] 
[/o[[:]sortorder]] 
[/p](pause) ;ctrl+c结束显示
[/q] 
[/r] 
[/s] 
[/t[[:]timefield]] 
[/w] (wide) ;每行只显示5个文件名和扩展名
[/x] 
[/4]
dir c:\windows
dir c:\windows /p(page)
dir c:\windows /a:h(hide)
dir c:\windows /a:s(system)
dir c:\windows /a:r(readonly)
dir c:\windows /o:n(name)
dir c:\windows /o:e(extension)

cd(change directory)
cd [/d] [drive:] [path](d开关为directory)
cd [..] (.代表此目录本身 ..代表此目录的上一层目录)
cd [\](反斜杠标识根目录)

format(格式化)

md [drive:] [path]

rd [/s] [/q](quiet) [drive:]path
