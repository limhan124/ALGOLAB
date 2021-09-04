// example: how to solve a simple explicit LP
#include<iostream>
#include<vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

// choose input type (input coefficients must fit)
typedef CGAL::Gmpq IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
using namespace std;
void solve(){
  int n,m,c;
  cin>>n>>m>>c;
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  Triangulation tri;
  vector<P> points;
  for(int i=0;i<n;i++){
    int x,y,s,a;
    cin>>x>>y>>s>>a;
    points.push_back(P(x,y));
    for(int j=0;j<m;j++){
      lp.set_a(i*m+j,i,1);
      lp.set_a(i*m+j,j+n,a);
      lp.set_a(i*m+j,j+n+m,1);
      lp.set_a(i*m+j,j+n+2*m,-1);
    }
    lp.set_b(i,s);
  }
  for(int i=0;i<m;i++){
    int x,y,d,u;
    cin>>x>>y>>d>>u;
    points.push_back(P(x,y));
    lp.set_b(i+n,100*u);
    lp.set_b(i+n+m,d);
    lp.set_b(i+n+2*m,-d);
  }
  tri.insert(points.begin(), points.end());
  vector<vector<double>> cs(n,vector<double>(m));
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      cin>>cs[i][j];
    }
  }
  for(int k=0;k<c;k++){
    int x,y,r; cin>>x>>y>>r;
    P center=P(x,y);
    long r2=long(r)*long(r);
    if(CGAL::squared_distance(tri.nearest_vertex(center)->point(),center)>r2){
      continue;
    }else{
      for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
          bool b1=(CGAL::squared_distance(center,points[i])<=r2);
          bool b2=(CGAL::squared_distance(center,points[j+n])<=r2);
          if(b1!=b2){
            cs[i][j]-=0.01;
          }
        }
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      lp.set_c(i*m+j,-cs[i][j]);
    }
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout<<"RIOT!"<<endl;
  }else{
    cout<<fixed<<setprecision(0)<<floor(CGAL::to_double(-s.objective_value()))<<endl;
  }
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t; cin>>t;
  while(t--){
    solve();
  }
}


// #include<iostream>
// #include <CGAL/QP_models.h>
// #include <CGAL/QP_functions.h>
// #include <CGAL/Gmpq.h>
// // choose input type (input coefficients must fit)
// typedef CGAL::Gmpq IT;
// // choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
// typedef CGAL::Gmpq ET;
// // program and solution types
// typedef CGAL::Quadratic_program<IT> Program;
// typedef CGAL::Quadratic_program_solution<ET> Solution;

// #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// #include <CGAL/Delaunay_triangulation_2.h>
// typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
// typedef K::Point_2 P;
// #include<vector>

// using namespace std;

// void solve(){
//   int n,m,c;
//   cin>>n>>m>>c;
//   // create an LP with Ax <= b, lower bound 0 and no upper bounds
//   Program lp (CGAL::SMALLER, true, 0, false, 0);
//   vector<P> ps;

//   for(int i=0;i<n;i++){
//     P p;
//     int s,a;
//     cin>>p>>s>>a;
//     ps.push_back(p);
//     for(int j=0;j<m;j++){
//       lp.set_a(i*m+j,i,1);
//       lp.set_a(i*m+j,j+n,a);
//       lp.set_a(i*m+j,j+n+m,1);
//       lp.set_a(i*m+j,j+n+2*m,-1);
//     }
//     lp.set_b(i,s);
//   }  
//   for(int j=0;j<m;j++){
//     P p;
//     int d,u;
//     cin>>p>>d>>u;
//     ps.push_back(p);
//     lp.set_b(j+n,u*100);
//     lp.set_b(j+n+m,d);
//     lp.set_b(j+n+2*m,-d);
//   }
//   vector<vector<double>> rs(n);
//   for(int i=0;i<n;i++){
//     rs[i].resize(m);
//     for(int j=0;j<m;j++){
//       cin>>rs[i][j];
//     }
//   }

