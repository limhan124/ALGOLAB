#include<iostream>
#include<vector>
#include<algorithm>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
using namespace std;
void test(){
  int x_s,y_s,n;
  cin>>x_s>>y_s>>n;
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  const int t=0;
  const int x=1;
  const int y=2;
  for(int i=0;i<n;i++){
    long a,b,c,v;
    cin>>a>>b>>c>>v;
    int num=-1;
    if(a*x_s+b*y_s+c>=0){
      num=1;
    }
    lp.set_a(t,i,v*sqrt(a*a+b*b));
    lp.set_a(x,i,-a*num);
    lp.set_a(y,i,-b*num);
    lp.set_b(i,c*num);
  }
  lp.set_l(t,true,0);
  lp.set_c(t,-1);
  lp.set_c(x,0);
  lp.set_c(y,0);
  lp.set_c0(0);
  Solution s=CGAL::solve_linear_program(lp, ET());
  cout<<fixed<<setprecision(0)<<floor(CGAL::to_double(-1*s.objective_value()))<<endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int c; cin>>c;
  for(;c;c--){
    test();
  }
  return 0;
}