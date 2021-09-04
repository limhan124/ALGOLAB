#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;
using namespace std;
struct pair_sorter {
  bool operator() (const pair<Triangulation::Face_handle, K::FT> &i, const pair<Triangulation::Face_handle, K::FT> &j) const {
    return i.second>j.second;
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n; cin>>n;
  while(n!=0){
    Triangulation t;
    vector<P> infected(n);
    for(int i=0;i<n;i++){
      int x,y; cin>>x>>y;
      infected[i]=P(x,y);
    }
    t.insert(infected.begin(),infected.end());
    //第二个参数指定内部排序规则，从大到小排序
    //可以有多个相同元素
    multiset<pair<Triangulation::Face_handle, K::FT>, pair_sorter> handles_edges;
    for(Face_handle f=t.all_faces_begin();f!=t.all_faces_end();f++) {
      if(t.is_infinite(f)){
        f->info()= -1;
        for(int i=0;i<3;i++){
          Face_handle ff=f->neighbor(i);
          if(!t.is_infinite(ff)){
            handles_edges.insert({ff,t.segment(f,i).squared_length()});
          }
        }
      }
      f->info()=0;
    }
    //要找到所有能连接上infinite face的finite face在这个路径中最短的距离！
    //对同一个face而言由于second大的在前面排着，所以就不用更换它的info了
    while(handles_edges.size()>0){
      Face_handle f=(*(handles_edges.begin())).first;
      K::FT d=(*(handles_edges.begin())).second;
      handles_edges.erase(handles_edges.begin());
      //之前已经遇到过就直接跳
      if(f->info()!=0) continue;
      //直接板上钉钉
      f->info()=d;
      for(int i=0;i<3;i++) 
        if(!t.is_infinite(f->neighbor(i))&&!f->neighbor(i)->info()) //min是因为要找路径上最窄的地方
          handles_edges.insert({f->neighbor(i),min(d,t.segment(f,i).squared_length())});
    }
    
    int m; cin>>m;
    for(int i=0;i<m;i++){
      int x,y; cin>>x>>y;
      K::FT d; cin>>d;
      P p(x, y);
      Face_handle f=t.locate(p);
      if(CGAL::squared_distance(p,t.nearest_vertex(p)->point())<d){
        cout<<"n";
        continue;
      }
      if(t.is_infinite(f)||f->info()>=4*d){
        cout<<"y";
        continue;
      }else cout<<"n";
    }
    cout<<endl;
    cin>>n;
  }
}