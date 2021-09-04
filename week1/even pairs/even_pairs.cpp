#include<iostream>
#include<vector>
using namespace std;
int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    int num;
    cin>>num;
    vector<int> values(num);
    for(int i=0;i<num;i++){
      cin>>values[i];
    }
    vector<int> sums(num);
    sums[0]=values[0];
    int even=0;
    int odd=0;
    for(int i=0;i<num;i++){
      if(i!=0){
        sums[i]=values[i]+sums[i-1];
      }
      if(sums[i]%2==0){
        even++;
      }else{
        odd++;
      }
    }
    // cout<<even<<" "<<odd<<endl;
    int ans=even*(even-1)/2+odd*(odd-1)/2+even;
    cout<<ans<<endl;
  }
  return 0;
}