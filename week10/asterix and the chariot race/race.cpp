#include <iostream>
#include <vector>
#include <climits>
using namespace std;
struct cost{
  int selected;
  int covered;
  int notCovered;
};
cost dp(vector<vector<int>> &childs,vector<int> &cs,int index){
  //叶子city自己的花费
  if(childs[index].size()==0){
    return{cs[index],0,cs[index]};
  }else{
    cost final={cs[index],0,0};
    int bestDiff=INT_MAX;
    for(int i=0;i<childs[index].size();i++){
      cost children = dp(childs,cs,childs[index][i]);
      final.selected+=children.covered;
      final.covered+=children.notCovered;
      bestDiff=min(bestDiff,children.selected-children.notCovered);
    }
    final.notCovered=final.covered+bestDiff;
    final.covered=min(final.selected,final.covered);
    final.notCovered=min(final.selected,final.notCovered);
    return final;
  }
}
void solve(){
  int n;
  cin>>n;
  vector<vector<int>> childs(n);
  for(int i=0;i<n-1;i++){
    int u,v;
    cin>>u>>v;
    childs[u].push_back(v);
  }
  vector<int> cs(n);
  for(int i=0;i<n;i++){
    cin>>cs[i];
  }
  cost res=dp(childs,cs,0);
  cout<<res.notCovered<<endl;
}
int main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}


// #include<iostream>
// #include<climits>
// #include<vector>
// using namespace std;
// //PS对于叶子节点，selected=notCovered
// struct cost{
//   //选它自己
//   int selected;
//   //它的爸爸被选了
//   int covered;
//   //它爸爸没有被选择，那么最少它的一个孩子要被选择！！
//   int notCovered;
// };
// cost costOfSubtree(int index,vector<vector<int>> &childs,vector<int> &cs){
//   //叶子节点
//   if(childs[index].size()==0){
//     return {cs[index],0,cs[index]};
//   }else{
//     cost final={cs[index],0,0};
//     int bestDiff=INT_MAX;
//     for(int i=0;i<childs[index].size();i++){
//       cost tmp=costOfSubtree(childs[index][i],childs,cs);
//       final.selected+=tmp.covered;
//       final.covered+=tmp.notCovered;
//       bestDiff=min(bestDiff,tmp.selected-tmp.notCovered);
//     }
//     final.notCovered=final.covered+bestDiff;
//     final.covered=min(final.selected,final.covered);
//     final.notCovered=min(final.selected,final.notCovered);
//     return final;
//   }
// }

// void test(){
//   int n; cin>>n;
//   vector<vector<int>> childs(n);
//   for(int i=0;i<n-1;i++){
//     int u,v; cin>>u>>v;
//     childs[u].push_back(v);
//   }
//   vector<int> cs(n);
//   for(int i=0;i<n;i++){
//     cin>>cs[i];
//   }
//   cost total=costOfSubtree(0,childs,cs);
//   cout<<total.notCovered << endl;
// }
// int main(){
//   int cases; cin>>cases;
//   for(;cases;cases--){
//     test();
//   }
// }