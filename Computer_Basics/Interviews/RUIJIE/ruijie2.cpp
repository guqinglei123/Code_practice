#include <stdio.h>
#include <string.h>
int pass, fail;
#define ASSERT_EQ(x, y) (y == x) ? pass++ : fail++;
//计算英文单词数量
//只是统计了单词的数量，不保证单词的正确性,如果需要则需要匹配模板
//符号不单独计算

int count_word(char *buf)
{
    int res = 0;

    if ((buf == NULL) || (buf == " ") || (buf == "/0"))
        return 0;
    for (int i = 0; i < strlen(buf); i++)
    {
        if (((buf[i] != ' ') && (buf[i + 1] == ' ')) || ((buf[i] != ' ') && (buf[i + 1] == '\0')))
        {
            int m = i;
            while ((m > 0) && (buf[m] != ' ')) //针对于测试情况2的处理
            {
                if ((buf[m] > 'A') && (buf[m] < 'z'))
                {
                    res++;
                    break;
                }
                else
                    m--;
            }
        }
    }
    return res;
}

//单元测试案例
void ut(void)
{
    static int assert_fail, assert_pass;
    pass = 0;
    fail = 0;
    //正确性检查
    ASSERT_EQ(count_word("hello word!"), 2);
    ASSERT_EQ(count_word("hello !!』!! word!"), 2);
    ASSERT_EQ(count_word("hello word!!!! word!"), 3);
    // //边界检查
    ASSERT_EQ(count_word(""), 0);
    ASSERT_EQ(count_word("/0"), 0);
    ASSERT_EQ(count_word(" "), 0);
    ASSERT_EQ(count_word(NULL), 0);
    ASSERT_EQ(count_word("!!!!"), 0);
    assert_pass = pass;
    assert_fail = fail;
    printf("Test Report :\n Fail:%d\n Pass :%d\n", assert_fail, assert_pass);
}

int main(int argc, char const *argv[])
{
    /* code */
      ut();
    return 0;
}
