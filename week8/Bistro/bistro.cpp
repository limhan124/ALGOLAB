#include<iostream>
#include<vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
using namespace std;
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n; cin>>n;
  while(n!=0){
    Triangulation t;
    vector<P> points(n);
    for(int i=0;i<n;i++){
      int x,y; cin>>x>>y;
      points[i]=P(x,y);
    }
    t.insert(points.begin(), points.end());
    int m; cin>>m;
    for(int i=0;i<m;i++){
      int x,y; cin>>x>>y;
      P p=P(x,y);
      long res=CGAL::squared_distance(p,t.nearest_vertex(p)->point());
      cout<<fixed<<setprecision(0)<<res<<endl;
    }
    cin>>n;
  }
}