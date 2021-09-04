#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_capacity_t, long, boost::property<boost::edge_residual_capacity_t, long, boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
using namespace std;
class edge_adder {
  graph &G;
  public:explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;r_map[rev_e] = e;
  }
};
void test(){
  int n,m,k,l; cin>>n>>m>>k>>l;
  graph G(2*n);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  for(int i=0;i<k;i++){
    int tmp; cin>>tmp;
    adder.add_edge(v_source,tmp,1);
    adder.add_edge(tmp+n,v_sink,1);
  }
  for(int i=0;i<l;i++){
    int tmp; cin>>tmp;
    adder.add_edge(tmp,tmp+n,1);
  }
  for(int i=0;i<m;i++){
    int x,y; cin>>x>>y;
    adder.add_edge(x,y,n);
    adder.add_edge(x+n,y+n,1);
  }
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  cout<<flow<<endl;
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