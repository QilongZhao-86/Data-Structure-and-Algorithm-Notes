
# missing semester·计算机教育中缺失的学期
---

# 🚀 Git + GitHub 使用教程

## 🧩 一、初次配置（每台设备只需一次）

```bash
# 设置全局用户名和邮箱（用于提交记录）
git config --global user.name "你的名字"
git config --global user.email "你的邮箱@example.com"

# 检查配置
git config --list
```

### SSH 密钥配置（推荐）

```bash
# 生成 SSH 密钥（建议用 ed25519）
ssh-keygen -t ed25519 -C "你的邮箱@example.com"

# 查看公钥（复制内容到 GitHub → Settings → SSH and GPG keys）
cat ~/.ssh/id_ed25519.pub

# 测试连接是否成功
ssh -T git@github.com
```

---

## 🧱 二、仓库初始化与上传（首次建立远程仓库）

```bash
# 初始化 Git 仓库
git init

# 添加所有文件
git add .

# 提交
git commit -m "Initial commit"

# 添加远程仓库（替换为你的地址）
git remote add origin git@github.com:你的用户名/仓库名.git

# 推送到 GitHub
git push -u origin main   # 或 master
```

---

## 🧲 三、在新设备上拉取项目

```bash
# 克隆远程仓库
git clone git@github.com:你的用户名/仓库名.git

# 进入目录
cd 仓库名
```

---

## 🧠 四、日常开发流程（多设备共用核心）

### 1. 同步远程代码（开始工作前）

```bash
git checkout main
git pull --rebase origin main
```

### 2. 新建分支进行开发

```bash
# 创建并切换到新分支
git checkout -b feat/功能名

# 编辑代码后
git add .
git commit -m "实现了 XXX 功能"
```

### 3. 推送分支到 GitHub

```bash
git push -u origin feat/功能名
```

### 4. 合并分支（通过 GitHub PR 或本地合并）

```bash
# 回到主分支
git checkout main

# 拉取最新
git pull --rebase origin main

# 合并开发分支
git merge feat/功能名

# 推送更新
git push origin main

# 删除已合并分支
git branch -d feat/功能名
git push origin --delete feat/功能名
```

---

## 🔁 五、跨设备同步与更新

```bash
git pull --rebase origin main     # 获取最新版本
git checkout -b feat/xxx          # 新分支继续开发
# 修改代码……
git add .
git commit -m "更新了功能"
git push -u origin feat/xxx
```

---

## ⚡ 六、冲突处理

```bash
# 拉取时有冲突
git pull --rebase origin main
# Git 会提示冲突文件，打开编辑器手动解决

# 解决后：
git add 发生冲突的文件
git rebase --continue    # 若是 rebase 情况
# 或者直接提交合并
git commit -m "解决冲突"

git push origin main
```

---

## 📦 七、暂存与切换分支

```bash
# 临时保存未提交改动
git stash

# 切换分支或更新
git checkout main
git pull --rebase origin main

# 恢复之前改动
git stash pop
```

---

## 🧰 八、查看与回溯

```bash
git status        # 当前状态
git log --oneline --graph --decorate --all   # 简洁查看提交历史
git diff          # 查看改动
git branch        # 查看分支
git remote -v     # 查看远程仓库
git tag           # 查看标签
```

---

## 🧨 九、版本回退与撤销

```bash
git reset --hard HEAD~1        # 回退到上一个提交（危险，会丢改动）
git revert 提交ID              # 创建一个新的反向提交（安全）
git checkout 文件名            # 撤销工作区修改
```

---

## 🧱 十、子命令速查表

| 操作    | 命令                   | 说明           |
| ----- | -------------------- | ------------ |
| 初始化仓库 | `git init`           | 在当前目录创建本地仓库  |
| 添加文件  | `git add .`          | 添加全部改动到暂存区   |
| 提交更改  | `git commit -m "信息"` | 记录改动         |
| 查看状态  | `git status`         | 显示当前改动情况     |
| 创建分支  | `git branch 分支名`     | 创建新分支        |
| 切换分支  | `git checkout 分支名`   | 切换分支         |
| 合并分支  | `git merge 分支名`      | 合并代码         |
| 拉取远程  | `git pull --rebase`  | 更新并整合最新改动    |
| 推送远程  | `git push`           | 上传代码到 GitHub |
| 查看日志  | `git log --oneline`  | 简略提交历史       |
| 储藏更改  | `git stash`          | 暂存未提交改动      |
| 恢复更改  | `git stash pop`      | 恢复上次暂存改动     |

---

## 🔒 十一、最佳实践建议

* 每次开始前 `git pull --rebase origin main`
* 每个功能一个分支，命名如 `feat/xxx`、`fix/bugname`
* 提交信息清晰简洁，推荐格式：

  ```
  feat: 添加用户登录功能
  fix: 修复文件读取错误
  docs: 更新说明文档
  ```
* 推送前确保本地运行正常（通过测试）
* 不在 `main` 上直接开发

---

## 🧭 十二、完整日常流程示例（从头到尾）

```bash
# 克隆项目
git clone git@github.com:you/repo.git
cd repo

# 同步并开新分支
git pull --rebase origin main
git checkout -b feat/add-login

# 开发中
vim login.py
git add login.py
git commit -m "feat: add login feature"

# 推送到远程
git push -u origin feat/add-login

# (GitHub 上合并后)
git checkout main
git pull --rebase origin main
git branch -d feat/add-login
```
---