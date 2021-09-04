#include<iostream>
#include<vector>
#include<set>
using namespace std;
vector<int> indexInTrip;
multiset<int> tempInTrip;//保持长度永远等于m
void dfs(int index,set<int> &starting_point,vector<vector<int>> &childs,vector<int> &temps,int m,int k){
  indexInTrip.push_back(index);
  tempInTrip.insert(temps[index]);
  int poped_index=-1;
  int poped_temp=-1;
  if(tempInTrip.size()>m){
    poped_index=indexInTrip[indexInTrip.size()-m-1];
    poped_temp=temps[poped_index];
    auto it = tempInTrip.find(poped_temp);
    tempInTrip.erase(it);
  }
  if(tempInTrip.size()==m){
    int diff=(*tempInTrip.rbegin())-(*tempInTrip.begin());
    if(diff<=k){
      starting_point.insert(indexInTrip[indexInTrip.size()-m]);
    }
  }
  for(int child : childs[index]){
    dfs(child,starting_point,childs,temps,m,k);
  }
  indexInTrip.pop_back();
  auto it = tempInTrip.find(temps[index]);
  tempInTrip.erase(it);
  //恢复！
  if(poped_index>=0){
    tempInTrip.insert(poped_temp);
  }
}
void solve(){
  int n,m,k;
  cin>>n>>m>>k;
  vector<int> temps(n);
  for(int i=0;i<n;i++){
    cin>>temps[i];
  }
  vector<vector<int>> childs(n);
  for(int i=0;i<n-1;i++){
    int u,v; cin>>u>>v;
    childs[u].push_back(v);
  }
  //要求升序
  set<int> starting_point;
  dfs(0,starting_point,childs,temps,m,k);
  if(starting_point.size()>0){
    for(auto it=starting_point.begin();it!=starting_point.end();it++){
      cout<<(*it)<<" ";
    }
    cout<<endl;
  }else{
    cout<<"Abort mission"<<endl;
  }
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t; cin>>t;
  while(t--){
    solve();
  }
}
// #include <iostream>
// #include <vector>
// #include <stack>
// #include <set>
// using namespace std;
// void test(){
//   int n,m,k; cin>>n>>m>>k;
//   vector<int> temps(n);
//   for(int i=0;i<n;i++){
//     cin>>temps[i];
//   }
//   vector<vector<int>> childs(n);
//   vector<bool> newRoot(n,true);
//   for(int i=0;i<n-1;i++){
//     int u,v; cin>>u>>v;
//     childs[u].push_back(v);
//     newRoot[v]=false;
//   }
//   set<int> tripSource;//result
//   for(int i=0;i<n;i++){
//     if(newRoot[i]){
//       //DFS深度优先
//       //index and depth
//       stack<pair<int,int>> stk;
//       multiset<int> tempsInTrip;
//       vector<int> indexInTrip;
//       stk.push(make_pair(0,1)); //the root
//       while(!stk.empty()){
//         pair<int,int> top=stk.top();
//         stk.pop();
//         int index=top.first;
//         if(top.second){
//           stk.push(make_pair(index,0)); //回溯！
//           tempsInTrip.insert(temps[index]);
//           indexInTrip.push_back(index);
//           if(indexInTrip.size()>=m){
//             if(indexInTrip.size()>m){
//               int toDelete=indexInTrip[indexInTrip.size()-m-1]; // source's parent
//               tempsInTrip.erase(tempsInTrip.find(temps[toDelete]));
//             }
//             int diff=(*tempsInTrip.rbegin())-(*tempsInTrip.begin());
//             if(diff<=k){
//               tripSource.insert(indexInTrip[indexInTrip.size()-m]);
//             }
//           }
//           if(childs[index].size()!=0){
//             for(int j=0;j<childs[index].size();j++){
//               stk.push(make_pair(childs[index][j],1));
//             }
//           }
//         }
//         //回溯！
//         else{
//           int depth=indexInTrip.size();
//           tempsInTrip.erase(tempsInTrip.find(temps[index]));
//           indexInTrip.pop_back();
//           if(depth>m){
//             int deleted=indexInTrip[depth-m-1];
//             tempsInTrip.insert(temps[deleted]);
//           }
//         }
        
//       }
//     }
//   }
//   if(tripSource.size()>0){
//     for( set<int>::iterator it=tripSource.begin();it!=tripSource.end();it++){
//       cout<<*it<<" ";
//     }
//   }else{
//     cout<<"Abort mission";
//   }
//   cout<<endl;
// }
// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int cases; cin>>cases;
//   for(;cases;cases--){
//     test();
//   }
// }