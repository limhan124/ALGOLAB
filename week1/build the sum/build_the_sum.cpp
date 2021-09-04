#include<iostream>
using namespace std;
int main(){
  int ans_num;
  cin>>ans_num;
  for(;ans_num;ans_num--){
    int num;
    cin>>num;
    int ans=0;
    for(;num;num--){
      int n=0;
      cin>>n;
      ans+=n;
    }
    cout<<ans<<endl;
    ans=0;
  }
  return 0;
}