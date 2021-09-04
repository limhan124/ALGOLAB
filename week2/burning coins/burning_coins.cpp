#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
// static int dp[2500][2500];
int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    int num;
    cin>>num;
    int coins[num];
    for(int i=0;i<num;i++){
      cin>>coins[i];
    }
    
    std::vector<vector<int>> dp(num);
    for(int i=0;i<num;i++){
      dp[i].resize(num);
    }
    
    // int dp[num][num];
    dp[0][0]=coins[0];
    //i为列
    //j为行
    //列不变，行变小
    for(int i=0;i<num;i++){
      int sum=0;
      for(int j=i;j>=0;j--){
        sum+=coins[j];
        if(j==i){
          dp[i][i]=coins[i];
          continue;
        }else if(i-j==1)
        {
          dp[j][i]=max(coins[i],coins[j]);
        }else
        {
          dp[j][i]=max(coins[i]+dp[i-1][j],coins[j]+dp[i][j+1]);
        }
        dp[i][j]=sum-dp[j][i];
      }
    }
    cout<<dp[0][num-1]<<endl;
  }
}