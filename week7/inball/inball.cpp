#include<iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
using namespace std;
void solve(int n){
  int d; cin>>d;
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  //d+1个未知数
  //n个不等式
  for(int i=0;i<n;i++){
    int ro_sq=0;
    for(int j=0;j<d;j++){
      int coeff; cin>>coeff;
      lp.set_a(j,i,coeff);
      ro_sq+=coeff*coeff;
    }
    lp.set_a(d,i,(int)sqrt(ro_sq));
    int bi; cin>>bi;
    lp.set_b(i,bi);
  }
  lp.set_c(d,-1);
  lp.set_l(d,true,0);
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout<<"none"<<endl;
    return;
  }
  if(s.is_unbounded()){
    cout<<"inf"<<endl;
    return;
  } 
  cout<<floor(CGAL::to_double(-s.objective_value()))<<endl;
}
int main(){
  int n,d;
  cin>>n;
  while(n){
    solve(n);
    cin>>n;
  }
}

// #include<iostream>
// #include<vector>
// #include<algorithm>
// #include <CGAL/QP_models.h>
// #include <CGAL/QP_functions.h>
// #include <CGAL/Gmpz.h>
// // choose input type (input coefficients must fit)
// typedef int IT;
// // choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
// typedef CGAL::Gmpz ET;
// // program and solution types
// typedef CGAL::Quadratic_program<IT> Program;
// typedef CGAL::Quadratic_program_solution<ET> Solution;
// using namespace std;
// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int n,d;
//   cin>>n;
//   while(n!=0){
//     cin>>d;
//     Program lp (CGAL::SMALLER, false, 0, false, 0);
//     for(int i=0;i<n;i++){
//       int sum=0;
//       for(int j=0;j<=d;j++){
//         int num;
//         cin>>num;
//         if(j==d){
//           lp.set_b(i,num);
//         }else{
//           lp.set_a(j,i,num);
//           sum+=num*num;
//         }
//       }
//       int sqr_sum=(int)sqrt(sum);
//       lp.set_a(d,i,sqr_sum);
//     }
//     lp.set_c(d,-1);
//     lp.set_l(d,true,0);
//     Solution s = CGAL::solve_linear_program(lp, ET());
//     if(s.is_infeasible()){
//       cout<<"none"<<endl;
//     }
//     else if(s.is_unbounded()){
//       cout<<"inf"<<endl;
//     }else{
//       cout<<floor(CGAL::to_double(-s.objective_value()))<<endl;
//     }
//     cin>>n;
//   }
// }