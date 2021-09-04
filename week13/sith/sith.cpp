#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef K::Point_2 P;
typedef std::pair<K::Point_2,Index> IPoint;
using namespace std;
bool feasible(int k,int r,vector<IPoint> points){
  Delaunay t;
  t.insert(points.begin(), points.end());
  long r2=long(r)*long(r);
  int n=points.size();
  EdgeV edges;
  edges.reserve(3*n); // there can be no more in a planar graph
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    // ensure smaller index comes first
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
  // setup and initialize union-find data structure
  boost::disjoint_sets_with_storage<> uf(n);
  // ... and process edges in order of increasing length
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end()&&get<2>(*e)<=r2; ++e) {
    // determine components of endpoints
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      // this edge connects two different components => part of the emst
      uf.link(c1, c2);
    }
  }
  vector<int> components(n,0);
  for(int i=0;i<n;i++){
    components[uf.find_set(i)]++;
  }
  int max_value=0;
  for(int i=0;i<n;i++){
    if(components[i]>max_value){
      max_value=components[i];
    }
  }
  return max_value>=k;
}
void solve(){
  int n,r;
  cin>>n>>r;
  vector<IPoint> points;
  for(int i=0;i<n;i++){
    int x,y;
    cin>>x>>y;
    points.push_back(make_pair(P(x,y),n-i-1));
  }
  //二分搜索，k：前k个已经被占领，剩下的"可以"被我占领
  int lower=0;
  int upper=n/2;
  while(lower<upper){
    int mid=(lower+upper+1)/2;
    vector<IPoint> pp(points.begin()+mid, points.end());
    if(feasible(mid,r,pp)){
      lower=mid;
    }else{
      upper=mid-1;
    }
  }
  cout<<lower<<endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t; cin>>t;
  while(t--){  
    solve();
  }
}
