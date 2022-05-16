#include <stdio.h>
void CreateMyFile(char *szFileName, long long nFileLength)
{
    FILE *fp = fopen(szFileName, "wb+"); // 创建文件
    if (fp == NULL)
        printf("文件打开失败");
    else
    {
        fputc(0, fp); // 在要指定大小文件的开头放\0
        fputc(0, fp); // 在要指定大小文件的开头放\0
        fputc(0, fp); // 在要指定大小文件的开头放\0

        if (nFileLength <= 2147483647)
            fseek(fp, nFileLength - 1, SEEK_SET); // 将文件的指针 移至 指定大小的位置
        else
        {
            while (nFileLength > 0)
            {
                fseek(fp, 2147483647, SEEK_SET);
                nFileLength -= 2147483647;
            }
        }
        fputc(32, fp); // 在要指定大小文件的末尾随便放一个数据
        fclose(fp);
    }
}
int main()
{
    long long cnt = 2; //指定文件大小：2MB
    CreateMyFile("test4.out", cnt * 1024 * 1024);
    return 0;
}
