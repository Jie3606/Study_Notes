### 1. **撤销本地的 commit 但保留修改（保留更改在工作区）**

如果你希望撤销本地的 commit，但是保留更改在工作区，这样你可以重新编辑文件并重新提交，你可以使用 `git reset --soft` 或 `git reset --mixed`。

#### 使用 `git reset --soft`

这个命令会撤销提交，但会将修改保留在暂存区（staging area），你可以重新编辑后再提交。

```c
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

### 2. **撤销本地 commit 并丢弃所有更改（彻底丢弃更改）**

如果你希望撤销本地 commit 并丢弃所有修改（包括工作区和暂存区的更改），可以使用 `git reset --hard`。

#### 使用 `git reset --hard`

```
git reset --hard HEAD~1
```

- 这个命令会彻底撤销最近的一个提交，并丢弃工作区和暂存区的所有更改。**注意：这个操作是不可恢复的，一旦执行后更改将丢失**。

### 3. **撤销多个 commit**

如果你想撤销多个提交，可以修改 `HEAD~1` 中的数字。例如，要撤销最近的两个提交：

```
git reset --soft HEAD~2
```

或者

```
git reset --mixed HEAD~2
```

如果你使用 `--hard`，则会丢弃最近两个提交的所有更改。

### 4. **撤销已推送的 commit**

如果你已经将提交推送到远程仓库，并且想要撤销这个提交，可以通过重置本地的提交并强制推送到远程仓库来覆盖远程仓库的历史。**注意：这会修改远程仓库的历史，可能会影响其他使用该仓库的人，应该小心使用**。

```
git reset --hard HEAD~1
git push origin master --force
```

- `git reset --hard HEAD~1` 会将本地的提交回退到上一个 commit。
- `git push origin master --force` 会将修改后的历史推送到远程仓库，覆盖远程的提交。

### 总结

- **保留更改**（在工作区或暂存区）：`git reset --soft` 或 `git reset --mixed`
- **彻底丢弃更改**：`git reset --hard`
- **撤销多个提交**：通过指定 `HEAD~n` 来撤销最近的多个提交
- **撤销已推送的 commit**：使用 `--force` 强制推送到远程仓库

- **`git show`**：查看最近一次提交的详细信息和差异。
- **`git show --stat`**：查看最近提交的文件修改统计。
- **`git diff HEAD~1 HEAD`**：查看当前提交与上一个提交之间的差异。
- **`git log -p -1`**：查看最近提交的详细差异。
- **`git diff <commit-id> <file-path>`**：查看某个特定文件的差异。

- **`git diff --cached --name-status`**：查看暂存区的文件名和文件状态（新增、修改、删除、重命名等）。

- **`git diff --cached --stat`**：查看暂存区的文件修改统计，包括行数和文件状态。
- **`git diff --cached -p`**：查看暂存区文件的详细差异，包括内容和权限变化。

```
git config --global core.editor vim
```

这会将 `vim` 设置为全局默认编辑器。

```
git config --global --get core.editor
```
