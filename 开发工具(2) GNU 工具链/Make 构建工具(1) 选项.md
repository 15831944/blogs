# 变量

## CFLAGS

1. CFLAGS 表示用于 C 编译器的选项
2. CXXFLAGS 表示用于 C++ 编译器的选项
3. CFLAGS 和 CXXFLAGS 这两个变量实际上涵盖了编译和汇编两个步骤
4. CFLAGS 可用于指定头文件(.h)的路径, 如: `CFLAGS=-I/usr/include -I/path/include`
5. 安装一个编译链的函数库时会在安装路径下建立一个 include 目录, 当安装过程中出现问题时, 可尝试把以前安装的包的 include 目录加入到 CFLAGS 变量中

## LDFLAGS

1. gcc 等编译器会用到的一些优化参数, 也可以在里面指定链接器查找库文件的位置, 如: `LDFLAGS=-L/usr/lib -L/path/to/your/lib`
2. 安装一个编译链的函数库时会在安装路径下建立一个 lib 目录, 如果安装了某个包, 而安装另一个包时提示找不到, 可尝试把那个包的 lib 路径加入到 LDFALGS 变量中
3. LDFLAGS 指定 -L 虽然能让链接器找到指定库进行链接, 但是运行时链接器却可能找不到这个库, 若要运行时库文件的路径也得到扩展, 则需要增加这该库给 "-Wl,R"

`LDFLAGS = -L/var/xxx/lib -L/opt/mysql/lib -Wl,R/var/xxx/lib -Wl,R/opt/mysql/lib`

4. 如果在执行 `./configure` 以前, 设置 LDFLAGS 环境变量 `export LDFLAGS="-L/var/xxx/lib -L/opt/mysql/lib -Wl,R/var/xxx/lib -Wl,R/opt/mysql/lib"`, 则执行 configure 以后, Makefile 将会设置这个选项, 链接时会有这个参数, 编译出来的可执行程序的库文件搜索路径就得到扩展了.

## LIBS

1. LIBS 用于告诉链接器要链接哪些库函数文件, 如 `LIBS = -lpthread -liconv`
2. LDFLAGS 和 LIBS 这两个参数在链接阶段都会加上, 所以这两个变量的值互换, 也没有问题

# 参考

1. [gcc如何指定目标文件的输出目录？](http://bbs.csdn.net/topics/90512346)
