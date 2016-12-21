# 本地仓库操作

git init        创建仓库
git status      查看状态
git add         添加文件到缓存区
git commit      提交缓存文件
git log         查看提交记录
git branch      查看分支, 创建新分支
git checkout    切换当前分支
git checkout -b 创建并切换到新分支
git merge       将指定分支合并到当前分支
git branch -d   删除分支
git branch -D   强制删除分支
git tag         查看标签, 在当前代码状态下新建标签(版本号)
git checkout    切换到指定标签的代码状态

# 远程仓库操作

ssh-keygen -t rsa     生成 Key
id_rea.pub            添加 Key
ssh -T git@github.com 测试连接
git push              把本地代码推到远程仓库
git pull              远程最新的代码更新到本地
git clone             克隆远程仓库到本地
git remote add        关联远程仓库
git remote -v         查看远程仓库

# 配置

## 设置用户名和邮箱

git config --global user.name "stormzhang"
git config --global user.email "stormzhang.dev@gmail.com"

## 设置别名

```
git config --global alias.co checkout  # 别名
git config --global alias.ci commit
git config --global alias.st status
git config --global alias.br branch
git config --global alias.psm 'push origin master'
git config --global alias.plm 'pull origin master'
```

### 设置日志格式

git log -–graph -–pretty=format:’%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset’ -–abbrev-commit –-date=relative

git config --global alias.lg "log
--graph
--pretty=format:'%Cred%h%Creset
-%C(yellow)%d%Creset
%s
%Cgreen(%cr)
%C(bold blue)<%an>%Creset'
--abbrev-commit --date=relative"

git config --global core.editor "vim"    # 设置Editor使用vim
git config --global color.ui true
git config --global core.quotepath false # 设置显示中文文件名

# 配置文件

./.git/config

~/.gitconfig

git config -l           # 查看项目配置文件
git config --global -l  # 查看用户配置文件

# 比较文件差异

git diff
git diff <$id1> <$id2>        # 比较两次提交之间的差异
git diff <branch1>..<branch2> # 在两个分支之间比较
git diff --staged             # 比较暂存区和版本库差异

git checkout develop
git checkout v1.0
git checkout ffd9f2dd68f1eb21d36cee50dbdd504e95d9c8f7 # 后面的一长串是commit_id，是每次commit的SHA1值，可以根据 git log 看到。
git checkout a.md

git stash
git stash list
git stash apply
git stash drop
git stash pop
git stash clear

git checkout master
git merge featureA
git rebase featureA

# 参考

[从0开始学习 GITHUB 系列](http://stormzhang.com/github/2016/06/19/learn-github-from-zero-summary
