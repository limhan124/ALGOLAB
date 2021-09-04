#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct island{
  int total_demand;
  int way_id;
  int position;
};
bool cmp(const island&a,const island&b){
  return a.total_demand<b.total_demand;
}
void solve(){
  int n,k,b;
  cin>>n>>k>>b;
  vector<int> solders(n);
  for(int i=0;i<n;i++){
    cin>>solders[i];
  }
  vector<vector<island>> ways(b);
  vector<island> all_islands;
  int max_len=0;
  for(int i=0;i<b;i++){
    int c; cin>>c;
    int total_d=0;
    ways[i].push_back({total_d,i,-1});
    for(int j=0;j<c;j++){
      int p; cin>>p;
      total_d+=solders[p];
      ways[i].push_back({total_d,i,j});
      all_islands.push_back({total_d,i,j});
    }
    if(total_d>=k){
      int l=0; int u=0;
      while(u<=c){
        int demand=ways[i][u].total_demand-ways[i][l].total_demand;
        if(demand==k){
          max_len=max(max_len,u-l);
          u++;
        }else if(demand>k){
          l++;
        }else{
          u++;
        }
      }
    }
  }
  sort(all_islands.begin(),all_islands.end(),cmp);
  //现在要考虑两个水路的情况了
  int goal=solders[0]+k;
  int l=0;
  int u=all_islands.size()-1;
  while(l<u){
    int demand=all_islands[l].total_demand+all_islands[u].total_demand;
    if(demand==goal){
      if(all_islands[l].way_id != all_islands[u].way_id){
        max_len=max(max_len,all_islands[l].position+all_islands[u].position+1);
      }
      if(all_islands[l+1].total_demand==all_islands[l].total_demand){
        l++;
      }else if(all_islands[u-1].total_demand==all_islands[u].total_demand){
        u--;
      }else{
        l++;
      }
    }else if(demand>goal){
      u--;
    }else{
      l++;
    }
  }
  cout<<max_len<<endl;
}
int main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}