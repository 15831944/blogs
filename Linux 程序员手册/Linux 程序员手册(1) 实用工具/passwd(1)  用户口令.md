PASSWD(1)                              User Commands                             PASSWD(1)






NAME
       passwd - change user password
       
       passwd - 修改用户口令


SYNOPSIS
       passwd [options] [LOGIN]


DESCRIPTION
       The passwd command changes passwords for user accounts. A normal user may only
       change the password for his/her own account, while the superuser may change the
       password for any account.  passwd also changes the account or associated password
       validity period.
       
       passwd命令修改用户账户的口令。普通用户只修改他/她自己的账户的口令，而超级用户可能
       修改任何账户的口令。passwd也可修改账户或与其关联的口令的有效期。


   Password Changes
       The user is first prompted for his/her old password, if one is present. This
       password is then encrypted and compared against the stored password. The user has
       only one chance to enter the correct password. The superuser is permitted to bypass
       this step so that forgotten passwords may be changed.
       
       用户首先被提示输入他/她的旧口令，如果可用。此口令随后被加密并且和已存储的口令相比较。
       用户只有一次机会来输入正确的口令。超级用户被允许跳过这一步，这样已忘记的密码也可被修改。


       After the password has been entered, password aging information is checked to see
       if the user is permitted to change the password at this time. If not, passwd
       refuses to change the password and exits.
       
       输入口令后，口令变化信息被检查，来判断用户当前是否被允许修改口令。如果不允许，
       passwd 拒绝修改口令并退出。


       The user is then prompted twice for a replacement password. The second entry is
       compared against the first and both are required to match in order for the password
       to be changed.
       
       用户随后被提示输入两次新口令，第二次输入和第一次输入相比较，并且两次输入必须匹配，为
       使口令被修改。
       
       Then, the password is tested for complexity. As a general guideline, passwords
       should consist of 6 to 8 characters including one or more characters from each of
       the following sets:
       
       然后，对口令进行复杂性测试。一般原则，口令应该包含6到8个字符，


       ·   lower case alphabetics
       
       ·   小写字母


       ·   digits 0 thru 9
       
       ·   数字0到9


       ·   punctuation marks
       
       ·   标点符号


       Care must be taken not to include the system default erase or kill characters.
       passwd will reject any password which is not suitably complex.
       
       必需要小心不要包含系统默认的擦除字符或抹行符。passwd会拒绝任何不够适当复杂的口令。


   Hints for user passwords
       The security of a password depends upon the strength of the encryption algorithm
       and the size of the key space. The legacy UNIX System encryption method is based on
       the NBS DES algorithm. More recent methods are now recommended (see
       ENCRYPT_METHOD). The size of the key space depends upon the randomness of the
       password which is selected.
       
       口令的安全性决定于加密算法的长度和键盘空间大小。传统UNIX系统加密方案基于NBS DEC算法。
       更多最近的方法已被推荐（参见ENCRYPT_METHOD）。选择的口令的随机程度取决于键盘大小。


       Compromises in password security normally result from careless password selection
       or handling. For this reason, you should not select a password which appears in a
       dictionary or which must be written down. The password should also not be a proper
       name, your license number, birth date, or street address. Any of these may be used
       as guesses to violate system security.
       
       口令安全性的妥协通常起因于不小心的口令选择和操作。处于这个考虑，你不应该选择字典中
       存在的或必需写下来的口令。口令也不应该是真实姓名，你的身份证号码，生日或街道地址。
       这些都可能被用于妨碍系统安全的猜测。


       You can find advices on how to choose a strong password on
       http://en.wikipedia.org/wiki/Password_strength
       
       你可以在以下网址找到关于如何选择可靠的口令的建议


