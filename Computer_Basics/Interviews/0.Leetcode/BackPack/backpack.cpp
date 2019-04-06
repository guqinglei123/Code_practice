/*****************************************************************************************************************************
 * 背包问题：
 * 问题一：（01背包）有n 个物品（每一个物品只有一件），它们有各自的重量和价值，现有给定容量的背包，如何让背包里装入的物品具有最大的价值总和？
 * 转移函数：dp[i][j] = max( dp[i-1][j] , dp[i-1][ j - weight[i] ] + value[i] )
 * 说明：
    eg：number＝4，capacity＝8

    i             1   2   3   4
    w(体积)       2    3   4   5
    v(价值)       3    4   5   6
 * 扩展：
 *  完全背包：每个物品有无穷多件的话。转移函数：dp[i][j] = max ( dp[i-1][j - k*weight[i]] +k*value[i] ) 0<=k*weight[i]<=m.
 *  多重背包：每个物品给出确定的件数，求可以得到的最大价值.dp[i][j] = max ( dp[i-1][j - k*weight[i]] +k*value[i] )     0<=k<=num[i]
 *  混合三种背包：
 *  二维背包：对于每件物品有两种不同费用，比如有n种物品，每种物品都有体积vi，重量wi，价值ti,限制体积最多为V，重量最多为W
 *          设f[i][x][y]表示前i件物品，付出两种代价分别为x和y时可以获得的最大价值。f[i][x][y]=max{f[i-1][x][y],f[i-1][x-v[i]][y-w[i]]+t[i]} 
 *  分组背包：有N件物品和一个容量为V的背包。第i件物品的费用是c[i]，价值是w[i]。这些物品被划分为若干组，每组中的物品互相冲突，最多选一件
 *  有依赖的背包：
 *  泛化物品：
 *  背包问题问法的变化：
 * 参考链接：https://blog.csdn.net/stack_queue/article/details/53544109
 *          https://www.cnblogs.com/Christal-R/p/Dynamic_programming.html
 *          https://blog.csdn.net/jushang0235/article/details/78841915
 *          https://blog.csdn.net/tinyguyyy/article/details/51203935
 *          https://blog.csdn.net/hemk340200600/article/details/64210235
 * 问题二：(部分背包)在选择物品i装入背包的时候，可以选择物品i的一部分装入背包，而不一定全部装入背包，这是与0-1背包问题的差别。
 * 形式化描述语言：给定背包容量c(c>0)，和物品i的重量wi(wi>0)、价值vi(vi>0)。
 * 说明：
 * 给定背包容量50Kg，物品信息：物品1，重量10Kg，价值60元；物品2，重量20Kg，价值100元；物品3，重量30Kg，价值120元。
 * 参考链接：https://blog.csdn.net/zangker/article/details/50223673
 *         https://blog.csdn.net/u013553804/article/details/51213909 
 * 
 * ************************************************************************************************************************/
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAX_NUM 1000

class BackPack_dp
{
  private:
    const int _number;
    int _capacity;

  public:
    int **V;
    int *w;
    int *v;
    int *item;
    int *B;
    //注意：1.由于number，capacity的大小不确定，这里使用的动态数组
    //2.数组和指针的不同，申明数组确定数组的内存大小，而指针则没有。同时注意二维数组名和二维指针不是相同概念。ziseof函数的中两个的区别。
    BackPack_dp(int number, int capacity, int *goods) : _number(number),
                                                        _capacity(capacity)
    {

        w = new int[_number + 1];
        v = new int[_number + 1];
        item = new int[_number + 1];
        B = new int[_capacity + 1];
        V = new int *[_number + 1];

        w[0] = 0;
        v[0] = 0;
        for (int i = 1; i <= _number; ++i)
        {
            w[i] = *(goods + i - 1);
            v[i] = *(goods + _number + i - 1);
        }
        for (int i = 0; i < _number + 1; ++i)
            V[i] = new int[_capacity + 1];
    }

    ~BackPack_dp()
    {
        for (int i = 0; i < _number; i++)
            delete[] V[i];
        delete[] V;
        delete[] B;
        delete[] item;
        delete[] w;
        delete[] v;
    }

    void ZeroOnePack() //动态规划,建立动态规划表
    {
        int i, j;
        //填表

        for (i = 1; i <= _number; i++)
        {
            for (j = 1; j <= _capacity; j++)
            {
                if (j < w[i]) //包装不进
                {
                    V[i][j] = V[i - 1][j];
                }
                else //能装
                {
                    if (V[i - 1][j] > V[i - 1][j - w[i]] + v[i]) //不装价值大
                    {
                        V[i][j] = V[i - 1][j];
                    }
                    else //前i-1个物品的最优解与第i个物品的价值之和更大
                    {
                        V[i][j] = V[i - 1][j - w[i]] + v[i];
                    }
                }
                cout << V[i][j];
            }
            cout << endl;
        }

        // FindMaxBetter();
    }

    void ZeroOnePack_Better() //优化空间后的动态规划，将二维表变为一维，但是没有办法找到最优解的构成
    {

        int i, j;
        for (i = 1; i <= _number; i++)
        {
            for (j = _capacity; j >= 0; j--) //采用逆序
            {
                if (B[j] <= B[j - w[i]] + v[i] && j - w[i] >= 0) //二维变一维
                {
                    B[j] = B[j - w[i]] + v[i];
                }
                cout << B[j] << ' ';
            }
        }
        cout << endl;
    }

