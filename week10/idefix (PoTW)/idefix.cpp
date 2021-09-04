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
typedef K::Point_2 P;
// As edges are not explicitly represented in the triangulation, we extract them
// from the triangulation to be able to sort and process them. We store the
// indices of the two endpoints, first the smaller, second the larger, and third
// the squared length of the edge. The i-th entry, for i=0,... of a tuple t can
// be accessed using std::get<i>(t).
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef std::pair<K::Point_2,Index> IPoint;
using namespace std;
int find_bones(int n,EdgeV& edges,long s,vector<pair<int,long>> &bone_to_tree){
  boost::disjoint_sets_with_storage<> uf(n);
  // ... and process edges in order of increasing length
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end()&&get<2>(*e)<=s; ++e) {
    // determine components of endpoints
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      // this edge connects two different components => part of the emst
      uf.link(c1, c2);
    }
  }
  vector<int> components(n,0);
  for(int i=0;i<bone_to_tree.size();i++){
    if(4*bone_to_tree[i].second<=s){
      components[uf.find_set(bone_to_tree[i].first)]++;
    }else{
      break;
    }
  }
  int max_bones=0;
  for(int i=0;i<n;i++){
    if(components[i]>max_bones){
      max_bones=components[i];
    }
  }
  return max_bones;
}
void solve(){
  int n,m,k;
  long s;
  cin>>n>>m>>s>>k;
  vector<IPoint> trees;
  for(int i=0;i<n;i++){
    int x,y;
    cin>>x>>y;
    trees.push_back(make_pair(P(x,y),i));
  }
  Delaunay t;
  t.insert(trees.begin(), trees.end());
  vector<pair<int,long>> bone_to_tree;
  for(int i=0;i<m;i++){
    int x,y;
    cin>>x>>y;
    P bone=P(x,y);
    int tree_index=t.nearest_vertex(bone)->info();
    long dis=CGAL::squared_distance(trees[tree_index].first,bone);
    bone_to_tree.push_back(make_pair(tree_index,dis));
  }
  std::sort(bone_to_tree.begin(), bone_to_tree.end(),
      [](const pair<int,long>& e1, const pair<int,long>& e2) -> bool {
        return std::get<1>(e1) < std::get<1>(e2);
            });
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
  int res_1=find_bones(n,edges,s,bone_to_tree);
  long l=0;
  long u=LONG_MAX;
  while(l<u){
    long mid=(l+u)/2;
    if(find_bones(n,edges,mid,bone_to_tree)<k){
      l=mid+1;
    }else{
      u=mid;
    }
  }
  cout<<res_1<<" "<<u<<endl;
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
// #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// #include <CGAL/Delaunay_triangulation_2.h>
// #include <CGAL/Triangulation_vertex_base_with_info_2.h>
// #include <CGAL/Triangulation_face_base_2.h>
// #include <boost/pending/disjoint_sets.hpp>
// typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// // we want to store an index with each vertex
// typedef std::size_t                                            Index;
// typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
// typedef CGAL::Triangulation_face_base_2<K>                     Fb;
// typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
// typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
// typedef std::pair<K::Point_2,Index> IPoint;
// typedef K::Point_2 P;
// typedef std::tuple<Index,Index,K::FT> Edge;
// typedef std::vector<Edge> EdgeV;
// #include<vector>
// using namespace std;
// int cal(long s,int n,int m,EdgeV edges,vector<pair<int,long>> bone_tree_dis){
//   boost::disjoint_sets_with_storage<> uf(n);
//   // ... and process edges in order of increasing length
//   for (EdgeV::const_iterator e = edges.begin(); e != edges.end() && get<2>(*e) <= s; ++e) {
//     // determine components of endpoints
//     Index c1 = uf.find_set(get<0>(*e));
//     Index c2 = uf.find_set(get<1>(*e));
//     if (c1 != c2 ) {
//       // this edge connects two different components => part of the emst
//       uf.link(c1, c2);
//     }
//   }
//   vector<int> counts(n,0);
//   for(int i=0;i<m;i++){
//     if(bone_tree_dis[i].second*4<=s){
//       counts[uf.find_set(bone_tree_dis[i].first)]++;
//     }else{
//       break;
//     }
//   }
//   int max=0;
//   for(int i=0;i<n;i++){
//     if(max<counts[i]){
//       max=counts[i];
//     }
//   }
//   return max;
// }

// void solve(){
//   int n,m,k;
//   long s;
//   cin>>n>>m>>s>>k;
//   vector<IPoint> trees;
//   vector<long> diss;
//   for(int i=0;i<n;i++){
//     int x, y;
//     std::cin >> x >> y;
//     trees.emplace_back(K::Point_2(x, y), i);
//   }
//   Delaunay tri;
//   tri.insert(trees.begin(), trees.end());
//   EdgeV edges;
//   edges.reserve(3*n); // there can be no more in a planar graph
//   for (auto e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e) {
//     Index i1 = e->first->vertex((e->second+1)%3)->info();
//     Index i2 = e->first->vertex((e->second+2)%3)->info();
//     // ensure smaller index comes first
//     if (i1 > i2) std::swap(i1, i2);
//     edges.emplace_back(i1, i2, tri.segment(e).squared_length());
//     diss.push_back(tri.segment(e).squared_length());
//   }
//   std::sort(edges.begin(), edges.end(),
//       [](const Edge& e1, const Edge& e2) -> bool {
//         return std::get<2>(e1) < std::get<2>(e2);
//             });
//   vector<pair<int,long>> bone_tree_dis;
//   for(int i=0;i<m;i++){
//     int x, y;
//     std::cin >> x >> y;
//     P tmp=P(x,y);
//     int idx=tri.nearest_vertex(tmp)->info();
//     long dis=CGAL::squared_distance(trees[idx].first,tmp);
//     bone_tree_dis.push_back(make_pair(idx,dis));
//     diss.push_back(dis*4);
//   }
//   std::sort(bone_tree_dis.begin(), bone_tree_dis.end(),
//       [](const pair<int,long>& e1, const pair<int,long>& e2) -> bool {
//         return e1.second < e2.second;
//             });
//   sort(diss.begin(),diss.end());
//   int res_1 = cal(s, n, m, edges, bone_tree_dis);
  
//   // int res_2 = 0;
//   // for(auto d:diss){
//   //   int tmp_res = cal(d, n, m, edges, bone_tree_dis);
//   //   if(tmp_res>=k){
//   //     res_2=d;
//   //     break;
//   //   }
//   // }
//   // cout<<res_1<<" "<<res_2<<endl;
  
//   long upper=LONG_MAX;
//   long lower=0;
//   while(upper>lower){
//     long tmp_s=(upper+lower)/2;
//     int tmp_res = cal(tmp_s, n, m, edges, bone_tree_dis);
//     if(tmp_res>=k){
//       upper=tmp_s;
//     }else{
//       lower=tmp_s+1;
//     }
//   }
//   cout<<res_1<<" "<<upper<<endl;
  
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