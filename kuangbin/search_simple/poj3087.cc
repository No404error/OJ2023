#include<iostream>
#include<set>
using namespace std;

int n,scale;
string s1,s2,tmp,en;
set<string> s;

string func(){
    string s="";
    int ptr1=0;
    int ptr2=0;
    while((ptr1!=scale)||(ptr2!=scale)){
        if(ptr2!=scale)
            s+=s2[ptr2++];
        if(ptr1!=scale)
            s+=s1[ptr1++];
    }
    s1=s.substr(0,scale);
    s2=s.substr(scale,scale);
    return s;
}

int dfs(){
    for(int times=1;;times++){
        tmp=func();
        if(tmp==en)
            return times;
        else if(s.count(tmp))
            return -1;
        s.insert(tmp);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>scale;
        cin>>s1>>s2>>en;
        s.clear();
        cout<<i<<" "<<dfs()<<endl;
    }
    return 0;
}