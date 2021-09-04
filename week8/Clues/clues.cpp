#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
//pair<components,frequency>
typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int,bool>,K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 P;
using namespace std;
bool inside(Triangulation &tri,long r2){
  for(auto e=tri.finite_edges_begin();e!=tri.finite_edges_end();e++){
    if(tri.segment(e).squared_length()<=r2){
      return false;
    }
  }
  return true;
}
bool doable(Triangulation &tri,long r2){
  vector<P> points1,points2;
  Triangulation tri1,tri2;
  int components=-1;
  for(auto v=tri.finite_vertices_begin();v!=tri.finite_vertices_end();v++){
    //not decided
    if(v->info().first==-1){
      v->info()=make_pair(++components,false);
      //BFS宽度优先算法
      //FIFO
      queue<Triangulation::Vertex_handle> vexQueue;
      vexQueue.push(v);
      do{
        //vex is decided
        Triangulation::Vertex_handle vex=vexQueue.front();
        vexQueue.pop();
        Triangulation::Vertex_circulator c=tri.incident_vertices(vex);
        if(c!=0) do{
          if(!tri.is_infinite(c)&&CGAL::squared_distance(c->point(),vex->point())<=r2){
            // if(c->info()==vex->info()){
            //   return false;
            // }
            //not decided
            if(c->info().first==-1){
              vexQueue.push(c->handle());
              c->info()=make_pair(components,!vex->info().second);
            }
          }
        }while(++c!=tri.incident_vertices(vex));
      }while(!vexQueue.empty());
    }
    if(v->info().second){
      // cout<<v->info().first<<" ";
      points1.push_back(v->point());
    }else{
      // cout<<v->info().first<<" ";
      points2.push_back(v->point());
    }
  }
  tri1.insert(points1.begin(), points1.end());
  tri2.insert(points2.begin(), points2.end());
  return inside(tri1,r2) && inside(tri2,r2);
  // return true;
}

