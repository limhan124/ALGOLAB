#include<iostream>
#include <iomanip>
using namespace std;
int main(){
  int num;
  cin>>num;
  for(;num;--num){
    int first;
    cin>>first;
    long second;
    cin>>second;
    std::string third;
    cin>>third;
    double fourth;
    cin>>fourth;
    cout<<first<<" "<<second<<" "<<third<<" "<<fixed<<setprecision(2)<<fourth<<" "<<endl;
  }
  return 0;
}