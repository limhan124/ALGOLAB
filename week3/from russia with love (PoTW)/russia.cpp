#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int dp(vector<int> &values,vector<vector<int>> &res,int left,int right,int m){
  if(left>right){
    return 0;
  }
  if(left==right){
    res[left][right]=values[left];
    return res[left][right];
  }
  if(res[left][right]!=-1){
    return res[left][right];
  }
  int chooseLeft=INT32_MAX;
  int chooseRight=INT32_MAX;
  for(int i=0;i<m;i++){
    chooseLeft=min(chooseLeft,dp(values,res,left+m-i,right-i,m));
    chooseRight=min(chooseRight,dp(values,res,left+i,right-m+i,m));
  }
  res[left][right]=max(values[left]+chooseLeft,values[right]+chooseRight);
  return res[left][right];
}
int main(){
  int cases; cin>>cases;
  for(;cases;cases--){
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> values(n);
    vector<vector<int>> res(n,vector<int>(n, -1));
    for(int i=0;i<n;i++){
      cin>>values[i];
    }
    int ans=INT32_MAX;
    for(int i=0;i<=k;i++){
      ans=min(ans,dp(values,res,i,n-1-k+i,m));
    }
    cout<<ans<<endl;
  }
}
// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;
// int dp(vector<int> &coins, vector<vector<int>> &memo, int start, int stop, int m) {
//     if(start > stop) return 0;
//     if(memo[start][stop] != -1) return memo[start][stop];
//     if(start == stop) {
//         memo[start][stop] = coins[start];
//         return memo[start][stop];
//     }
//     int box_start = INT32_MAX, box_stop = INT32_MAX;
//     for(int i = 0; i < m; i++) {
//         box_start = min(box_start, dp(coins, memo, start+m-i, stop-i, m));
//         box_stop = min(box_stop, dp(coins, memo, start+i, stop-m+i, m));
//     }
//     memo[start][stop] = max(coins[start] + box_start, coins[stop] + box_stop);
//     return memo[start][stop];
// }

// int main() {
    
//     int t;
//     cin >> t;
//     while(t--) {
//         int n, m, k;
//         cin >> n >> m >> k;
//         vector<int> coins(n);
//         vector<vector<int>> memo(n, vector<int>(n, -1));
//         for(int i = 0; i < n; i++) {
//             cin >> coins[i];
//         }
//         int result = INT32_MAX;
//         for(int i = 0; i <= k; i++)
//             result = min(result, dp(coins, memo, i, n-k+i-1, m));
//         cout << result << "\n";
//     }
// }

// #include<iostream>
// #include<vector>
// #include<climits>
// #include<algorithm>
// using namespace std;
// int doit(int left,int right,int k,int m,vector<vector<int>> res){
//   int minn=INT_MAX;
//   int rright=right-(m-1);
//   if(right<left){
//     return 0;
//   }
//   while(rright<=right){
//     if(rright>=left && res[left][rright]<minn){
//       minn=res[left][rright];
//     }
//     left++;
//     rright++;
//   }
//   cout<<minn<<endl;
//   return minn;
// }

// void testcases(){
//   int n,m;
//   int k;
//   cin>>n>>m;
//   cin>>k;
//   vector<int> values(n);
//   for(int i=0;i<n;i++){
//     cin>>values[i];
//   }
//   vector<vector<int>> res(n);
//   for(int i=0;i<n;i++){
//     res[i].resize(n);
//   }
//   //从j到i可以获得的钱
//   res[0][0]=(k==0)?values[0]:0;
//   //i是列，j是行
//   for(int i=0;i<n;i++){
//     for(int j=i;j>=0;j--){
//       if(j==i){
//         res[j][i]=(k==0)?values[i]:0;
//       }else{
//         if(i-j<k){
//           res[j][i]=0;
//         }else{
//           int left=j;
//           int right=i-k;
//           int minn=INT_MAX;
//           while(left<right && right<=i && left>=j){
//             int getleft=doit(left+1,right,k,m,res);
//             int getright=doit(left,right-1,k,m,res);
//             int tmp;
//             tmp=max(values[left]+getleft,values[right]+getright);
//             if(minn>tmp){
//               minn=tmp;
//             }
//             right++;
//             left++;
//           }
//           res[j][i]=minn;
//           // cout<<minn<<endl;
//         }
//       }
//     }
//   }
//   cout<<res[0][n-1]<<endl;
// }
// int main(){
//   int cases; cin>>cases;
//   for(;cases;cases--){
//     testcases();
//   }
//   return 0;
// }
