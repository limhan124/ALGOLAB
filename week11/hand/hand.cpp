#include<iostream>
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
// As edges are not explicitly represented in the triangulation, we extract them
// from the triangulation to be able to sort and process them. We store the
// indices of the two endpoints, first the smaller, second the larger, and third
// the squared length of the edge. The i-th entry, for i=0,... of a tuple t can
// be accessed using std::get<i>(t).
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef std::pair<K::Point_2,Index> IPoint;
typedef K::Point_2 P;
using namespace std;
int cal(long s,int n,int k,EdgeV &edges){
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  // ... and process edges in order of increasing length
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end() && get<2>(*e)<s; ++e) {
    // determine components of endpoints
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      // this edge connects two different components => part of the emst
      uf.link(c1, c2);
      n_components--;
    }
  }
  vector<int> components(n);
  for(int i=0;i<n;i++){
    components[uf.find_set(i)]++;
  }
  int res_f=0;
  vector<int> clusters_less_than_k(k,0);
  for(int i=0;i<n;i++){
    if(components[i]>=k){
      res_f++;
    }
    else{
      clusters_less_than_k[components[i]]++;
    }
  }
  if(k==2){
    res_f+=clusters_less_than_k[1]/2;
  }else if(k==3){
    if(clusters_less_than_k[1]<clusters_less_than_k[2]){
      res_f+=clusters_less_than_k[1];
      res_f+=(clusters_less_than_k[2]-clusters_less_than_k[1])/2;
    }else {
      res_f+=clusters_less_than_k[2];
      res_f+=(clusters_less_than_k[1]-clusters_less_than_k[2])/3;
    }
  }else if(k==4){
    res_f+=clusters_less_than_k[2]/2;
    int twos_left = clusters_less_than_k[2] % 2;
    if(clusters_less_than_k[1]<clusters_less_than_k[3]){
      res_f+=clusters_less_than_k[1];
      res_f+=(clusters_less_than_k[3]-clusters_less_than_k[1]+twos_left)/2;
    }else{
      res_f+=clusters_less_than_k[3];
      res_f+=(clusters_less_than_k[1]-clusters_less_than_k[3]+twos_left*2)/4;
    }
  }
  return res_f;
}

void solve(){
  int n,k,f; cin>>n>>k>>f;
  long s; cin>>s;
  std::vector<IPoint> tents;
  for(int i=0;i<n;i++){
    int x,y; cin>>x>>y;
    tents.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(tents.begin(), tents.end());

  // extract edges and sort by (squared) length
  // This step takes O(n log n) time (for the sorting).
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
  int f_max=cal(s,n,k,edges);
  // int s_max=0;
  // for (int i=edges.size()-1;i>=0;i--){
  //   int tmp_res = cal(get<2>(edges[i]), n, k, edges);
  //   if(tmp_res>=f){
  //     s_max=get<2>(edges[i]);
  //     break;
  //   }
  // }
  // cout<<s_max<<" "<<f_max<<endl;
  long upper=LONG_MAX;
  long lower=0;
  while(upper>lower){
    long tmp_s=(upper+lower)/2;
    int tmp_res = cal(tmp_s, n, k, edges);
    if(tmp_res>=f){
      lower=tmp_s+1;
    }else{
      upper=tmp_s;
    }
  }
  cout<<upper-1<<" "<<f_max<<endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t; cin>>t;
  for(;t;t--){
    solve();
  }
}