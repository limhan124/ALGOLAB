// ALGOLAB BGL Tutorial 3
// Code demonstrating 
// - MinCostMaxFlow with arbitrary edge costs using cycle_canceling
// - MinCostMaxFlow with non-negative edge costs using successive_shortest_path_nonnegative_weights

// Includes
// ========
#include <iostream>
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
void test(){
  int n,m,s;
  cin>>n>>m>>s;
  // Create graph, edge adder class and propery maps
  graph G(n+m+s);
  edge_adder adder(G);
  const int v_source = boost::add_vertex(G);
  const int v_sink = boost::add_vertex(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  for(int i=0;i<s;i++){
    int x; cin>>x;
    adder.add_edge(i+n+m,v_sink,x,0);
  }
  for(int i=0;i<m;i++){
    int x; cin>>x;
    adder.add_edge(i+n,x-1+n+m,1,0);
  }
  int maxcost=100;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      int x; cin>>x;
      adder.add_edge(i,j+n,1,maxcost-x);
    }
    adder.add_edge(v_source,i,1,0);
    // adder.add_edge(i,v_sink,1,maxcost);
  }
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost2 = boost::find_flow_cost(G);
  int s_flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
    s_flow += c_map[*e] - rc_map[*e];     
  }
  cout<<s_flow<<" "<<s_flow*maxcost-cost2<<endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  int c;
  cin >>c;
  for(;c;c--){
    test();
  }
  return 0;
}  
