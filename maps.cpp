#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
void testcases(){
  int q; cin>>q;
  map<string,vector<int>> m;
  for(int i=0;i<q;i++){
    int a;
    string b;
    cin>>a;
    cin>>b;
    if(a==0){
      auto search = m.find(b);
      if (search != m.end()){
        m.erase(search);
      }
    }else{
      m[b].push_back(a);
    }
  }
  string s;
  cin>>s;
  if(m.size()==0){
    cout<<"Empty"<<endl;  
  }else{
    vector<int> ints = m[s];
    if (ints.size() > 0) {
      std::sort(ints.begin(), ints.end());
      for(int i = 0; i < ints.size(); i++) {
        std::cout << ints[i] << " ";
      } 
    } else {
      std::cout << "Empty";
    }
    cout<<endl;
  }
}
int main(){
  int cases; cin>>cases;
  for(;cases;cases--){
    testcases();
  }
  return 0;
}