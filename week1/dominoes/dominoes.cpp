#include<iostream>
#include<vector>
using namespace std;
int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    int num;
    cin>>num;
    vector<int> heights(num);
    for(int i=0;i<num;i++){
      cin>>heights[i];
    }
    int max=heights[0];
    
    int i=0;
    for(;i<num && i<max;i++){
      if(heights[i]+i>max){
        max=heights[i]+i;
      }
    }
    cout<<i<<endl;
  }
  return 0;
}