#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void partition(string s, string *&list)
{
    int len = s.length();
    list = new string[len];

    for (int i = 0; i < len; i++)
        list[i] = s.substr(i, len - i);
}

int find_common_prefix(const string &str1, const string &str2)
{
    int len1 = str1.length();
    int len2 = str2.length();
    int len = len1 < len2 ? len1 : len2;

    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (str1[i] != str2[i])
            break;
        count++;
    }

    return count >= 4 ? count : 0;
}

int main()
{

    string *list = NULL;
    string s = "";
    cin >> s;
    int s_len = s.length();

    partition(s, list);
    sort(list, list + s_len);

    // for(int i=0;i<s_len;i++)
    //     cout<<list[i]<<endl;

    int max_length = 0;
    string max_str = "";

    int temp;
    for (int i = 0; i < s_len - 1; i++)
    {
        temp = find_common_prefix(list[i], list[i + 1]);
        if (temp > max_length)
        {
            max_length = temp;
            max_str = list[i].substr(0, max_length);
        }
    }

    cout << max_str << " " << max_length << endl;

    return 0;
}
