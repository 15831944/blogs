说明：原文档使用man命令重定向到本地文件获取的。翻译纯属自娱自乐，望指正。

TFTP(1) BSD General Commands ManualTFTP(1)


NAME
tftp — trivial file transfer program


SYNOPSIS
tftp [host]


DESCRIPTION
Tftp is the user interface to the Internet TFTP (Trivial File Transfer Protocol),
which allows users to transfer files to and from a remote machine.  The remote host
may be specified on the command line, in which case tftp uses host as the default
host for future transfers (see the connect command below).
Tftp是网络TFTP的用户接口，允许用户同远程设备传输文件。远程主机可以在命令行中指定，
这种情况下，tftp用host作为默认主机来进行以后的传输（见下面的连接命令）。


COMMANDS
Once tftp is running, it issues the prompt and recognizes the following commands:
一旦tftp运行起来，它发出提示符并且识别以下命令：


? command-name ...
Print help information.
打印帮助信息


ascii Shorthand for "mode ascii"
文本模式的简写


binary Shorthand for "mode binary"
二进制模式的简写


connect host-name [port]
Set the host (and optionally port) for transfers.  Note that the TFTP proto‐
col, unlike the FTP protocol, does not maintain connections betwen trans‐
fers; thus, the connect command does not actually create a connection, but
merely remembers what host is to be used for transfers.  You do not have to
use the connect command; the remote host can be specified as part of the get
or put commands.
设置主机（选择性的设置端口）用于传输。注意，TFTP协议，不同于FTP协议，不维持
各次传输指间的连接；因此，connect命令并非真正的创建了一个连接，而只是记住用
于传输的主机。你并非必须使用connect命令；远程主机可以被识别为get或put命令的
一部分。


get filename
get remotename localname
get file1 file2 ... fileN
Get a file or set of files from the specified sources.  Source can be in one
of two forms: a filename on the remote host, if the host has already been
specified, or a string of the form hosts:filename to specify both a host and
filename at the same time.  If the latter form is used, the last hostname
specified becomes the default for future transfers.
从指定的源获得一个或一组文件。源可以是两种形式中的一种：指定的远程主机上的文
件名，或者是hosts:filename组成的字符串的形式，用于同时指定主机和文件名。如果
用后一种形式，最后指定的主机名称成为用于以后传输的默认设备。


mode transfer-mode
Set the mode for transfers; transfer-mode may be one of ascii or binary.
The default is ascii.
设置传输模式；参数transfer-mode可以是ascii或binary中的一个，默认是ascii。


put file
put localfile remotefile
put file1 file2 ... fileN remote-directory
Put a file or set of files to the specified remote file or directory.  The
destination can be in one of two forms: a filename on the remote host, if
the host has already been specified, or a string of the form hosts:filename
to specify both a host and filename at the same time.  If the latter form is
used, the hostname specified becomes the default for future transfers.  If
the remote-directory form is used, the remote host is assumed to be a UNIX
machine.
上传一个或一组文件到指定的远程文件或目录。目标可以是两种形式中的一种：指定的
远程主机上的文件名，或者是host:filename组成的字符串形式，用于同时指定主机和
文件名。如果用后一种形式，最后指定的主机名称成为用于以后传输的默认设备。如果
用远程目录形式，则认为远程主机是一台UNIX主机。



quit Exit tftp.  An end of file also exits.
退出tftp，文件结束也会退出。


rexmt retransmission-timeout
Set the per-packet retransmission timeout, in seconds.
设置数据包重发超时秒数。


status Show current status.
显示当前状态。


timeout total-transmission-timeout
Set the total transmission timeout, in seconds.
设置总体传输超时秒数。


trace Toggle packet tracing.
切换数据包追踪。


verbose Toggle verbose mode.
切换详细模式。


BUGS
Because there is no user-login or validation within the TFTP protocol, the remote
site will probably have some sort of file-access restrictions in place.  The exact
methods are specific to each site and therefore difficult to document here.
因为TFTP协议中没有用户登录或验证，远程站点将可能有适当的文件访问权限。不同站点有特
定的方式，因此难于在此说明。


HISTORY
The tftp command appeared in 4.3BSD.
tftp命令最早出现在4.3BSD中。


Linux NetKit (0.17)                   August 15, 1999                  Linux NetKit (0.17)
