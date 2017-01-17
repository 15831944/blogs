# 本地仓库操作

```
git init dirpath				# 在指定目录中初始化 git 仓库 `.git`, 默认生成 master 主分支, 不会影响目录中原有文件
git status						# 查看仓库状态, 默认在 master 主分支
git add filename				# 添加文件到缓存区
git rm –cached filename			# 移除缓存区中的指定文件
git commit -m ‘commit message’	# 提交缓存文件, -m 选项指定提交信息
git log							# 查看所有 commit 记录
git branch						# 查看当前分支(有星号标识)状态
git branch branchname			# 新建分支(内容和主分支一样?从主分支新建还是从当前分支新建?), 但仍处于原分支
git checkout branchname			# 切换到指定分支
git checkout -b branchname		# 创建新分支并直接切换到该新分支
git checkout tagname			# 回滚到指定标签的代码状态(release 版本)
git checkout commit_id			# 切换到某次提交, commit_id 是每次 commit 的 SHA1 值, 可以使用 git log 命令查看
git checkout filename			# 撤销还没有 add 进暂存区的文件, 还原原文件内容
git merge branchname			# 将指定分支合并到当前分支, 依然能够分辨合并前的两个分支, 例如先切换到 master 分支, 再把指定分支合并过来
git rebase branchname			# 将指定分支合并到当前分支, 重新组织, 无法分辨合并前的两个分支
git branch -d branchname		# 删除分支
git branch -D branchname		# 强制删除分支
git tag tagname					# 在当前代码状态下新建标签
git tag							# 查看历史标签记录
git diff						# 比较当前文件和暂存区文件差异
git diff <$id1> <$id2>			# 比较两次提交之间的差异
git diff <branch1>..<branch2>	# 在两个分支之间比较
git diff --staged				# 比较暂存区和版本库差异
git stash						# 把当前分支所有没有 commit 的写了一半的代码先暂存起来, 以便先进行紧急任务
git stash list					# 查看暂存区的记录
git stash apply					# 还原被 stash 的代码
git stash drop					# 删除最近一条 stash 记录
git stash drop stash_id			# 删除指定一条 stash 记录
git stash pop					# 还原被 stash 的代码且删除最近一条 stash 记录
git stash clear					# 清空所有 stash 记录
git show
git mv
git reset
git bisect
git grep
```

# 远程仓库操作

```
git clone git@github.com:username/repositoryname.git				# 克隆远程仓库到本地
git remote add origin git@github.com:username/remoterepository.git	# 将当前本地仓库关联到远程仓库(必须已存在), 指定远程仓库名称为 origin, 之后就可直接 push 和 pull 到该名称
git remote -v														# 查看当前所有远程仓库
git pull origin master --allow-unrelated-histories		# 远程最新的代码更新到本地
git push origin master									# 把本地代码推到远程仓库(origin 远程仓库的 master 分支), 先 pull 再 push, 不易发生冲突
git fetch
```

# SSH

```
ssh-keygen -t rsa		# 生成 rsa 算法密钥, 得到 id_rsa 和 id_rsa.pub 两个文件
ssh -T git@github.com	# 测试是否连接成功
```

# 日志

```
git log -–graph -–pretty=format:’%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset’ -–abbrev-commit –-date=relative
```

# 配置

```
git config --global user.name "stormzhang"					# 设置用户名(–global 参数表示全局设置, 切换到项目仓库并去掉 –global 参数可单独设置该项目)
git config --global user.email "stormzhang.dev@gmail.com"	# 设置邮箱, 提交代码配置的邮箱跟 GitHub 上的邮箱须一致

git config --global alias.co checkout						# 设置命令别名
git config --global alias.ci commit
git config --global alias.st status
git config --global alias.br branch
git config --global alias.psm 'push origin master'
git config --global alias.plm 'pull origin master'
git config --global alias.lg "log --graph --pretty=format:'%Cred%h%Creset' --abbrev-commit --date=relative"		# 设置日志格式命令别名

git config --global core.editor "vim"						# 设置 Editor 使用 vim
git config --global core.quotepath false					# 设置显示中文文件名

git config --global color.ui true
```

# 配置文件及操作

1. 项目配置文件: `./.git/config`
2. 用户配置文件: `~/.gitconfig`

```
git config -l           # 查看项目配置文件
git config --global -l  # 查看用户配置文件
```

# 比较文件差异

```
git merge featureA
git rebase featureA
```
