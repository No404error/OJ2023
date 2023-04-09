#include<cstdio>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);i++)

const int maxn=12;
char pos[maxn][maxn][maxn];
char view[6][maxn][maxn];
int n;

char getChar(){
    char ch;
    while(true){
        ch=getchar();
        if((ch>='A'&&ch<='Z')||ch=='.') return ch;
    }
}

//mapping view to pos,add len of view
void getPos(int k,int i,int j,int len,int& x,int& y,int& z){
    //前
    if(k==0) x=len,y=j,z=i;
    //左
    else if(k==1) x=n-j-1,y=len,z=i;
    //后
    else if(k==2) x=n-len-1,y=n-j-1,z=i;
    //右
    else if(k==3) x=j,y=n-len-1,z=i;
    //顶
    else if(k==4) x=n-i-1,y=j,z=len;
    //底
    else if(k==5) x=i,y=j,z=n-len-1;
}

int main(){
    while(scanf("%d",&n)==1&&n){
        rep(i,n) rep(k,6) rep(j,n) view[k][i][j]=getChar();
        //set all pos ok
        rep(i,n) rep(j,n) rep(k,n) pos[i][j][k]='#';

        //set view null to pos null
        rep(k,6) rep(i,n) rep(j,n)
            if(view[k][i][j]=='.')
                rep(l,n){
                    int x,y,z;
                    getPos(k,i,j,l,x,y,z);
                    pos[x][y][z]='.';
                }
        
        //set view's color not allow to null,until all ok
        bool ok=true;
        while(ok){
            ok=false;
            rep(k,6) rep(i,n) rep(j,n)
                if(view[k][i][j]!='.'){
                    rep(l,n){
                        int x,y,z;
                        getPos(k,i,j,l,x,y,z);
                        if(pos[x][y][z]=='.') continue;
                        else if(pos[x][y][z]=='#'){
                            pos[x][y][z]=view[k][i][j];
                            break;
                        }
                        else if(pos[x][y][z]==view[k][i][j]) break;
                        ok=true;
                        pos[x][y][z]='.';
                    }
                }
        } 
        int ans=0;
        rep(i,n) rep(j,n) rep(k,n) if(pos[i][j][k]!='.') ans++;
        printf("Maximum weight: %d gram(s)\n",ans);
    }
    return 0;
}