OPTIONS
       The options which apply to the passwd command are:
       
       passwd命令提供的选项有：


       -a, --all
           This option can be used only with -S and causes show status for all users.
           
           此选项只能和-S选项联用于显示所有用户状态的情况。


       -d, --delete
           Delete a user's password (make it empty). This is a quick way to disable a
           password for an account. It will set the named account passwordless.
           
           删除用户的口令（使之为空）。这是使一个账户的口令无效的快捷的方式。它会使
           指定的账户设置为无密码。


       -e, --expire
           Immediately expire an account's password. This in effect can force a user to
           change his/her password at the user's next login.
           
           使一个账户的口令立即过期。这实际上强迫用户在下次登录时修改密码。


       -h, --help
           Display help message and exit.
           
           显示帮助信息并退出。


       -i, --inactive INACTIVE
           This option is used to disable an account after the password has been expired
           for a number of days. After a user account has had an expired password for
           INACTIVE days, the user may no longer sign on to the account.
           
           此选项用于在口令过期几天后禁用该账户。用户账号的口令过期INACTIVE指定的天数后，
           该用户将无法再登录此账号。


       -k, --keep-tokens
           Indicate password change should be performed only for expired authentication
           tokens (passwords). The user wishes to keep their non-expired tokens as before.
           
           口令修改提示应该只作用于过期的认证标记。用户希望依旧保留他们的未过期标记。


       -l, --lock
           Lock the password of the named account. This option disables a password by
           changing it to a value which matches no possible encrypted value (it adds a ´!´
           at the beginning of the password).
           
           锁定指定账号的口令。此选项通过修改口令为一个不匹配任何已有加密值的口令来禁用该
           口令（它会在口令的起始处加！号）。


           Note that this does not disable the account. The user may still be able to
           login using another authentication token (e.g. an SSH key). To disable the
           account, administrators should use usermod --expiredate 1 (this set the
           account's expire date to Jan 2, 1970).
           
           注意这样做并没有禁用该账号。用户依然可以用另一个认证的标记登录（例如SSH key）。
           要禁用该账户，系统管理员应该用usermod --expiredate 1（设置账号到期日为1970年1月2日）


           Users with a locked password are not allowed to change their password.
           
           口令被锁定的用户不允许修改其口令。


       -n, --mindays MIN_DAYS
           Set the minimum number of days between password changes to MIN_DAYS. A value of
           zero for this field indicates that the user may change his/her password at any
           time.
           
           设置口令修改的最小天数间隔为 MIN_DAYS。此字段设为0表示用于可以随时修改其口令。


       -q, --quiet
           Quiet mode.
           
           静默模式。


       -r, --repository REPOSITORY
           change password in REPOSITORY repository
           
           在资源库REPOSITORY中修改口令。


       -S, --status
           Display account status information. The status information consists of 7
           fields. The first field is the user's login name. The second field indicates if
           the user account has a locked password (L), has no password (NP), or has a
           usable password (P). The third field gives the date of the last password
           change. The next four fields are the minimum age, maximum age, warning period,
           and inactivity period for the password. These ages are expressed in days.
           
           显示账户状态信息。账户信息包含7个字段。第1个字段是用户的登录名。第2个字段指示用户
           账号口令是锁定(L)、无口令(NP)还是有可用口令(P)。第3个字段给出最后一次口令修改的
           日期。接下来4个字段是最小有效期，最大有效期，警告字段和口令的休止期。这些时期用天标志。


       -u, --unlock
           Unlock the password of the named account. This option re-enables a password by
           changing the password back to its previous value (to the value before using the
           -l option).
           
           解锁指定账号的口令。此选项通过把口令改回它原来的值（使用-l选项前的值）来重新使能口令。


       -w, --warndays WARN_DAYS
           Set the number of days of warning before a password change is required. The
           WARN_DAYS option is the number of days prior to the password expiring that a
           user will be warned that his/her password is about to expire.
           
           设置口令需要修改前发出警告的天数。WARN_DAYS选项是口令过期前的天数。据到期日这些天数时，
           用户将被警告其口令即将过期。


       -x, --maxdays MAX_DAYS
           Set the maximum number of days a password remains valid. After MAX_DAYS, the
           password is required to be changed.
           
           设置口令有效的最大天数。MAX_DAYS天数后，口令需要修改。


CAVEATS
       Password complexity checking may vary from site to site. The user is urged to
       select a password as complex as he or she feels comfortable with.
       
       对于不同的站点口令复杂度检查可能会不同。强烈建议用户选择一个他/她感觉合适的尽
       可能复杂的口令。


       Users may not be able to change their password on a system if NIS is enabled and
       they are not logged into the NIS server.
       
       用户可能不允许修改其口令，在使能NIS的系统中但未登录NIS服务时。


       passwd uses PAM to authenticate users and to change their passwords.
       
       passwd使用PAM认证用户和修改其口令。


FILES
       /etc/passwd
           User account information.
           
           记录用户账号信息。


       /etc/shadow
           Secure user account information.
           
           保护用户账号信息。


       /etc/pam.d/passwd
           PAM configuration for passwd.
           
           用于passwd的PAM配置。


EXIT VALUES
       The passwd command exits with the following values:
       
       passwd命令以下列值退出：


       0
           success
           
           成功


       1
           permission denied
           
           权限不足


       2
           invalid combination of options
           
           选项组合无效


       3
           unexpected failure, nothing done
           
           意外退出，未进行任何操作


       4
           unexpected failure, passwd file missing
           
           意外退出，口令文件丢失


       5
           passwd file busy, try again
           
           口令文件忙，再次尝试


       6
           invalid argument to option
           
           无效的选项参数。


SEE ALSO
       passwd(5), shadow(5), usermod(8).






User Commands                           02/21/2011                               PASSWD(1)
