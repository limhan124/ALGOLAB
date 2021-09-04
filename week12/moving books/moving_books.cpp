#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
void solve(){
  int n,m;
  cin>>n>>m;
  vector<int> s(n);
  vector<int> w(m);
  multiset<int,greater<int>> ws;
  int max_s=0;
  for(int i=0;i<n;i++){
    cin>>s[i];
    if(s[i]>max_s){
      max_s=s[i];
    }
  }
  int max_w=0;
  for(int i=0;i<m;i++){
    cin>>w[i];
    ws.insert(w[i]);
    if(w[i]>max_w){
      max_w=w[i];
    }
  }
  if(max_s<max_w){
    cout<<"impossible"<<endl;
    return;
  }
  sort(s.begin(),s.end(),greater<int>());
  int r=0;
  while(!ws.empty()){
    r++;
    for(int i=0;i<n;i++){
      auto p=ws.lower_bound(s[i]);
      if(p!=ws.end()){
        ws.erase(p);
      }else{
        break;
      }
    }
  }
  cout<<3*r-1<<endl;
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
// #include<set>
// #include<algorithm>
// using namespace std;
// void test(){
//   int n,m;
//   cin>>n>>m;
//   vector<int> ss(n);
//   vector<int> ws(m);
//   for(int i=0;i<n;i++){
//     cin>>ss[i];
//   }
//   for(int i=0;i<m;i++){
//     cin>>ws[i];
//   }
//   sort(ss.begin(),ss.end(),greater<int>());
//   sort(ws.begin(),ws.end(),greater<int>());
//   if(ws[0]>ss[0]){
//     cout<<"impossible"<<endl;
//     return;
//   }
//   multiset<int,greater<int>> ws2;
//   for(int i=0;i<m;i++){
//     ws2.insert(ws[i]);
//   }
//   int r=0;
//   bool c=false;
//   while(!ws2.empty()){
//     r++;
//     for(int i=0;i<n;i++){
//       auto b=ws2.lower_bound(ss[i]);
//       if(b!=ws2.end()){
//         ws2.erase(b);
//       }else{
//         if(i==1){
//           c=true;
//         }
//         break;
//       }
//     }
//     if(c){
//       r+=ws2.size();
//       break;
//     }
//   }
//   cout<<3*r-1<<endl;
// }
// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int cases; cin>>cases;
//   for(;cases;cases--){
//     test();
//   }
// }