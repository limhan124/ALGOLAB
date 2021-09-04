#include<iostream>
#include<string>
using namespace std;
int main(){
  int num;
  cin>>num;
  for(;num;num--){
    string a,b;
    cin>>a>>b;
    int al=a.length();
    int bl=b.length();
    cout<<al<<" "<<bl<<endl;
    
    string cor=a+b;
    cout<<cor<<endl;
    
    string c,d;
    c.append(b.substr(bl-1,1));
    d.append(a.substr(al-1,1));
    for( int i = 1; i <al; i++ )
    {
        c.append(a.substr(al-i-1,1));
    }
    for( int i = 1; i <bl; i++ )
    {
        d.append(b.substr(bl-i-1,1));
    }
    cout<<c<<" "<<d<<endl;
  }
  return 0;
}