    void FindWhat(int i, int j) //寻找解的组成方式
    {

        if (i > 0)
        {
            if (V[i][j] == V[i - 1][j]) //相等说明没装
            {
                item[i] = 0; //全局变量，标记未被选中
                FindWhat(i - 1, j);
            }
            else if (j - w[i] >= 0 && V[i][j] == V[i - 1][j - w[i]] + v[i])
            {
                item[i] = 1;               //标记已被选中
                FindWhat(i - 1, j - w[i]); //回到装包之前的位置
                cout << i << endl;
            }
        }
    }
};

class BackPack_Greed
{
  public:
    struct Goods //info of goods定义物品信息结构体
    {
        int weight;       // the weight of goods重量
        int value;        // the value of goods价值
        double ValPerWei; // value per weight权重
        double load;      //物品装入背包的部分的系数（例如上图中物品全部装入则load为1，装入10/20则load为0.5）
        int index;        //物品编号
    };
    int goods_num;
    int bagvol;
    double total_value;
    double total_weight;
    Goods *G;

    BackPack_Greed(int number, int capacity, int *goods) : goods_num(number), bagvol(capacity)
    {
        G = new Goods[goods_num];
        total_value = 0;
        total_weight = 0;
        for (int i = 0; i < goods_num; i++)
        {
            G[i].index = i;
            G[i].weight = *(goods + i - 1);
            G[i].value = *(goods + goods_num + i - 1);         //输入重量价值
            G[i].ValPerWei = (double)G[i].value / G[i].weight; //计算权重
            G[i].load = 0;                                     //load置0
        }
    }
    ~BackPack_Greed()
    {
        delete[] G;
    }

    static int cmp(Goods const &a, Goods const &b) //定义sort函数的比较函数，注意该函数为staic类型以及传入变量类型应该为const
    {
        if (a.ValPerWei < b.ValPerWei)
            return 0;
        else
            return 1;
    }
    //这里考虑的是选取单位重量价值最大的物品，但是也存在不适合的情况。比如
    // W=30
    // 物品：A B C
    // 重量：28 20 10
    // 价值：28 20 10
    // 根据策略，三种物品单位重量价值一样，程序无法依据现有策略作出判断，如果选择A，则答案错误。
    void Greedy() //贪心算法
    {
        // sort(G, G + goods_num*sizeof(Goods), cmp);//sort by ValPerWei
        sort(G, G + goods_num, cmp); //为什么这里的goods_num,不用×sizeof(Goods)；
        for (int i = 0; i < goods_num; i++)
        {
            cout << G[i].index << endl;
        }

        for (int i = 0; i < goods_num; i++)
        {
            if (bagvol > G[i].weight) //如果背包足够装下整个物品
            {
                bagvol -= G[i].weight;
                G[i].load = 1;
            }
            else if (bagvol > 0)
            {                                             //如果背包不足以装下整个物品
                G[i].load = (double)bagvol / G[i].weight; //计算物品装入背包的部分
                bagvol = 0;                               //背包容量置0
                return;                                   //程序结束，返回
            }
        }
    }

    void Load_Good()
    {

        for (int i = 0; i < goods_num; i++) //output the info of goods
        {
            if (G[i].load == 0.0)
                break; //如果检测到物品未被装入背包，则推出循环

            total_value += (G[i].value * G[i].load);   //装入背包的物品总价值
            total_weight += (G[i].weight * G[i].load); //装入背包的物品总重量
            cout << "物品：" << G[i].index << "  "
                 << "体重：" << G[i].weight << "  "
                 << "价值：" << G[i].value << "  "
                 << "单价：" << G[i].ValPerWei << "  装入部分为：" << G[i].load << endl; //输出装入背包的物品信息
        }
        cout << "背包容量：" << bagvol << endl;           //输出背包容量
        cout << "装入物品重量：" << total_weight << endl; //输出装入物品的总重量
        cout << "装入物品价值：" << total_value << endl;  //输出装入物品的总价值
    }
};

class cin_data
{
    //
    // cout << "Please input the volum of bag:" << endl;
    // cin >> bagvol;
    // cout << "Please input the number of goods:" << endl;
    // cin >> goods_num;

    // cout << "Please inuput the weight and value of goods:" << endl;
};

int main(void)
{
    //数据例子
    const int number = 4;
    int capacity = 8;
    int goods[2][number] = {{2, 3, 4, 5}, {3, 4, 6, 5}}; //使用结构体会比使用使用数组分别一些
    //问题一，蛮力算法
    //问题一，动态规划算法
    BackPack_dp pack(number, capacity, goods[0]); //注意二维数组的大小
    cout << "二维动态规划表为：" << endl;
    pack.ZeroOnePack();
    cout << endl
         << "二维动态规划表优化后的一维规划表为：" << endl;
    pack.ZeroOnePack_Better();
    cout << endl
         << "选中的物品编号为：" << endl;
    pack.FindWhat(number, capacity); //为什么一定是最后一个中得到最优秀解呢？

    //问题二，贪心算法
    BackPack_Greed pack2(number, capacity, goods[0]);
    cout << endl
         << "排序之后的物品编号：" << endl;
    pack2.Greedy();
    cout << endl
         << "load之后的物品信息:" << endl;
    pack2.Load_Good();
    return 0;
}