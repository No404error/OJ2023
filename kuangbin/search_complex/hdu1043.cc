#include<iostream>
#include<queue>
#include<unordered_map>
#include<string>
using namespace std;

unordered_map<string,string> ans;
//上下左右
int op[]={-3,3,-1,1};
//char old_mov[]="udlr";
char mov[]="durl";

void bfs(string s){
    ans.clear();
    string tmp;

    queue<string> q;
    q.push(s);
    ans[s]="";

    while(!q.empty()){
        s=q.front();
        q.pop();
        int pos=s.find('x');
        for(int i=0;i<4;i++){
            int nPos=pos+op[i];
            if(nPos>=0&&nPos<9&&(i<2||(i==2&&pos%3)||(i==3&&nPos%3))){
                tmp=s;
                //swap two chars
                char c=tmp[pos];
                tmp[pos]=tmp[nPos];
                tmp[nPos]=c;

                if(!ans.count(tmp)){
                    ans[tmp]=mov[i]+ans[s];
                    q.push(tmp);
                }
            }
        }
    }
    
}

int main(){
    bfs("12345678x");

    string s(9,' '),out;
    char tmp;
    while(cin>>s[0]){
        for(int i=1;i<9;i++)
            cin>>s[i];
        if(ans.count(s))
            out=ans[s];
        else
            out="unsolvable";
        cout<<out<<endl;
    }
    return 0;
}