void test(){
  long n,m,r;
  cin>>n>>m>>r;
  long r2=r*r;
  Triangulation tri;
  vector<pair<P,pair<int,bool>>> stations(n);
  for(int i=0;i<n;i++){
    int x,y; cin>>x>>y;
    stations[i]=make_pair(P(x,y),make_pair(-1,false));
    //-1 means not decided
  }
  tri.insert(stations.begin(),stations.end());
  bool can=doable(tri,r2);
  if(can){
    for(int i=0;i<m;i++){
      P H,W;
      cin>>H>>W;
      if(CGAL::squared_distance(H,W)<=r2){cout<<"y";}
      else{
        Triangulation::Vertex_handle p_1=tri.nearest_vertex(H);
        Triangulation::Vertex_handle p_2=tri.nearest_vertex(W);
        if(CGAL::squared_distance(p_1->point(),H)>r2 ||
          CGAL::squared_distance(p_2->point(),W)>r2){
          cout<<"n";
        }
        else if(p_1->info().first==p_2->info().first){
          cout<<"y";
        }
        else{
          cout<<"n";
        }
      }
    }
  }else{
    for(int i=0;i<m;i++){
      P H,W;
      cin>>H>>W;
      cout<<"n";
    }
  }
  cout<<endl;
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

// #include<iostream>
// #include<vector>
// #include<queue>
// #include<algorithm>
// #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// #include <CGAL/Triangulation_vertex_base_with_info_2.h>
// #include <CGAL/Triangulation_face_base_2.h>
// #include <CGAL/Delaunay_triangulation_2.h>
// #include<boost/graph/adjacency_list.hpp>
// #include<boost/graph/connected_components.hpp>
// typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,boost::no_property,boost::no_property> Graph;
// typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
// //pair<component,frequency>
// typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int,bool>,K>     Vb;
// typedef CGAL::Triangulation_face_base_2<K>                     Fb;
// typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
// typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
// typedef K::Point_2 P;
// typedef Triangulation::Finite_faces_iterator Face_iterator;
// using namespace std;
// void test(){
//   int n,m,r;
//   cin>>n>>m>>r;
//   long r2=r*r;
//   Triangulation tri;
//   vector<pair<P,pair<int,bool>>> stations(n);
//   for(int i=0;i<n;i++){
//     int x,y; cin>>x>>y;
//     stations[i]=make_pair(P(x,y),make_pair(-1,false));
//   }
//   tri.insert(stations.begin(), stations.end());
//   Graph G(n);
//   vector<bool> colored(n,false);
//   int doable=true;
//   for(auto e=tri.finite_edges_begin();e!=tri.finite_edges_end(); ++e){
//     if(tri.segment(e).squared_length()<=r2){
//       pair<int,bool> p1=e->first->vertex((e->second+1)%3)->info();
//       pair<int,bool> p2=e->first->vertex((e->second+2)%3)->info();
//       boost::add_edge(p1.first,p2.first,G);
//       if(!colored[p1.first]&&!colored[p2.first]){
//         //p1、p2 not changed
//         e->first->vertex((e->second+1)%3)->info().second=false;
//         e->first->vertex((e->second+2)%3)->info().second=true;
//         colored[p1.first]=true;
//         colored[p2.first]=true;
//       }else if(!colored[p1.first]){
//         e->first->vertex((e->second+1)%3)->info().second=!p2.second;
//         colored[p1.first]=true;
//       }else if(!colored[p2.first]){
//         e->first->vertex((e->second+2)%3)->info().second=!p1.second;
//         colored[p2.first]=true;
//       }else{
//         if(p1.second==p2.second){
//           // cout<<p1.second<<" "<<p2.second<<" "<<e->first->vertex((e->second+1)%3)->point()<<" "<<e->first->vertex((e->second+2)%3)->point()<<endl;
//           doable=false;
//           break;
//         }else{
//           continue;
//         }
//       } 
//     }
//   }

// for(int i=0;i<m;i++) {
//     P H,W;
//     cin>>H>>W;
//     if(!network) cout<<"n";
//     else{
//       Triangulation::Vertex_handle v1=tri.nearest_vertex(H),v2=tri.nearest_vertex(W);
//       if(CGAL::squared_distance(H,W)<=r2||
//         (v1->info().first==v2->info().first && 
//         CGAL::squared_distance(v1->point(),H)<=r2 &&
//         CGAL::squared_distance(v2->point(),W)<=r2)) cout<<"y";
//       else cout << "n";
//     }
//   }
//   cout<<endl;

//   vector<int> scc_map(n);
//   int nscc=boost::connected_components(G,boost::make_iterator_property_map(scc_map.begin(),boost::get(boost::vertex_index, G)));
//   if(doable){
//     vector<int> scc_map(n);
//     boost::connected_components(G,boost::make_iterator_property_map(scc_map.begin(),boost::get(boost::vertex_index, G)));
//     for(int i=0;i<m;i++){
//       P H,W;
//       cin>>H>>W;
//       if(CGAL::squared_distance(H,W)<=r2){cout<<"y";}
//       else{
//         Triangulation::Vertex_handle p_1=tri.nearest_vertex(H);
//         Triangulation::Vertex_handle p_2=tri.nearest_vertex(W);
//         if(CGAL::squared_distance(p_1->point(),H)>r2 ||
//           CGAL::squared_distance(p_2->point(),W)>r2){
//           cout<<"n";
//         }
//         else if(scc_map[p_1->info().first]==scc_map[p_2->info().first]){
//           cout<<"y";
//         }
//         else{
//           cout<<"n";
//         }
//       }
//     }
//   }else{
//     for(int i=0;i<m;i++){
//       P H,W;
//       cin>>H>>W;
//       cout<<"n";
//     }
//   }
//   cout<<endl;
// }
// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int c; cin>>c;
//   for(;c;c--){
//     test();
//   }
//   return 0;
// }