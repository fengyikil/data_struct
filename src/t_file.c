#include <stdio.h>
#define COUNT 5
typedef struct
{
    int a;
    char name[20];
} tstype;

void twrite(int offset, void *value, int size)
{
    FILE *fp = fopen("D:/workspace/qt/t_data/flash.txt", "r+");
    if (fp == NULL)
    {
        printf("open err.\n");
        return;
    }
    fseek(fp, offset, 0);
    int ret = fwrite(value, size, 1, fp);
    if (ret != 1)
    {
        printf("write err.\n");
    }
    fclose(fp);
}
void tread(int offset, void *value, int size)
{
    FILE *fp = fopen("D:/workspace/qt/t_data/flash.txt", "r+");
    if (fp == NULL)
    {
        printf("open err.\n");
        return;
    }
    fseek(fp, offset, 0);
    int ret = fread(value, size, 1, fp);
    if (ret != 1)
    {
        printf("read err.\n");
    }
    fclose(fp);
}
void test_file()
{
    tstype ts[COUNT] = {{6, "hello"}, {8, "kooj"}, {9, "goof"}, {18, "uu"}, {28, "iop"}};
    tstype tr;
    memset(&tr, 0, sizeof(tstype));

    twrite(0, &ts, sizeof(tstype) * COUNT);

    for (int i = 0; i < COUNT; i++)
    {
        tread(sizeof(tstype) * i, &tr, sizeof(tstype));
        printf("tr.a is %d,ts.name is %s\n", tr.a, tr.name);
    }
}