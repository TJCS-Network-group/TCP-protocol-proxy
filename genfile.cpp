#include <stdio.h>
void CreateMyFile(char *szFileName, long long nFileLength)
{
    FILE *fp = fopen(szFileName, "wb+"); // �����ļ�
    if (fp == NULL)
        printf("�ļ���ʧ��");
    else
    {
        fputc(0, fp); // ��Ҫָ����С�ļ��Ŀ�ͷ��\0
        fputc(0, fp); // ��Ҫָ����С�ļ��Ŀ�ͷ��\0
        fputc(0, fp); // ��Ҫָ����С�ļ��Ŀ�ͷ��\0

        if (nFileLength <= 2147483647)
            fseek(fp, nFileLength - 1, SEEK_SET); // ���ļ���ָ�� ���� ָ����С��λ��
        else
        {
            while (nFileLength > 0)
            {
                fseek(fp, 2147483647, SEEK_SET);
                nFileLength -= 2147483647;
            }
        }
        fputc(32, fp); // ��Ҫָ����С�ļ���ĩβ����һ������
        fclose(fp);
    }
}
int main()
{
    long long cnt = 2; //ָ���ļ���С��2MB
    CreateMyFile("test4.out", cnt * 1024 * 1024);
    return 0;
}
