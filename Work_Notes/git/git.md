### 基本指令

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

`git push origin HEAD:refs/for/master`
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

git 在没有错误的情况下进行空的commit git commit

    git commit --allow-empty -m "empty commit"
    git commit --allow-empry -message (不需要填写提交信息)

git checkout master (切换到master分支，git 2.23以后版本，建议使用Switch进行切换，git checkout 用于恢复工作树文件)

git merge pa0 (当前分支为master) pa0  -> merge master

git checkout -b pa1 (创建或切换到新分支)

### 全局设置 Git 默认编辑器为 Vim

运行以下命令，将 Git 的全局编辑器设置为 `vim`：

```
git config --global core.editor vim
```

这会将 `vim` 设置为全局默认编辑器。

  ```
git config --global --get core.editor
  ```

------

在 Git 中，如果你希望撤销本地的 commit，有几种不同的方法可以选择，具体取决于你是否希望保留更改并只是撤销提交，或者是否希望丢弃更改。以下是常见的几种情况和解决方法：

### 1. 撤销本地的 commit 但保留修改（保留更改在工作区）

如果你希望撤销本地的 commit，但是保留更改在工作区，这样你可以重新编辑文件并重新提交，你可以使用 `git reset --soft` 或 `git reset --mixed`。

#### 使用 `git reset --soft`

这个命令会撤销提交，但会将修改保留在暂存区（staging area），你可以重新编辑后再提交。

```
git reset --soft HEAD~1
```

- `HEAD~1` 表示上一个提交，你可以修改数字来撤销多个提交（例如 `HEAD~2` 表示撤销最近的两个提交）。
- 这个命令会撤销最近的一个提交，但保留所有修改在暂存区，方便你修改后再次提交。

#### 使用 `git reset --mixed`

如果你希望撤销提交，并且保留修改在工作区（不放回暂存区），可以使用 `git reset --mixed`：

```
git reset --mixed HEAD~1
```

- `--mixed` 会将最近一次提交的更改撤销，但不会保留这些更改在暂存区，它们会返回到工作区未暂存状态。

### 2. 撤销本地 commit 并丢弃所有更改（彻底丢弃更改）

如果你希望撤销本地 commit 并丢弃所有修改（包括工作区和暂存区的更改），可以使用 `git reset --hard`。

#### 使用 `git reset --hard`

```
git reset --hard HEAD~1
```

- 这个命令会彻底撤销最近的一个提交，并丢弃工作区和暂存区的所有更改。**注意：这个操作是不可恢复的，一旦执行后更改将丢失**。

### 3. 撤销多个 commit

如果你想撤销多个提交，可以修改 `HEAD~1` 中的数字。例如，要撤销最近的两个提交：

```
git reset --soft HEAD~2
```

或者

```
git reset --mixed HEAD~2
```

如果你使用 `--hard`，则会丢弃最近两个提交的所有更改。

### 4. 撤销已推送的 commit

如果你已经将提交推送到远程仓库，并且想要撤销这个提交，可以通过重置本地的提交并强制推送到远程仓库来覆盖远程仓库的历史。**注意：这会修改远程仓库的历史，可能会影响其他使用该仓库的人，应该小心使用**。

```
git reset --hard HEAD~1
git push origin master --force
```

- `git reset --hard HEAD~1` 会将本地的提交回退到上一个 commit。
- `git push origin master --force` 会将修改后的历史推送到远程仓库，覆盖远程的提交。

### 总结：

- **保留更改**（在工作区或暂存区）：`git reset --soft` 或 `git reset --mixed`
- **彻底丢弃更改**：`git reset --hard`
- **撤销多个提交**：通过指定 `HEAD~n` 来撤销最近的多个提交
- **撤销已推送的 commit**：使用 `--force` 强制推送到远程仓库

选择哪种方法取决于你是否希望保留本地更改，还是希望完全丢弃它们。

### 5. **查看重命名历史**

在 Git 中，重命名操作会被视为文件的删除和新文件的添加，但是 Git 能够识别这种变化。在查看提交历史时，可以通过 `git log` 来查看重命名操作。

如果你想查看文件的重命名历史，可以使用以下命令：

```
git log --follow -- <文件路径>
```

`--follow` 参数告诉 Git 在查找文件的提交历史时跟踪文件的重命名。

### 6. **关于重命名的注意事项**

- Git 会根据文件内容的相似度来判断是否是“重命名”，而不仅仅是文件名的变化。文件的内容如果有较大的变化，Git 可能不会将其视为重命名。
- 重命名操作会记录在 Git 的提交历史中，但如果你查看某个文件的历史时，需要使用 `--follow` 来确保 Git 能够识别文件重命名的历史。

这样，你就能在 Git 中正确处理文件或目录的重命名了！
