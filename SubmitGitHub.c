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
 * 编码处理（重要）:
 *   - 终端输入的注释会先按控制台代码页（如 GBK）转换成 UTF-8，
 *     再写入提交，因此提交信息在 GitHub 上能正确显示中文。
 *   - git 自身的输出（如 [main xxx] 提交摘要）会按控制台代码页
 *     输出，保证在 GBK 终端里也显示正常、不乱码。
 *   - git status 里中文文件名显示为 \344\270\255 这类八进制转义，
 *     这是 git 的默认行为（core.quotepath），属于正常现象。
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
 *   - 没有可提交的更改时，程序会提示并直接退出，不会要求输入。
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

/* 取得控制台输出代码页对应的 git 编码名（用于 git 自身输出） */
static void console_encoding_name(char *buf, size_t size)
{
#ifdef _WIN32
    UINT cp = GetConsoleOutputCP();
    switch (cp) {
        case 936:   snprintf(buf, size, "GBK");       break;  /* 简体中文 */
        case 950:   snprintf(buf, size, "BIG5");      break;  /* 繁体中文 */
        case 932:   snprintf(buf, size, "SHIFT-JIS"); break;  /* 日文 */
        case 65001: snprintf(buf, size, "UTF-8");     break;
        case 0:     snprintf(buf, size, "UTF-8");     break;
        default:    snprintf(buf, size, "cp%u", cp);  break;
    }
#else
    snprintf(buf, size, "UTF-8");
#endif
}

/* 把控制台输入的字节从代码页 cp 转换为 UTF-8；失败返回 -1 */
#ifdef _WIN32
static int console_to_utf8(const char *in, char *out, size_t out_size, UINT cp)
{
    int wlen = MultiByteToWideChar(cp, 0, in, -1, NULL, 0);
    if (wlen <= 0)
        return -1;
    wchar_t *wbuf = (wchar_t *)malloc((size_t)wlen * sizeof(wchar_t));
    if (wbuf == NULL)
        return -1;
    MultiByteToWideChar(cp, 0, in, -1, wbuf, wlen);
    int ulen = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, NULL, 0, NULL, NULL);
    if (ulen <= 0 || (size_t)ulen > out_size) {
        free(wbuf);
        return -1;
    }
    WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, out, ulen, NULL, NULL);
    free(wbuf);
    return 0;
}
#endif

int main(void)
{
    char msg[MAX_MSG];
    char utf8_msg[MAX_MSG * 4];     /* 转成 UTF-8 后可能更长 */
    char encname[32];
    char cmd[2200];
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

    /* 5. 检查是否有可提交的内容（无更改则直接退出，不要求输入） */
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

    /* 7. 把注释从控制台代码页转换为 UTF-8，保证 GitHub 上中文不乱码 */
#ifdef _WIN32
    if (console_to_utf8(msg, utf8_msg, sizeof(utf8_msg), GetConsoleCP()) != 0) {
        printf("[警告] 编码转换失败，将按原始字节提交。\n");
        strncpy(utf8_msg, msg, sizeof(utf8_msg) - 1);
        utf8_msg[sizeof(utf8_msg) - 1] = '\0';
    }
#else
    strncpy(utf8_msg, msg, sizeof(utf8_msg) - 1);
    utf8_msg[sizeof(utf8_msg) - 1] = '\0';
#endif
    printf("提交注释: %s\n\n", msg);   /* 回显用原始输入，控制台显示正常 */

    /* 8. 将 UTF-8 注释写入临时文件，避免命令行转义问题 */
    {
        FILE *f = fopen(TMP_FILE, "wb");
        if (f == NULL) {
            printf("[错误] 无法创建临时文件 %s。\n", TMP_FILE);
            return 1;
        }
        fprintf(f, "%s\n", utf8_msg);
        fclose(f);
    }

    /* 9. 提交：信息以 UTF-8 存储（GitHub 显示正确）；
            git 自身输出按控制台代码页显示（终端不乱码） */
    console_encoding_name(encname, sizeof(encname));
    printf("[3/4] git commit ...\n");
    snprintf(cmd, sizeof(cmd),
             "git -c i18n.commitEncoding=UTF-8 -c i18n.logOutputEncoding=%s commit -F %s",
             encname, TMP_FILE);
    rc = system(cmd);
    remove(TMP_FILE);   /* 无论成败都清理临时文件 */
    if (rc != 0) {
        printf("[错误] git commit 失败。\n");
        return 1;
    }

    /* 10. 推送到 GitHub */
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
