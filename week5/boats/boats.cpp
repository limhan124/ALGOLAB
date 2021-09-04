#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct{
  int length;
  int position;
}boat;
bool cmp(boat i,boat j){
  return i.position<j.position;
}
void test(){
  int n;
  cin>>n;
  vector<boat> boats(n); 
  for(int i=0;i<n;i++){
    int length,position; cin>>length>>position;
    boat b;
    b.length=length;
    b.position=position;
    boats[i]=b;
  }
  sort(boats.begin(),boats.end(),cmp);
  int end_of_line=boats[0].position;
  int prev_eol=end_of_line;
  int res=1;
  // cout<<end_of_line<<" "<<prev_eol<<endl;
  for(int i=1;i<n;i++){
    if(end_of_line<=boats[i].position){
      prev_eol=end_of_line;
      //若pre_p+boats[i]则紧紧接上一茬，可能朝左可能朝右
      //若boats[i].position则与上一茬有点距离，依旧朝左
      end_of_line=max(end_of_line+boats[i].length,boats[i].position);
      res++;
    }else//要选一个end_of_line最小的！！！
    {
      int potential_eol=max(prev_eol+boats[i].length,boats[i].position);
      if(potential_eol<end_of_line){
        end_of_line=potential_eol;
      }
      //也不用新增，因为之前的不好的相当于被替换了
    }
  }
  cout<<res<<endl;
}
int main(){
  int cases; cin>>cases;
  for(;cases;cases--){
    test();
  }
  return 0;
}