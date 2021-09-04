#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
// typedef pair<int, int> canal;
//position表示现在所处的地方，moves表示剩下可以走的步数了
long dp(vector<vector<long>> &scores,vector<vector<pair<int, int>>> &canals,int position,int moves){
  if(scores[position][moves]!=-1){
    return scores[position][moves];
  }else{
    long max_score=numeric_limits<long>::min();
    for(int i=0;i<canals[position].size();i++){
      if(canals[position][i].second!=-1){
        max_score=max(max_score,dp(scores,canals,canals[position][i].first,moves-1)+canals[position][i].second);
      }else{
        max_score=max(max_score,dp(scores,canals,0,moves));
      }
    }
    scores[position][moves]=max_score;
  }
  return scores[position][moves];
}
void test(){
  int n,m;
  long x;
  int k;
  cin>>n>>m>>x>>k;
  vector<vector<pair<int, int>>> canals(n,vector<pair<int, int>>());
  for(int i=0;i<m;i++){
    int u,v,p; cin>>u>>v>>p;
    canals[u].push_back(make_pair(v,p));
  }
  for(int i=0;i<n;i++){
    if(canals[i].size()==0){
      canals[i].push_back(make_pair(0,-1));
    }
  }
  //scores[i][j]在i这个点走j步能够得到的最大分数
  vector<vector<long>> scores(n,vector<long>(k+1,-1));
  for(int i=0;i<n;i++){
    //走0步当然只能得0了
    scores[i][0]=0;
  }
  bool possible=false;
  for(int i=1;i<=k;i++){
    if(dp(scores,canals,0,i)>=x){
      possible=true;
      cout<<i<<endl;
      break;
    }
  }
  if(!possible){
    cout<<"Impossible"<<endl;
  }
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int cases; cin>>cases;
  for(;cases;cases--){
    test();
  }
  return 0;
}