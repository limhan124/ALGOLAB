#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool mysort(pair<int,int> a,pair<int,int> b){
  return a.first<b.first;
}
bool deactivated(vector<bool> &de,vector<int> &bombs_2,int &count,int i,int n){
  if(de[i]){
    return true;
  }
  if(count<bombs_2[i]){
    if(i>=n || de[2*i+1]&&de[2*i+2]){
      count++;
      de[i]=true;
      return true;
    }
    else{
      if(deactivated(de,bombs_2,count,2*i+1,n)
      && deactivated(de,bombs_2,count,2*i+2,n)
      && count<bombs_2[i]){
        count++;
        de[i]=true;
        return true;
      }else{
        return false;
      }
    }
  }
  else{
    return false;
  }
}
void test(){
  int n; cin>>n;
  vector<pair<int,int>> bombs;
  vector<int> bombs_2;
  for(int i=0;i<n;i++){
    int t;cin>>t;
    bombs.push_back(make_pair(t,i));
    bombs_2.push_back(t);
  }
  sort(bombs.begin(),bombs.end(),mysort);
  int count=0;
  vector<bool> de(n,false);
  bool check=true;
  int pp=(n-1)/2;
  for(int i=0;i<n;i++){
    check=deactivated(de,bombs_2,count,bombs[i].second,pp);
    if(!check){
      break;
    }
  }
  if(check){
    cout<<"yes"<<endl;
  }else{
    cout<<"no"<<endl;
  }
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int cases;
  cin>>cases;
  for(;cases;cases--){
    test();
  }
  return 0;
}