#include<iostream>
#include<climits>
#include<cmath>
#include<vector>
using namespace std;
int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    int n,k;
    cin>>n>>k;
    int values[n];
    for(int i=0;i<n;i++){
      cin>>values[i];
    }
    int d=INT_MAX;
    int left=0;
    int right=0;
    int ans=values[0];
    int m_left=0;
    int m_right=0;
    while(right<n && left<=right){
      if(abs(ans-k)<d){
        d=abs(ans-k);
        m_left=left;
        m_right=right;
        if(d==0){
          break;
        }
      }
      if(ans<k){
        right++;
        ans+=values[right];
      }else{
        left++;
        ans-=values[left-1];
        if(left>right){
          right++;
          ans+=values[left];
        }
      }
    }
    cout<<m_left<<" "<<m_right<<endl;
  }
  return 0;
}

