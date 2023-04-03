#include<iostream>
#include<cstring>
using namespace std;

const int maxn=5e4+5;
int a[maxn];
int s[10],e[10];
int n;

int main(){
    int tmp;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>tmp;
        a[i]=(a[i-1]+tmp)%7;
    }
    int res=0;
    for(int i=n;i>=1;i--)
        s[a[i]]=i;
    for(int i=1;i<=n;i++)
        e[a[i]]=i;
    s[0]=0;
    for(int i=0;i<=6;i++)
        res=max(res,e[i]-s[i]);
    cout<<res<<endl;
    return 0;
}