#include<iostream>
#include<vector>
#include<climits>
using namespace std;
void testcase(){
  int n,m;
  cin>>n>>m;
  int r,b;
  cin>>r>>b;
  
  vector<vector<int>> transitions(n);
  for(int i=0;i<m;i++){
    int u,v;
    cin>>u>>v;
    transitions[u-1].push_back(v-1);
  }
  
  vector<int> min_step_slow_final(n,-1);
  vector<int> max_step_fast_final(n,INT_MAX);
  //终点到终点是0步
  min_step_slow_final[n-1]=0;
  max_step_fast_final[n-1]=0;
  
  for(int i=n-2;i>=0;i--){
    int fast=INT_MAX;
    int slow=-1;
    for(int j=0;j<transitions[i].size();j++){
      int transit_point=transitions[i][j];
      // cout<<"here"<<endl;
      if(fast>1+min_step_slow_final[transit_point]){
        fast=1+min_step_slow_final[transit_point];
      }
      if(slow<1+max_step_fast_final[transit_point]){
        slow=1+max_step_fast_final[transit_point];
      }
    }
    min_step_slow_final[i]=slow;
    max_step_fast_final[i]=fast;
    // cout<<min_step_slow_final[i]<<" "<<max_step_fast_final[i]<<endl;
  }
  
  int r_moves=max_step_fast_final[r-1];
  int b_moves=max_step_fast_final[b-1];
  if (r_moves < b_moves) {
      //Sherlock赢了
    std::cout << "0" << std::endl;
  } else if (r_moves > b_moves){
      //Moriarty赢了
    std::cout << "1" << std::endl;
  } else {
    std::cout << 1 - r_moves % 2 << std::endl; 
  }
}

int main(){
  
    int t; std::cin >> t;
    for(int i = 0; i < t; ++i) {
        testcase();
    }
}


