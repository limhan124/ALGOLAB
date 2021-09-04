#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
using namespace std;
// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};
vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}
void solve(){
  int n,m,s,f;
  cin>>n>>m>>s>>f;
  graph G(n);
  auto w_map = boost::get(boost::edge_weight, G); // new!
  auto c_map = boost::get(boost::edge_capacity, G);
  edge_adder adder(G);
  
  weighted_graph G_w(n);
  weight_map weights = boost::get(boost::edge_weight, G_w);
  edge_desc e;
  for(int i=0;i<m;i++){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    e = boost::add_edge(a, b,G_w).first; weights[e]=d;
    adder.add_edge(a, b, c, d);
    e = boost::add_edge(b, a,G_w).first; weights[e]=d;
    adder.add_edge(b, a, c, d);
  }
  vector<int> from_s=dijkstra_dist(G_w,s);
  vector<int> from_f=dijkstra_dist(G_w,f);
  int min_dis=from_s[f];
  auto e_its=boost::edges(G);
  auto e_begin=e_its.first;
  auto e_end=e_its.second;
  for(;e_begin!=e_end;e_begin++){
    if(w_map[*e_begin]+from_s[boost::source(*e_begin,G)]+from_f[boost::target(*e_begin,G)]>min_dis){
      c_map[*e_begin]=0;
    }
  }
  cout<<boost::push_relabel_max_flow(G, s, f)<<endl;
}
int main(){
  int t; cin>>t;
  while(t--){
    solve();
  }
}