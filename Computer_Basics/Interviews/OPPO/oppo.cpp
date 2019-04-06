//题目1


using namespace std;

int comp(const void * a,const void * b){
    return *(int *)b-*(int *)a;
}

int main(){
    map<int,int> m;
    int number[100];
    int temp;
    int n=0;
    int k;
    char c;

    while(true){
        cin>>temp;
        number[n++]=temp;
        c=cin.get();
        if(c!=',')
            break;
    }
    cin>>k;

    for(int i=0;i<n;i++ )
         m[number[i]]=i;
    
    qsort(number,n,sizeof(int),comp);

    cout<<m[number[k-1]]+1<<endl;
    // for(int i=0;i<n;i++)
    //     cout<<number[i]<<" ";

    return 0;
}



//题目2