#include<iostream>
using namespace std;

const int maxn=10e4+5;
int a[maxn];
int n,m;
int main(){
    cin>>n;
    int tmp;
    for(int i=1;i<=n;i++){
        cin>>tmp;
        a[i]=tmp+a[i-1];
    }
    cin>>m;
    int a1,a2;
    for(int i=1;i<=m;i++){
        cin>>a1>>a2;
        cout<<a[a2]-a[a1-1]<<endl;
    }
    return 0;
}