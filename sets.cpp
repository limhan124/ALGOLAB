#include<iostream>
#include<set>
using namespace std;
void testcases(){
  int q; cin>>q;
  set<int> iset;
  for(int i=0;i<q;i++){
    int a,b;
    cin>>a>>b;
    if(a==0){
      iset.insert(b);
    }else{
      iset.erase(b);
    }
  }
  if(iset.empty()){
    cout<<"Empty"<<endl;
  }else{
    set<int>::iterator iter;
    for(iter = iset.begin() ; iter != iset.end() ; ++iter){
      cout<<*iter<<" ";
    }
    cout<<endl;
  }
}
int main(){
  int cases; cin>>cases;
  for(;cases;cases--){
    testcases();
  }
}