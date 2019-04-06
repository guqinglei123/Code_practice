/***************************************************************************************************
 * 问题一：给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个
 * 在字典中出现的单词。
 * 说明：
    拆分时可以重复使用字典中的单词。
    你可以假设字典中没有重复的单词。
    示例 1：

    输入: s = "leetcode", wordDict = ["leet", "code"]
    输出: true
    解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
    示例 2：

    输入: s = "applepenapple", wordDict = ["apple", "pen"]
    输出: true
    解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
        注意你可以重复使用字典中的单词。
    示例 3：

    输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
    输出: false   
    参考链接：http://www.cnblogs.com/easonliu/p/3654123.html
 * 问题二：给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，在字符串中增加空格来构建一个句子，
 * 使得句子中所有的单词都在词典中。返回所有这些可能的句子。
 * 说明：

    分隔时可以重复使用字典中的单词。
    你可以假设字典中没有重复的单词。
    示例 1：

    输入:
    s = "catsanddog"
    wordDict = ["cat", "cats", "and", "sand", "dog"]
    输出:
    [
    "cats and dog",
    "cat sand dog"
    ]
    示例 2：

    输入:
    s = "pineapplepenapple"
    wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
    输出:
    [
    "pine apple pen apple",
    "pineapple pen apple",
    "pine applepen apple"
    ]
    解释: 注意你可以重复使用字典中的单词。
    示例 3：

    输入:
    s = "catsandog"
    wordDict = ["cats", "dog", "sand", "and", "cat"]
    输出:
    []
    参考链接：https://www.cnblogs.com/zl1991/p/6947745.html
 * ********************************************************************************************/
#include <unordered_set>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <climits>
using namespace std;
//采用动态规划的方法
class Solution_dp
{
    vector<string> midres;
    vector<string> res;
    vector<bool> *dp;
  public:
    //问题一：
    bool wordBreak(string s, vector<string> &wordDict)
    {
        int len = s.length();
        vector<bool> v(len + 1, false);
        v[0] = true;   //初始边界条件
        int min_len = INT_MAX, max_len = INT_MIN;
        //获得字典中元素长度的最大值与最小值。
        for (auto &ss : wordDict)
        {
            min_len = min(min_len, (int)ss.length());
            max_len = max(max_len, (int)ss.length());
        }
        for (int pos = 0; pos < len; pos++)
        {
            for (int i = min_len;i <= max_len && (i + pos) <= len; i++)
            {
                vector<string>::iterator iter = find(wordDict.begin(), wordDict.end(), s.substr(pos, i));
                if (iter != wordDict.end())
                    v[pos + i] = true;
            }
        }
        vector<bool>::iterator t;
        for (t = v.begin(); t != v.end(); t++)
            cout << *t << " ";
        cout<<endl;
        return v[len];
    }
    //问题二：
    vector<string> wordBreak2(string s, vector<string> &dict)
    {
        int len = s.length();

        dp = new vector<bool>[len];
        //建立一个相应的表存储i~j之间是否可以在字典中搜索到，注意这一个表的维度并非需要n*n。
        for (int i = 0; i < len; ++i)
        {
            for (int j = i; j < len; ++j)
            {
                vector<string>::iterator iter = find(dict.begin(), dict.end(), s.substr(i, j - i + 1));
                if (iter != dict.end())
                {
                    dp[i].push_back(true); //第二维的下标实际是:单词长度-1
                }
                else
                {
                    dp[i].push_back(false); //数组第二维用vector,size不一定是n,这样比n*n节省空间
                }
            }
        }
        func(s, len - 1);
        return res;
    }

    void func(const string &s, int i)
    {
        if (i >= 0)
        {
            //这部分属于一个递归，从dp[j][n-j]开始从后往前搜索，n是字符串的总长度。
            for (int j = 0; j <= i; ++j)
            {

                if (dp[j][i - j])    //代表从j到i-j的分解可以在字典中搜索到，对j前的字符串进行判断是否可以搜索到。
                { //注意此处的第二个下标是 i-j，不是i,因为数组的第二维长度是不固定的,第二维的下标实际是单词长度-1。

                    midres.push_back(s.substr(j, i - j + 1));
                    func(s, j - 1);
                    midres.pop_back(); //继续考虑for循环的下一个分段处
                }
            }
            return;
        }
        else
        {
            //这部分属于递归基
            string str;
            for (int k = midres.size() - 1; k >= 0; --k)
            {                     //注意遍历的顺序是倒序的
                str += midres[k]; //注意此处是k,不是i
                if (k > 0)
                    str += " ";
            }
            res.push_back(str);
            return;
        }
    }
};
//问题一不采用动态规划方法，使用蛮力算法
class Solution
{
  public:
    bool wordBreakHelper(string s, vector<string> &dict, set<string> &unmatched, int mn, int mx)
    {
        if (s.size() < 1)
            return true;
        int i = mx < s.length() ? mx : s.length();
        //将字符串分为两个部分
        for (; i >= mn; i--)
        {
            string preffixstr = s.substr(0, i);//前串
            vector<string>::iterator iter = find(dict.begin(), dict.end(), preffixstr);
            if (iter != dict.end())
            {
                string suffixstr = s.substr(i);//后串
                if (unmatched.find(suffixstr) != unmatched.end())//查看未匹配成功的串的set中是否存在该串
                    continue;
                else if (wordBreakHelper(suffixstr, dict, unmatched, mn, mx))//将后串继续分解，形成了一个递归
                    return true;
                else
                    unmatched.insert(suffixstr);//查看未匹配成功的串形成一个set
            }
        }
        return false;
    }
    bool wordBreak(string s, vector<string> &dict)
    {
        // Note: The Solution object is instantiated only once.
        if (s.length() < 1)
            return true;
        if (dict.empty())
            return false;
        vector<string>::iterator it = dict.begin();
        int maxlen = (*it).length(), minlen = (*it).length();
        for (it++; it != dict.end(); it++)
            if ((*it).length() > maxlen)
                maxlen = (*it).length();
            else if ((*it).length() < minlen)
                minlen = (*it).length();
        set<string> unmatched;
        return wordBreakHelper(s, dict, unmatched, minlen, maxlen);
    }
};

int main(void)
{
    //问题一的求解
    Solution_dp sol_dp;//动态规划算法
    Solution sol;       //蛮力算法
    vector<string> dict;
    dict.push_back("leet");
    dict.push_back("code");
    cout << (bool)sol_dp.wordBreak("leetcode", dict) << endl;
    cout << sol.wordBreak("leetcode", dict) << endl;
    dict.push_back("cat");
    dict.push_back("cats");
    dict.push_back("and");
    dict.push_back("sand");
    dict.push_back("dog");
    cout << (bool)sol_dp.wordBreak("catsanddog", dict) << endl;
    cout << (bool)sol.wordBreak("catsanddog", dict) << endl;

    //问题二的求解
    vector<string> dict2;
    dict2.push_back("cat");
    dict2.push_back("cats");
    dict2.push_back("and");
    dict2.push_back("sand");
    dict2.push_back("dog");
    vector<string> v;
    vector<string>::iterator t;
    v = sol_dp.wordBreak2("catsanddog", dict2);
    for (t = v.begin(); t != v.end(); t++)
        cout << *t << " ";
    system("pause");
    return 0;
}