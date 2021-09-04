#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
//face with bottleneck
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;
typedef std::pair<K::FT,Triangulation::Face_handle> bottleneck_handle;
typedef K::Point_2 P;
typedef K::FT FT;
using namespace std;
struct cmp{
  bool operator()(bottleneck_handle a, bottleneck_handle b){
    return a.first<b.first;
  }
};
FT max_value = FT(numeric_limits<long>::max()) * FT(numeric_limits<long>::max());

void fill_tri(Triangulation &tri){
  priority_queue<bottleneck_handle,vector<bottleneck_handle>,cmp> que;
  for (auto f = tri.all_faces_begin(); f != tri.all_faces_end(); ++f){
    if(tri.is_infinite(f)){
      que.emplace(max_value,f);
    }else{
      K::FT face_len_squared = CGAL::squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point());
      que.emplace(face_len_squared, f);
    }
  }
  while(!que.empty()){
    bottleneck_handle tmp=que.top();
    que.pop();
    if(tmp.second->info()!=0){
      continue;
    }
    tmp.second->info()=tmp.first;
    for(int i=0;i<3;i++){
      auto neighbor=tmp.second->neighbor(i);
      if(tri.is_infinite(neighbor)||neighbor->info()!=0){
        continue;
      }else{
        K::FT edge_length=CGAL::squared_distance(tmp.second->vertex((i+1)%3)->point(),tmp.second->vertex((i+2)%3)->point());
        que.emplace(min(edge_length,tmp.first), neighbor);
      }
    }
  }
}

void solve(){
  int n,m;
  long r;
  cin>>n>>m>>r;
  vector<P> trees;
  for(int i=0;i<n;i++){
    long x,y;
    cin>>x>>y;
    trees.push_back(P(x,y));
  }
  Triangulation tri;
  tri.insert(trees.begin(),trees.end());
  fill_tri(tri);
  for(int i=0;i<m;i++){
    long x,y,s;
    cin>>x>>y>>s;
    P center = P(x,y);
    K::FT min_distance_from_center = (K::FT(r) + K::FT(s)) * (K::FT(r) + K::FT(s));
    //无法充气
    if(CGAL::squared_distance(tri.nearest_vertex(center)->point(),center)<min_distance_from_center){
      cout<<"n";
    }else{
      //可以移动到合适点
      if(4*min_distance_from_center<=tri.locate(center)->info()){
        cout<<"y";
      }else{
        cout<<"n";
      }
    }
  }
  cout<<endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t; cin>>t;
  while(t--){
    solve();
  }
}
