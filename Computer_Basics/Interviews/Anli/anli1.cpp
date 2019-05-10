/*****************************************************************************************************
参考链接：http://www.cnblogs.com/maybe2030/p/4715035.html
https://blog.csdn.net/chenyukuai6625/article/details/76889375
https://blog.csdn.net/chenyukuai6625/article/details/77165144
 * *******************************************************************************************/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
/** 请完成下面这个函数，实现题目要求的功能 **/
/** 当然，你也可以不按照这个模板来作答，完全按照自己的想法来 ^-^  **/
int maxpathnumber(int node, int edge_size_row, int edge_size_cols, int **edge)
{
    int res = 0;
    int m = 0, n = 0;

    int vect_l[node];
    int vect_r[node];
    for(int i = 0; i < edge_size_row; i++ )
    {
        vect_l[edge[i][0]]++;
        vect_r[edge[i][1]]++;
    }
    for(int i = 0; i < edge_size_row; i++)
    {
        if((vect_r[i]==0)||(vect_l[i]==0))
        {
            vect_r[i]=1;
            vect_l[i]=1;
        }            
        res=res+vect_l[i]*vect_r[i];
    }
    return res;
}

int main()
{
    int res;

    int _node;
    scanf("%d", &_node);

    int _edge_rows = 0;
    int _edge_cols = 0;
    scanf("%d", &_edge_rows);
    scanf("%d", &_edge_cols);

    int **_edge = (int **)malloc(_edge_rows * sizeof(int *));
    int _edge_init_i = 0;
    for (_edge_init_i = 0; _edge_init_i < _edge_rows; ++_edge_init_i)
    {
        _edge[_edge_init_i] = (int *)malloc(_edge_cols * (sizeof(int)));
    }

    int _edge_i, _edge_j;
    for (_edge_i = 0; _edge_i < _edge_rows; _edge_i++)
    {
        for (_edge_j = 0; _edge_j < _edge_cols; _edge_j++)
        {
            int _edge_item;
            scanf("%d", &_edge_item);

            _edge[_edge_i][_edge_j] = _edge_item;
        }
    }

    res = maxpathnumber(_node, _edge_rows, _edge_cols, _edge);
    printf("%d\n", res);

    return 0;
}