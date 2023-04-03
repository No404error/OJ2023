#include<iostream>
using namespace std;

const int maxn=1e4+5;
int a[maxn];

int main(){
    int n,f,s;
    cin>>n;
    f=s=0;
    for(int i=1;i<=n;i++){
        f=s;
        cin>>s;
        a[i]=s-f;
    }
    for(int i=1;i<n;i++)
        cout<<a[i]<<" ";
    cout<<a[n]<<endl;
    return 0;
}