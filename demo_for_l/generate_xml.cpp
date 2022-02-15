#include <stdlib.h>
#include <stdio.h>
int main()
{

    FILE *p = fopen("a.txt", "w");
    if (p == NULL)
        printf("文件打开失败\n");
    else
    {
        char * root_name;
        fputs("data\n", p);
        fputs("cv1\n", p);
        fputs("cv2\n", p);
        fputs("data1\n", p);
        fputs("demo.xml", p);
        fclose(p);
    }

    system("python generate_xml.py");
    return 0;
}