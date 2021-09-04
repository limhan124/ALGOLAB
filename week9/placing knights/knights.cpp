#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;
// Interior Property Maps
typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  traits::vertex_descriptor vertex_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;
using namespace std;
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};
void test(){
  int n; cin>>n;
  graph G(n*n);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  vector<vector<bool>> ps(n);
  int field=0;
  for(int i=0;i<n;i++){
    ps[i].resize(n);
    for(int j=0;j<n;j++){
      int x; cin>>x;
      if(x==1){
        field++;
        ps[i][j]=true;
        if((i+j)%2==0){
          adder.add_edge(v_source,i*n+j,1);
        }else{
          adder.add_edge(i*n+j,v_sink,1);
        }
      }else{
        ps[i][j]=false;
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(ps[i][j]&&((i+j)%2==0)){
        vector<pair<int,int>> points(8);
        points[0]=make_pair(i-1,j-2);
        points[1]=make_pair(i-1,j+2);
        points[2]=make_pair(i+1,j-2);
        points[3]=make_pair(i+1,j+2);
        points[4]=make_pair(i-2,j-1);
        points[5]=make_pair(i-2,j+1);
        points[6]=make_pair(i+2,j-1);
        points[7]=make_pair(i+2,j+1);
        for(int k=0;k<8;k++){
          if(points[k].first>=0&&points[k].first<n
          &&points[k].second>=0&&points[k].second<n&&ps[points[k].first][points[k].second]){
            adder.add_edge(i*n+j,(points[k].first)*n+(points[k].second),1);
          }
        }
      }
    }
  }
  long flow=push_relabel_max_flow(G,v_source,v_sink);
  cout<<field-flow<<endl;
}
int main() {
  ios_base::sync_with_stdio(false);
  int c;
  cin>>c;
  for(;c;c--){
    test();
  }
  return 0;
}