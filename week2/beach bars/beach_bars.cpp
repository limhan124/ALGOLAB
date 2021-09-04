#include<iostream>
#include<climits>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    int n;
    cin>>n;
    std::vector<int> c(n);
    for(int i=0;i<n;i++){
      cin>>c[i];
    }
    sort(c.begin(),c.end());
    
    // std::vector<std::tuple<int, int, int>> potential_locations;
    std::vector<int> ans;
    //position.reachable parasols.distance
    int limit=100;
    int left=0;
    int right=0;
    int parasols=0;
    int distance=INT_MAX;
    while(left<n){
      if(c[right]-c[left]<=2*limit){
        int tmp_num=right-left+1;
        if(tmp_num>=parasols){
          if(tmp_num>parasols){
            parasols=tmp_num;
            distance=INT_MAX;
            ans.clear();
          }
        // }else if(tmp_num==parasols){
          int tmp_dis=((c[right]-c[left])%2==0)?(c[right]-c[left])/2:(c[right]-c[left]+1)/2;
          if(tmp_dis<=distance){
            if(tmp_dis<distance){
              distance=tmp_dis;
              ans.clear();
            }
            if((c[right]-c[left])%2==0){
              ans.push_back(c[left]+(c[right]-c[left])/2);
            }else{
              ans.push_back(c[left]+(c[right]-c[left]-1)/2);
              ans.push_back(c[left]+(c[right]-c[left]+1)/2);
            }
          }
        }
      }
      
      if(c[right]-c[left]<=2*limit && right<n-1){
        right++;
      }else{
        left++;
      }
    }
    
    cout<<parasols<<" "<<distance<<endl;
    for(int i=0;i<(int)ans.size();i++){
      cout<<ans[i]<<" ";
    }
    cout<<endl;
  }
  return 0;
}