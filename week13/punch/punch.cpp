#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
struct value{
  int cost;
  int num;
  bool used;
  
  bool operator>(const value v){
    return cost<v.cost||
           cost==v.cost&&num>v.num||
           cost==v.cost&&num==v.num&&!used&&v.used;
  }
};
void test(){
  int n,k;
  cin >> n >> k;
  vector<pair<int,int> > c_v;
  for(int i = 0; i<n; i++){
    int c, v;
    cin >> c >> v;
    c_v.push_back(make_pair(c,v));
  }
  //共有i种酒比较合适
  //共需要j升酒
  vector<vector<value>> dp(n,vector<value>(k+1));
  // dp[0][0]=make_pair(0,0);
  for(int i=0;i<n;i++){
    dp[i][0]={0,0,false};
  }
  for(int j=1;j<=k;j++){
    dp[0][j]={c_v[0].first*ceil((1.0*j)/c_v[0].second),1,true};
  }
  for(int i=1;i<n;i++){
    for(int j=1;j<=k;j++){
      value withi={c_v[i].first,1,true};
      //a new bottle
      if(j>c_v[i].second){
        withi.cost+=(dp[i][j-c_v[i].second]).cost;
        withi.num=(dp[i][j-c_v[i].second]).num;
        if(!(dp[i][j-c_v[i].second].used)){
          withi.num++;
        }
      }
      value withouti=dp[i-1][j];
      withouti.used=false;
      if(withouti>withi){
        dp[i][j]=withouti;
      }else{
        dp[i][j]=withi;
      }
    }
  }
  cout<<dp[n-1][k].cost<<" "<<dp[n-1][k].num<<endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int cases; cin>>cases;
  for(;cases;cases--){
    test();
  }
}