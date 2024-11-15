# 基本指令

`git init`
 建立新的本地端 Repository。

`git clone [Repository URL]`
 复制远程的 Repository 文件到本地端。

`git status`
 检查本地档案异动状态。

`git add [``档案或文件夹``]`
 将指定的文件（或文件夹）加入版本控制。

`git commit`
 提交（commit）目前的异动。

`git commit -m "``提交说明内容``"`
 提交（commit）目前的异动并通过 -m 参数设定摘要说明文字。

`git log`
 查看先前的 commit 记录。

`git push`
 将本地端 Repository 的 commit 发布到远程。

`git push origin [BRANCH_NAME]`
 发布至远程指定的分支（Branch）

`git pull`
 将远程 Repository 的 更新拉回本地端。

`git branch`
 查看分支。

`git branch [BRANCH_NAME]`
 建立分支。

`git merge [BRANCH_NAME]`
 合并两条分支



git clone ssh://jieliu@172.16.63.202:29418/projects/RC2/ver_val && scp -p -P 29418 jieliu@172.16.63.202:hooks/commit-msg ver_val/.git/hooks/

git 在没有错误的情况下进行空的commit git commit

    git commit --allow-empty -m "empty commit"
    git commit --allow-empry -message (不需要填写提交信息)

git checkout master (切换到master分支，git 2.23以后版本，建议使用Switch进行切换，git checkout 用于恢复工作树文件)

git merge pa0 (当前分支为master) pa0  -> merge master

git checkout -b pa1 (创建或切换到新分支)
