#include<iostream>
#include<tuple>
#include<vector>
#include<climits>
#include <boost/pending/disjoint_sets.hpp>
using namespace std;
int cost(int ignore_edge,int n,vector<int> &used_edge,vector<tuple<int,int,int>> &channels){
  boost::disjoint_sets_with_storage<> uf(n);
  int cc=0;
  int n_components = n;
  // ... and process edges in order of increasing length
  for (int i=0;i<channels.size();i++) {
    // determine components of endpoints
    int c1 = uf.find_set(std::get<0>(channels[i]));
    int c2 = uf.find_set(std::get<1>(channels[i]));
    if (c1 != c2 && i!=ignore_edge) {
      // this edge connects two different components => part of the emst
      uf.link(c1, c2);
      cc += get<2>(channels[i]);
      if(ignore_edge==-1){
        used_edge.push_back(i);
      }
      if (--n_components == 1) break;
    }
  }
  return cc;
}
bool cmp(const tuple<int,int,int>& a,const tuple<int,int,int>& b){
  return get<2>(a) < get<2>(b);
}
void solve(){
  int n,i;
  cin>>n>>i;
  vector<tuple<int,int,int>> channels;
  for(int i=0;i<n-1;i++){
    for(int j=1;j<n-i;j++){
      int c; cin>>c;
      channels.push_back(make_tuple(i,i+j,c));
    }
  }
  sort(channels.begin(),channels.end(),cmp);
  vector<int> used_edge;
  cost(-1,n,used_edge,channels);
  int res=INT_MAX;
  for(int i=0;i<used_edge.size();i++){
    res=min(res,cost(used_edge[i],n,used_edge,channels));
  }
  cout<<res<<endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t; cin>>t;
  while(t--){
    solve();
  }
}
// #include<iostream>
// #include<vector>
// #include<tuple>
// #include<boost/pending/disjoint_sets.hpp>
// #include<climits>
// using namespace std;
// int cost(vector<tuple<int,int,int>> &edges,vector<int> &used_edges,int to_ignore,int n,bool push){
//   boost::disjoint_sets_with_storage<> uf(n);
//   int cost=0;
//   for(int i=0;i<edges.size();i++){
//     int a=uf.find_set(get<0>(edges[i]));
//     int b=uf.find_set(get<1>(edges[i]));
//     if(a!=b && i!=to_ignore){
//       uf.link(a,b);
//       cost+=get<2>(edges[i]);
//       if(push){
//         used_edges.push_back(i);
//       }
//       //只用添加这么多边
//       if(--n==1) break;
//     }
//   }
//   return cost;
// }

// bool mySort(tuple<int,int,int> &a,tuple<int,int,int> &b){
//   return get<2>(a) < get<2>(b);
// }

// void test(){
//   int n,tat; cin>>n>>tat;
//   vector<tuple<int,int,int>> edges;
//   for(int i=1;i<=n-1;i++){
//     for(int j=1;j<=n-i;j++){
//       int cost; cin>>cost;
//       edges.push_back(make_tuple(i-1,j+i-1,cost));
//     }
//   }
//   sort(edges.begin(),edges.end(),mySort);
  
//   vector<int> used_edges;
//   cost(edges,used_edges,-1,n,true);
//   vector<int> tmp;
//   int res=INT_MAX;
//   for(int i=0;i<used_edges.size();i++){
//     res=min(res,cost(edges,tmp,used_edges[i],n,false));
//   }
//   cout<<res<<endl;
// }
// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int cases; cin>>cases;
//   for(;cases;cases--){
//     test();
//   }
// }