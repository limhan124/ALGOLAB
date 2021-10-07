#include<iostream>
using namespace std;
int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    int col;
    cin>>col;
    int mat[col][col];
    int even[col+1][col+1];
    for(int i=0;i<=col;i++){
      even[i][0]=1;
      even[0][i]=1;
    }
    for(int i=1;i<=col;i++){
      for(int j=1;j<=col;j++){
        cin>>mat[i-1][j-1];
        even[i][j]=(mat[i-1][j-1]%2==0)?1:-1;
        even[i][j]=even[i-1][j]*even[i-1][j-1]*even[i][j-1]*even[i][j];
      }
    }
    // for(int i=0;i<=col;i++){
    //   for(int j=0;j<=col;j++){
    //     cout<<even[i][j]<<" ";
    //   }
    //   cout<<endl;
    // }
    int ans=0;
    for(int i_1=1;i_1<=col;i_1++){
      for(int i_2=i_1;i_2<=col;i_2++){
        int evens=0;
        int odds=0;
        for(int j=1;j<=col;j++){
          if(i_1==i_2){
            if(even[i_1][j]==1){
              ans++;
              ans+=evens;
              evens++;
            }else{
              ans+=odds;
              odds++;
            }
            continue;
          }
          if(even[i_1][j]*even[i_2][j]==1){
            ans++;
            ans+=evens;
            evens++;
          }else{
            ans+=odds;
            odds++;
          }
        }
      }
    }
    cout<<ans<<endl;
  }
  return 0;
}
