# 配置环境

## 1. 安装 MinGW (MSYS2)

1.  下载 MinGW 安装程序：[MSYS2](https://github.com/msys2/msys2-installer/releases/download/2025-12-13/msys2-x86_64-20251213.exe)
2.  运行安装程序，安装路径建议保持默认 (`C:\msys64`)。
3.  安装完成后，勾选 "Run MSYS2 now" 或在开始菜单搜索并打开 **MSYS2 UCRT64** 终端。

## 2. 安装 GCC 工具链

在 **MSYS2 UCRT64** 终端中输入以下命令并回车（遇到询问直接回车确认）：

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-make
```

## 3. 添加环境变量 (Path)

为了在 VS Code 和 PowerShell 中直接使用 `g++`，需要将编译器路径添加到系统环境变量：

1.  按 `Win + S` 搜索 "查看高级系统设置"。
2.  点击 "环境变量" -> 在 "系统变量" 区域找到 `Path` -> 点击 "编辑"。

## 4. 安装 xmake

如果尚未安装 xmake，请在 PowerShell (管理员) 中运行：

```powershell
irm https://xmake.io/psget.text | iex
```

## 5. 安装Git
1. 下载 Git 安装程序：[Git for Windows](https://github.com/git-for-windows/git/releases/download/v2.52.0.windows.1/Git-2.52.0-64-bit.exe)
2. 运行安装程序，保持默认选项，直到安装完成。
   
## 5. 克隆仓库与配置项目

打开 PowerShell 或 VS Code 终端：


### 1. 克隆仓库
```powershell
git clone https://github.com/TeacherLi07/bankmgr
cd bankmgr
```
### 2. 配置 xmake 使用 MinGW 环境
```powershell
xmake f -p mingw --sdk=C:\msys64\ucrt64 -c
```
### 3. 编译并运行测试
```powershell
xmake run test-list

## from wzs2