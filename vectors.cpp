#include<iostream>
#include<vector>
using namespace std;
int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    int length;
    cin>>length;
    vector<int> a(length);
    for(int i=0;i<length;i++){
      cin>>a[i];
    }
    int x;
    cin>>x;
    a.erase(a.begin()+x);
    int y,z;
    cin>>y>>z;
    a.erase(a.begin()+y,a.begin()+z+1);
    int size=a.size();
    // cout<<size<<endl;
    if(size==0){
      cout<<"Empty"<<endl;
      return 0;
    }
    for(int i=0;i<size;i++){
      cout<<a[i];
      if(i==size-1){
        break;
      }
      cout<<" ";
    }
    cout<<endl;
  }
  return 0;
}