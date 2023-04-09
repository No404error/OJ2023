#include<iostream>
#include<algorithm>
using namespace std;

const int maxn=10000+5;

struct node{
    int id,p,d;
    bool operator<(const node& n) const{
        return p<n.p;
    }
} before[maxn],after[maxn];

int order[maxn];

const char dirName[][10]={"L","Turning","R"};

int main(){
    int kase;
    int L,T,n;
    int pos;
    char dir;
    cin>>kase;
    for(int k=1;k<=kase;k++){
        cout<<"Case #"<<k<<":"<<endl;
        cin>>L>>T>>n;
        for(int i=1;i<=n;i++){
            cin>>pos>>dir;
            int d=(dir=='L'?-1:1);
            before[i]=(node){i,pos,d};
            after[i]=(node){0,pos+d*T,d};
        }

        sort(before+1,before+n+1);
        for(int i=1;i<=n;i++)
            order[before[i].id]=i;
        
        sort(after+1,after+n+1);
        for(int i=1;i<n;i++)
            if(after[i].p==after[i+1].p)
                after[i].d=after[i+1].d=0;
        for(int i=1;i<=n;i++){
            int x=order[i];
            if(after[x].p<0||after[x].p>L) printf("Fell off\n");
            else printf("%d %s\n",after[x].p,dirName[after[x].d+1]);
        }
        puts("");
    }
    return 0;
}