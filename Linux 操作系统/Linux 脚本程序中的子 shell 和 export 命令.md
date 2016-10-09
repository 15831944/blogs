# 子 shell 与 export 命令

用户登录到Linux系统后，系统将启动一个用户shell。在这个shell中，可以使用shell命令或声明变量，也可以创建并运行shell脚本程序。

运行shell脚本程序时，系统将创建一个子shell。

此时，系统中将有两个shell，一个是登录时系统启动的shell，另一个是系统为运行脚本程序创建的shell。

当一个脚本程序运行完毕，它的脚本shell将终止，可以返回到执行该脚本之前的shell。

从这种意义上来说，用户可以有许多 shell，每个shell都是由某个shell（称为父shell）派生的。

在子shell中定义的变量只在该子shell内有效。

如果在一个shell脚本程序中定义了一个变量，当该脚本程序运行时，这个定义的变量只是该脚本程序内的一个局部变量，其他的shell不能引用它，要使某个变量的值可以在其他shell中被改变，可以使用 export 命令对已定义的变量进行输出。

export 命令将使系统在创建每一个新的 shell 时定义这个变量的一个拷贝。

这个过程称之为变量输出。

［例］在本例中，变量myfile是在dispfile脚本程序中定义的。然后用export命令将变量myfile输出至任何子shell，例如当执行 printfile脚本程序时产生的子shell。

dispfile 脚本程序清单：

```
myfile=”List”
export myfile
echo “Displaying $myfile”
pr –t –n $myfile
printfile
```

printfile 脚本程序清单：

```
echo “Printing $myfile”
lpr $myfile&
```

运行如下:

```
$dispfile
Displaying List
1 screen
2 modem
3 paper
Printing List
```
