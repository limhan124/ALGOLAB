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
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef std::pair<K::Point_2,Index> IPoint;
typedef K::Point_2 P;
using namespace std;

void solve(){
  int z,u,v,w;
  cin>>z>>u>>v>>w;
  int a,g;
  cin>>a>>g;
  vector<IPoint> gangs;
  vector<tuple<int,int,int>> leaks;
  for(int i=0;i<g;i++){
    int x,y,ui,vi,wi;
    cin>>x>>y>>ui>>vi>>wi;
    gangs.emplace_back(K::Point_2(x, y), i);
    leaks.push_back(make_tuple(ui,vi,wi));
  }
  Delaunay t;
  t.insert(gangs.begin(), gangs.end());
  vector<int> g_a_fee(g,INT_MAX);
  for(int i=0;i<a;i++){
    int x,y,zi;
    cin>>x>>y>>zi;
    P agent=P(x,y);
    int tmp=t.nearest_vertex(agent)->info();
    if(g_a_fee[tmp]>zi){
      g_a_fee[tmp]=zi;
    }
  }
  Program lp (CGAL::SMALLER, true, 0, true, 24); 
  int varible=0;
  for(int i=0;i<g;i++){
    if(g_a_fee[i]!=INT_MAX){
      lp.set_a(varible,0,g_a_fee[i]);
      lp.set_a(varible,1,-get<0>(leaks[i]));
      lp.set_a(varible,2,-get<1>(leaks[i]));
      lp.set_a(varible,3,-get<2>(leaks[i]));
      varible++;
    }
  }
  lp.set_b(0,z);
  lp.set_b(1,-u);
  lp.set_b(2,-v);
  lp.set_b(3,-w);
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout<<"H"<<endl;
  }else{
    cout<<"L"<<endl;
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
// #include <CGAL/Gmpz.h>
// // choose input type (input coefficients must fit)
// typedef int IT;
// // choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
// typedef CGAL::Gmpz ET;
// // program and solution types
// typedef CGAL::Quadratic_program<IT> Program;
// typedef CGAL::Quadratic_program_solution<ET> Solution;

// #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// #include <CGAL/Delaunay_triangulation_2.h>
// #include <CGAL/Triangulation_vertex_base_with_info_2.h>
// #include <CGAL/Triangulation_face_base_2.h>
// typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// typedef std::size_t                                            Index;
// typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
// typedef CGAL::Triangulation_face_base_2<K>                     Fb;
// typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
// typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
// typedef std::pair<K::Point_2,Index> IPoint;
// typedef K::Point_2 P;
// #include<vector>
// #include<tuple>
// using namespace std;
// void solve(){
//   int z,u,v,w;
//   cin>>z>>u>>v>>w;
//   int a,g;
//   cin>>a>>g;
//   Program lp (CGAL::SMALLER, true, 0, true, 24);
//   Delaunay tri;
//   vector<IPoint> gangs;
//   vector<tuple<int,int,int>> leaks;
//   vector<int> g_a_z(g,-1);
//   for(int i=0;i<g;i++){
//     int x,y,ui,vi,wi;
//     cin>>x>>y>>ui>>vi>>wi;
//     gangs.emplace_back(K::Point_2(x, y), i);
//     leaks.push_back(make_tuple(ui,vi,wi));
//   }
//   tri.insert(gangs.begin(), gangs.end());
//   for(int i=0;i<a;i++){
//     int x,y,zi;
//     cin>>x>>y>>zi;
//     P agent = P(x,y);
//     int gang=tri.nearest_vertex(agent)->info();
//     if(g_a_z[gang]>zi || g_a_z[gang]==-1){
//       g_a_z[gang]=zi;
//     }
//   }
//   int varible=0;
//   for(int i=0;i<g;i++){
//     if(g_a_z[i]!=-1){
//       lp.set_a(varible,0,g_a_z[i]);
//       lp.set_a(varible,1,-get<0>(leaks[i]));
//       lp.set_a(varible,2,-get<1>(leaks[i]));
//       lp.set_a(varible,3,-get<2>(leaks[i]));
//       varible++;
//     }
//   }
//   lp.set_b(0,z);
//   lp.set_b(1,-u);
//   lp.set_b(2,-v);
//   lp.set_b(3,-w);
//   Solution s = CGAL::solve_linear_program(lp, ET());
//   if(s.is_infeasible()){
//     cout<<"H"<<endl;
//   }else{
//     cout<<"L"<<endl;
//   }
// }
// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int t;
//   cin>>t;
//   for(;t;t--){
//     solve();
//   }
// }
// // #include<iostream>
// // #include<vector>
// // #include<tuple>
// // // #include<pair>
// // #include <CGAL/QP_models.h>
// // #include <CGAL/QP_functions.h>
// // #include <CGAL/Gmpz.h>

// // // choose input type (input coefficients must fit)
// // typedef int IT;
// // // choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
// // typedef CGAL::Gmpz ET;

// // // program and solution types
// // typedef CGAL::Quadratic_program<IT> Program;
// // typedef CGAL::Quadratic_program_solution<ET> Solution;
// // #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// // #include <CGAL/Delaunay_triangulation_2.h>
// // #include <CGAL/Triangulation_vertex_base_with_info_2.h>
// // #include <CGAL/Triangulation_face_base_2.h>
// // typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// // // we want to store an index with each vertex
// // typedef std::size_t                                            Index;
// // typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
// // typedef CGAL::Triangulation_face_base_2<K>                     Fb;
// // typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
// // typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
// // typedef std::tuple<Index,Index,K::FT> Edge;
// // typedef std::vector<Edge> EdgeV;
// // typedef std::pair<K::Point_2,Index> IPoint;
// // typedef K::Point_2 Point;
// // using namespace std;
// // void test(){
// //   Program lp (CGAL::SMALLER, true, 0, true, 24);
// //   int z_0,u_0,v_0,w_0;
// //   cin>>z_0>>u_0>>v_0>>w_0;
// //   lp.set_b(0,-u_0);
// //   lp.set_b(1,-v_0);
// //   lp.set_b(2,-w_0);
// //   lp.set_b(3,z_0);
// //   int a,g; cin>>a>>g;
// //   Delaunay tri;
// //   vector<IPoint> points;
// //   vector<tuple<int,int,int>> gangs;
// //   for(int i=0;i<g;i++){
// //     int x,y,u,v,w;
// //     cin>>x>>y>>u>>v>>w;
// //     points.push_back(make_pair(Point(x,y),i));
// //     gangs.push_back(make_tuple(u,v,w));
// //   }
// //   tri.insert(points.begin(),points.end());
// //   vector<int> gang_agent(g,-1);
// //   vector<int> wages(a);
// //   for(int i=0;i<a;i++){
// //     int x,y,z;
// //     cin>>x>>y>>z;
// //     wages[i]=z;
// //     int index_g=tri.nearest_vertex(Point(x,y))->info();
// //     if(gang_agent[index_g]>=0){
// //       if(z<wages[gang_agent[index_g]]){
// //         gang_agent[index_g]=i;
// //       }
// //     }else{
// //       gang_agent[index_g]=i;
// //     }
// //   }
// //   for(int i=0;i<g;i++){
// //     if(gang_agent[i]<0){
// //       continue;
// //     }else{
// //       lp.set_a(gang_agent[i],0,-get<0>(gangs[i]));
// //       lp.set_a(gang_agent[i],1,-get<1>(gangs[i]));
// //       lp.set_a(gang_agent[i],2,-get<2>(gangs[i]));
// //       lp.set_a(gang_agent[i],3,wages[gang_agent[i]]);
// //     }
// //   }
// //   Solution s = CGAL::solve_linear_program(lp, ET());
// //   if(!s.is_infeasible()){
// //     cout<<"L"<<endl;
// //   }else{
// //     cout<<"H"<<endl;
// //   }
// // }
// // int main(){
// //   int cases; cin>>cases;
// //   for(;cases;cases--){
// //     test();
// //   }
// // }