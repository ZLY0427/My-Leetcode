/*
 * ============================================================
 *  SubmitGitHub.c  —— 一键提交本文件夹所有更改到 GitHub
 * ============================================================
 *
 * 功能:
 *   1. 自动执行 git add -A，暂存本文件夹的全部更改
 *      （包括新增、修改、删除的文件）
 *   2. 在终端提示你输入提交注释（commit message）
 *   3. 自动执行 git commit 和 git push，推送到 GitHub
 *
 * 使用方法（Windows / MinGW gcc）:
 *   编译:   gcc SubmitGitHub.c -o SubmitGitHub.exe
 *   运行:   SubmitGitHub.exe      （在仓库文件夹内运行）
 *
 * 前提:
 *   - 已安装 git 并配置 PATH
 *   - 本文件夹是一个 git 仓库，且已配置远程仓库 origin
 *     （可用 git remote -v 查看）
 *   - 首次推送时若提示没有上游分支，需要先执行一次:
 *       git push -u origin <分支名>
 *
 * 说明:
 *   - 提交注释先写入临时文件 commit_msg.tmp 再交给 git，
 *     因此注释里可以包含双引号 " 等特殊字符，不会报错。
 *   - Windows 下会根据控制台代码页自动设置提交编码，
 *     保证中文注释不乱码（提交到仓库后统一为 UTF-8）。
 *   - 提交完成后临时文件会自动删除。
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_MSG 1024

static const char *TMP_FILE = "commit_msg.tmp";

#ifdef _WIN32
#define DEVNULL "nul"
#else
#define DEVNULL "/dev/null"
#endif

int main(void)
{
    char msg[MAX_MSG];
    char cmd[2100];
    int rc;

    /* 1. 检查 git 是否可用 */
    rc = system("git --version >" DEVNULL " 2>&1");
    if (rc != 0) {
        printf("[错误] 未检测到 git，请先安装 git 并加入 PATH。\n");
        return 1;
    }

    /* 2. 检查当前文件夹是否是 git 仓库 */
    rc = system("git rev-parse --is-inside-work-tree >" DEVNULL " 2>&1");
    if (rc != 0) {
        printf("[错误] 当前文件夹不是 git 仓库。\n");
        printf("       请进入仓库文件夹运行，或先执行 git init。\n");
        return 1;
    }
    printf("[OK] git 已就绪。\n\n");

    /* 3. 显示当前更改 */
    printf("========== 当前更改 (git status) ==========\n");
    system("git status --short");
    printf("============================================\n\n");

    /* 4. 暂存全部更改（含删除的文件） */
    printf("[1/4] git add -A ...\n");
    rc = system("git add -A");
    if (rc != 0) {
        printf("[错误] git add 失败。\n");
        return 1;
    }

    /* 5. 检查是否有可提交的内容 */
    rc = system("git diff --cached --quiet");
    if (rc == 0) {
        printf("没有需要提交的更改，程序结束。\n");
        return 0;
    }

    /* 6. 在终端输入提交注释 */
    printf("\n[2/4] 请输入提交注释: ");
    if (fgets(msg, sizeof(msg), stdin) == NULL) {
        printf("\n[错误] 读取输入失败。\n");
        return 1;
    }
    msg[strcspn(msg, "\r\n")] = '\0';   /* 去掉结尾的换行 / 回车 */
    if (strlen(msg) == 0) {
        printf("[提示] 未输入提交注释，已取消提交。\n");
        return 1;
    }
    printf("提交注释: %s\n\n", msg);

    /* 7. 将注释写入临时文件，避免命令行转义问题 */
    {
        FILE *f = fopen(TMP_FILE, "wb");
        if (f == NULL) {
            printf("[错误] 无法创建临时文件 %s。\n", TMP_FILE);
            return 1;
        }
        fprintf(f, "%s\n", msg);
        fclose(f);
    }

    /* 8. 提交。Windows 下按控制台代码页指定编码，保证中文注释不乱码 */
    printf("[3/4] git commit ...\n");
#ifdef _WIN32
    {
        UINT cp = GetConsoleOutputCP();
        const char *enc = "UTF-8";
        char encbuf[32];
        switch (cp) {
            case 936:  enc = "GBK";        break;   /* 简体中文 */
            case 950:  enc = "BIG5";       break;   /* 繁体中文 */
            case 932:  enc = "SHIFT-JIS";  break;   /* 日文 */
            case 65001: enc = "UTF-8";     break;   /* UTF-8 */
            case 0:    enc = "UTF-8";      break;
            default:
                snprintf(encbuf, sizeof(encbuf), "cp%u", cp);
                enc = encbuf;
                break;
        }
        snprintf(cmd, sizeof(cmd),
                 "git -c i18n.commitEncoding=%s commit -F %s",
                 enc, TMP_FILE);
    }
#else
    snprintf(cmd, sizeof(cmd),
             "git -c i18n.commitEncoding=UTF-8 commit -F %s", TMP_FILE);
#endif
    rc = system(cmd);
    remove(TMP_FILE);   /* 无论成败都清理临时文件 */
    if (rc != 0) {
        printf("[错误] git commit 失败。\n");
        return 1;
    }

    /* 9. 推送到 GitHub */
    printf("\n[4/4] git push ...\n");
    rc = system("git push");
    if (rc != 0) {
        printf("[错误] git push 失败。\n");
        printf("       提示: 若提示没有上游分支 (no upstream branch)，请先执行:\n");
        printf("             git push -u origin <分支名>\n");
        return 1;
    }

    printf("\n[完成] 所有更改已成功提交并推送到 GitHub！\n");
    return 0;
}
