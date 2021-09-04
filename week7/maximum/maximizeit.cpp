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
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int p;
  cin>>p;
  while(p!=0){
    int a,b;
    cin>>a>>b;
    Solution s;
    if(p==1){
      Program lp (CGAL::SMALLER, true, 0, false, 0); 
      const int x = 0;
      const int y = 1;
      lp.set_a(x,0,1); 
      lp.set_a(y,0,1);
      lp.set_b(0,4);
      lp.set_a(x,1,4); 
      lp.set_a(y,1,2);
      lp.set_b(1,a*b);
      lp.set_a(x,2,-1); 
      lp.set_a(y,2,1);
      lp.set_b(2,1);
      lp.set_c(x,a);
      lp.set_c(y,-b);
      s=CGAL::solve_linear_program(lp, ET());
    }else if(p==2){
      Program lp (CGAL::SMALLER, false, 0, true, 0); 
      const int x = 0;
      const int y = 1;
      const int z = 2;
      lp.set_a(x,0,-1); 
      lp.set_a(y,0,-1);
      lp.set_a(z,0,0);
      lp.set_b(0,4);
      lp.set_a(x,1,-4); 
      lp.set_a(y,1,-2);
      lp.set_a(z,1,-1);
      lp.set_b(1,a*b);
      lp.set_a(x,2,1); 
      lp.set_a(y,2,-1);
      lp.set_a(z,2,0);
      lp.set_b(2,1);
      lp.set_c(x,a);
      lp.set_c(y,b);
      lp.set_c(z,1);
      s=CGAL::solve_linear_program(lp, ET());
    }
    if (s.is_optimal()) { 
      int res=ceil(CGAL::to_double(s.objective_value()));
      if(p==1){
        res=-1*res;
      }
      cout<<res<<endl;
    }
    if (s.is_unbounded()) { cout<<"unbounde"<<endl; }
    if (s.is_infeasible()) { cout<<"no"<<endl; }
    cin>>p;
  }
}