//   Triangulation tri;
//   tri.insert(ps.begin(), ps.end());
//   for(int k=0;k<c;k++){
//     P center;
//     int r;
//     cin>>center>>r;
//     if(CGAL::squared_distance(tri.nearest_vertex(center)->point(),center)<r*r){
//       for(int i=0;i<n;i++){
//         for(int j=0;j<m;j++){
//           bool b1=(CGAL::squared_distance(ps[i],center)<r*r);
//           bool b2=(CGAL::squared_distance(ps[j+n],center)<r*r);
//           if(b1!=b2){
//             rs[i][j]-=0.01;
//           }
//         }
//       }
//     }
//   }
//   for(int i=0;i<n;i++){
//     for(int j=0;j<m;j++){
//       lp.set_c(i*m+j,-rs[i][j]);
//     }
//   }
//   // solve the program, using ET as the exact type  
//   Solution s = CGAL::solve_linear_program(lp, ET());
//   if (s.is_infeasible()){
//     cout<<"RIOT!"<<endl;
//   }else{
//     cout<<fixed<<setprecision(0)<<floor(CGAL::to_double(-s.objective_value()))<<endl;
//   }
// }


// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int t;
//   cin>>t;
//   for(int i=0;i<t;i++){
//     solve();
//   }
// }
// // #include <iostream>
// // #include <CGAL/QP_models.h>
// // #include <CGAL/QP_functions.h>
// // #include <CGAL/Gmpq.h>
// // // choose input type (input coefficients must fit)
// // typedef CGAL::Gmpq IT;
// // // choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
// // typedef CGAL::Gmpq ET;
// // // program and solution types
// // typedef CGAL::Quadratic_program<IT> Program;
// // typedef CGAL::Quadratic_program_solution<ET> Solution;

// // #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// // #include <CGAL/Delaunay_triangulation_2.h>
// // #include <vector>
// // typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// // typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
// // typedef K::Point_2 P;
// // using namespace std;

// // void test(){
// //   int n,m,c;
// //   cin>>n>>m>>c;
// //   // create an LP with Ax <= b and no upper bounds and >=0
// //   Program lp (CGAL::SMALLER, true, 0, false, 0); 
// //   vector<P> ps;
// //   for(int i=0;i<n;i++){
// //     int x,y,s,a;
// //     cin>>x>>y>>s>>a;
// //     ps.push_back(P(x,y));
// //     for(int j=0;j<m;j++){
// //       lp.set_a(i*m+j,i,1); 
// //       lp.set_a(i*m+j,j+n,a);
// //       lp.set_a(i*m+j,j+n+m,1);
// //       lp.set_a(i*m+j,j+n+(m*2),-1); 
// //     }
// //     lp.set_b(i,s);
// //   }
// //   for(int i=0;i<m;i++){
// //     int x,y,d,u;
// //     cin>>x>>y>>d>>u;
// //     ps.push_back(P(x,y));
// //     lp.set_b(i+n,u*100);
// //     lp.set_b(i+n+m,d);
// //     lp.set_b(i+n+(m*2),-1*d);
// //   }
// //   vector<vector<double>> rs(n);
// //   for(int i=0;i<n;i++){
// //     rs[i].resize(m);
// //     for(int j=0;j<m;j++){
// //       int r; cin>>r;
// //       rs[i][j]=-r;
// //     }
// //   }
// //   Triangulation tri;
// //   tri.insert(ps.begin(), ps.end());
// //   for(int i=0;i<c;i++){
// //     P center;
// //     int r;
// //     cin>>center>>r;
// //     long r_2=r*r;
// //     if(CGAL::squared_distance(tri.nearest_vertex(center)->point(),center)<=r_2){
// //       for(int a=0;a<n;a++){
// //         for(int b=0;b<m;b++){
// //           bool sign1=(CGAL::squared_distance(ps[a],center)<=r_2);
// //           bool sign2=(CGAL::squared_distance(ps[b+n],center)<=r_2);
// //           if(sign1 != sign2){
// //             rs[a][b]+=0.01;
// //           }
// //         }
// //       }
// //     }
// //   }
// //   for(int i=0;i<n;i++){
// //     for(int j=0;j<m;j++){
// //       lp.set_c(i*m+j,rs[i][j]);
// //     }
// //   }
  
// //   // solve the program, using ET as the exact type
// //   Solution s = CGAL::solve_linear_program(lp, ET());
// //   assert(s.solves_linear_program(lp));
// //   // output solution
// //   if(s.is_infeasible()){
// //     cout<<"RIOT!"<<endl;
// //   }
// //   else{
// //     cout<<fixed<<setprecision(0)<<floor(CGAL::to_double(-s.objective_value()))<<endl;
// //   }
// // }
// // int main(){
// //   ios_base::sync_with_stdio(false);
// //   cin.tie(0);
// //   int testcases;
// //   cin>>testcases;
// //   for(;testcases;testcases--){
// //     test();
// //   }
// // }