#include<iostream>
#include<vector>
#include<algorithm>
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
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n,m;
  cin>>n>>m;
  while(n != 0 || m != 0) {
    Program lp (CGAL::SMALLER, true, 0, false, 0);
    for(int i=0;i<n;i++) {
      int minc,maxc;
      cin>>minc>>maxc;
      lp.set_b(i,maxc);
      lp.set_b(n+i,-minc);
    }
    for(int i=0;i<m;i++) {
      int price;
      cin>>price;
      lp.set_c(i,price);
      for(int j=0;j<n;j++) {
        int contain;
        cin>>contain;
        lp.set_a(i,j,contain);
        lp.set_a(i,n+j,-contain);
      }
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()){
      cout<<"No such diet."<<endl;
    }
    else{
      cout<<floor(CGAL::to_double(s.objective_value()))<<endl;
    }
    cin>>n>>m;
  }
}