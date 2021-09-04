#include<iostream>
#include<vector>
#include<algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n; cin>>n;
  while(n!=0){
    Triangulation tri;
    vector<P> points(n);
    int l,b,r,t; cin>>l>>b>>r>>t;
    vector<K::FT> min_dis;
    for(int i=0;i<n;i++){
      int x,y; cin>>x>>y;
      points[i]=P(x,y);
    }
    tri.insert(points.begin(), points.end());
    for(auto v=tri.vertices_begin();v!=tri.vertices_end();v++){
      P p=v->point();
      long min_d=min(abs(p.x()-l),abs(p.x()-r));
      min_d=min((long)abs(p.y()-b),min_d);
      min_d=min((long)abs(p.y()-t),min_d);
      min_d=min_d*min_d*4;//与后面(r/2)*(r/2)变得可比较
      Triangulation::Edge_circulator c=tri.incident_edges(v->handle());
      if(c!=0) do{
        if(!tri.is_infinite(c)&&(min_d>(tri.segment(c).squared_length()))){
          min_d=tri.segment(c).squared_length();
        }
      } while(++c!=tri.incident_edges(v->handle()));
      min_dis.push_back(min_d);
    }
    sort(min_dis.begin(), min_dis.end());
    cout<<fixed<<setprecision(0)<<ceil(CGAL::to_double(CGAL::sqrt(CGAL::sqrt(min_dis[0]/4)-0.5)))<<" ";
    cout<<fixed<<setprecision(0)<<ceil(CGAL::to_double(CGAL::sqrt(CGAL::sqrt(min_dis[n/2]/4)-0.5)))<<" ";
    cout<<fixed<<setprecision(0)<<ceil(CGAL::to_double(CGAL::sqrt(CGAL::sqrt(min_dis[n-1]/4)-0.5)))<<endl;
    cin>>n;
  }
}