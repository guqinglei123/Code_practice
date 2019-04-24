#include <vector>
#include <algorithm>
using namespace std;

int minContainer(int numPieces, int capacityContainer, int carats[])
{
    int legth = numPieces;
    vector<int> carats_vec;
    for(int i = 0; i < legth;i++)
    {
        carats_vec.push_back(carats[i]);
    }
    sort(carats_vec.begin(),carats_vec.end());
    int sum = 0;
    int res = 0;
    int i =0;
    
    // while(i < legth)
    // {
    //     sum = sum + carats_vec[i];
    //     if(sum > capacityContainer)
    //     {
    //         sum = carats_vec[i];
    //         res++;
    //     }
    //     i++;
    // }
    // res++;
    return res;    
}

main(int argc, char const *argv[])
{
    /* code */
    int carats[] = {14,18,11,14,12,13};
    int carats2[] = {15,30,5,2,10,10};
    minContainer(6,40,carats2);
    return 0;
}
