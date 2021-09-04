#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;
int find(int b,vector<int> &path,vector<pair<string,int>> &name_age){
  int l=0; int u=path.size()-1;
  while(l<u){
    int mid=(l+u)/2;
    if(name_age[path[mid]].second>b){
      l=mid+1;
    }else{
      u=mid;
    }
  }
  return path[u];
}
void dfs(int index,vector<vector<int>> &query_on_i,vector<int> &path,vector<pair<string,int>> &name_age,map<pair<int,int>,int> &answer,vector<vector<int>> &childs){
  path.push_back(index);
  // cout<<"here"<<endl;
  for(int b:query_on_i[index]){
    int res=find(b,path,name_age);
    answer[make_pair(index,b)]=res;
    // cout<<name_age[res].first<<endl;
  }
  for(int child:childs[index]){
    dfs(child,query_on_i,path,name_age,answer,childs);
  }
  path.pop_back();
}
void solve(){
  int n,q;
  cin>>n>>q;
  map<string,int> name_index;
  vector<pair<string,int>> name_age;
  int root=-1;
  int max_age=-1;
  for(int i=0;i<n;i++){
    string n;
    int a;
    cin>>n>>a;
    name_index[n]=i;
    name_age.push_back(make_pair(n,a));
    if(a>max_age){
      max_age=a;
      root=i;
    }
  }
  vector<vector<int>> childs(n);
  for(int i=0;i<n-1;i++){
    string s,p;
    cin>>s>>p;
    childs[name_index[p]].push_back(name_index[s]);
  }
  vector<pair<int,int>> query;
  vector<vector<int>> query_on_i(n);
  for(int i=0;i<q;i++){
    string s;
    int b;
    cin>>s>>b;
    query_on_i[name_index[s]].push_back(b);
    query.push_back(make_pair(name_index[s],b));
  }
  vector<int> path;
  map<pair<int,int>,int> answer;
  dfs(root,query_on_i,path,name_age,answer,childs);
  for(int i=0;i<q;i++){
    cout<<name_age[answer[query[i]]].first<<" ";
  }
  cout<<endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t; cin>>t;
  while(t--){
    solve();
  }
}