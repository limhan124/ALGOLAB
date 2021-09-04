#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include<vector>
#include<iostream>
// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
using namespace std;

void solve(){
  int n,m;
  long s;
  cin>>n>>m>>s;
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  const int b=0;
  const int c=1;
  const int d=2;
  const int lf=3;
  //noble
  long noble_sum_x=0;
  long noble_sum_y=0;
  vector<pair<int,int>> nobles;
  for(int i=0;i<n;i++){
    int x,y;
    cin>>x>>y;
    lp.set_a(b, i, y); 
    lp.set_a(c, i, 1);
    lp.set_b(i,-x);
    noble_sum_x+=x;
    noble_sum_y+=y;
    nobles.push_back(make_pair(x,y));
  }
  //commom
  long common_sum_x=0;
  long common_sum_y=0;
  vector<pair<int,int>> commons;
  for(int i=0;i<m;i++){
    int x,y;
    cin>>x>>y;
    lp.set_a(b, i+n, -y); 
    lp.set_a(c, i+n, -1);
    lp.set_b(i+n,x);
    common_sum_x+=x;
    common_sum_y+=y;
    commons.push_back(make_pair(x,y));
  }
  Solution s_1 = CGAL::solve_linear_program(lp, ET());
  if(s_1.is_infeasible()){
    cout<<"Yuck!"<<endl;
    return;
  }else{
    if(s!=-1){
      lp.set_a(b, m+n, common_sum_y-noble_sum_y); 
      lp.set_a(c, m+n, m-n);
      lp.set_b(m+n,s+noble_sum_x-common_sum_x);
    }
    Solution s_2 = CGAL::solve_linear_program(lp, ET());
    if(s_2.is_infeasible()){
      cout<<"Bankrupt!"<<endl;
      return;
    }else{
      for(int i=0;i<n;i++){
        lp.set_a(b, i+m+n+1, -nobles[i].first); 
        lp.set_a(d, i+m+n+1, -1);
        lp.set_a(lf, i+m+n+1, -1);
        lp.set_b(i+m+n+1,-nobles[i].second);
        
        lp.set_a(b, i+m+2*n+1, nobles[i].first); 
        lp.set_a(d, i+m+2*n+1, 1);
        lp.set_a(lf, i+m+2*n+1, -1);
        lp.set_b(i+m+2*n+1,nobles[i].second);
      }
      for(int i=0;i<m;i++){
        lp.set_a(b, i+m+3*n+1, -commons[i].first); 
        lp.set_a(d, i+m+3*n+1, -1);
        lp.set_a(lf, i+m+3*n+1, -1);
        lp.set_b(i+m+3*n+1,-commons[i].second);
        
        lp.set_a(b, i+2*m+3*n+1, commons[i].first); 
        lp.set_a(d, i+2*m+3*n+1, 1);
        lp.set_a(lf, i+2*m+3*n+1, -1);
        lp.set_b(i+2*m+3*n+1,commons[i].second);
      }
      lp.set_c(lf,1);
      Solution s_3 = CGAL::solve_linear_program(lp, ET());
      long res=ceil(CGAL::to_double(s_3.objective_value()));
      cout<<res<<endl;
    }
  }
}
using namespace std;
int main(){
  int t; cin>>t;
  while(t--){
    solve();
  }
}
// #include<iostream>
// #include<vector>
// #include <CGAL/QP_models.h>
// #include <CGAL/QP_functions.h>
// #include <CGAL/Gmpz.h>
// // choose input type (input coefficients must fit)
// typedef long IT;
// // choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
// typedef CGAL::Gmpz ET;

// // program and solution types
// typedef CGAL::Quadratic_program<IT> Program;
// typedef CGAL::Quadratic_program_solution<ET> Solution;
// using namespace std;
// void solve(){
//   int n,m;
//   long s;
//   cin>>n>>m>>s;
//   Program lp_1 (CGAL::SMALLER, false, 0, false, 0);
//   const int b = 0;
//   const int c = 1;
//   const int d = 2;
//   const int lf = 3;
//   long x_noble_sum=0;
//   long y_noble_sum=0;
//   vector<pair<int,int>> nobles;
//   for(int i=0;i<n;i++){
//     int x,y;
//     cin>>x>>y;
//     lp_1.set_a(b, i, y);
//     lp_1.set_a(c, i, 1);
//     lp_1.set_b(i, -x);
    
//     x_noble_sum+=long(x);
//     y_noble_sum+=long(y);
//     nobles.push_back(make_pair(x,y));
//   }
//   long x_common_sum=0;
//   long y_common_sum=0;
//   vector<pair<int,int>> commons;
//   for(int i=0;i<m;i++){
//     int x,y;
//     cin>>x>>y;
//     lp_1.set_a(b, i+n, -y);
//     lp_1.set_a(c, i+n, -1);
//     lp_1.set_b(i+n, x);
    
//     x_common_sum+=long(x);
//     y_common_sum+=long(y);
//     commons.push_back(make_pair(x,y));
//   }
//   Solution s_1 = CGAL::solve_linear_program(lp_1, ET());
//   if(s_1.is_infeasible()) {
//     cout<<"Yuck!"<<endl;
//     return;
//   }else{
//     if(s!=-1){
//       lp_1.set_a(b, m+n, y_common_sum-y_noble_sum);
//       lp_1.set_a(c, m+n, m-n);
//       lp_1.set_b(m+n, x_noble_sum-x_common_sum+s);
//     }
//     lp_1.set_l(lf,true,0);
//     for(int i=0;i<n;i++){
//       lp_1.set_a(b, i+m+n+1, nobles[i].first);
//       lp_1.set_a(d, i+m+n+1, 1);
//       lp_1.set_a(lf, i+m+n+1, -1);
//       lp_1.set_b(i+m+n+1, nobles[i].second);
        
//       lp_1.set_a(b, i+m+2*n+1, -nobles[i].first);
//       lp_1.set_a(d, i+m+2*n+1, -1);
//       lp_1.set_a(lf, i+m+2*n+1, -1);
//       lp_1.set_b(i+m+2*n+1, -nobles[i].second);
//     }
//     for(int i=0;i<m;i++){
//       lp_1.set_a(b, i+m+3*n+1, commons[i].first);
//       lp_1.set_a(d, i+m+3*n+1, 1);
//       lp_1.set_a(lf, i+m+3*n+1, -1);
//       lp_1.set_b(i+m+3*n+1, commons[i].second);
        
//       lp_1.set_a(b, i+2*m+3*n+1, -commons[i].first);
//       lp_1.set_a(d, i+2*m+3*n+1, -1);
//       lp_1.set_a(lf, i+2*m+3*n+1, -1);
//       lp_1.set_b(i+2*m+3*n+1, -commons[i].second);
//     }
//     lp_1.set_c(lf, 1);
//     Solution s_2 = CGAL::solve_linear_program(lp_1, ET());
//     if(s_2.is_infeasible()) {
//       cout<<"Bankrupt!"<<endl;
//       return;
//     }else{
//       double result = s_2.objective_value_numerator().to_double() / s_2.objective_value_denominator().to_double();
//       cout << (long)ceil(result) << endl;
//     }
//   }
// }
// int main(){
//   int t; cin>>t;
//   while(t--){
//     solve();
//   }
// }