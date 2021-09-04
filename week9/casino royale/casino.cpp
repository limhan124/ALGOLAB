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
typedef boost::graph_traits<graph>::edge_iterator EdgeIt;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
using namespace std;
// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  edge_desc add_edge(int from, int to, long capacity, long cost) {
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
    return e;
  }
};
void test(){
  int n,m,l;
  cin>>n>>m>>l;
  // Create graph, edge adder class and propery maps
  graph G(n);
  edge_adder adder(G);
  const int v_source = boost::add_vertex(G);
  //把最后一个点看作v_sink
  // const int v_sink = boost::add_vertex(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  //从源头控制最多有l个任务
  adder.add_edge(v_source,0,l,0);
  int maxcost=128;
  for(int i=0;i<n-1;i++){
    adder.add_edge(i,i+1,l,maxcost);
  }
  map<edge_desc,int> cost_map;
  for(int i=0;i<m;i++){
    int x,y,q; cin>>x>>y>>q;
    //！！！！！！！！！！！！！！！！！！！
    //这里竟然还考虑了长度的影响，经过的站越多代价越大!
    edge_desc e=adder.add_edge(x,y,1,maxcost*(y-x)-q);
    cost_map.insert(make_pair(e,q));
  }
  boost::successive_shortest_path_nonnegative_weights(G, v_source, n-1);
  int cost2 = boost::find_flow_cost(G);
  int cost=0;
  EdgeIt e, e_end;
  for (tie(e, e_end) = edges(G); e != e_end; ++e) {
    long flow = c_map[*e] - rc_map[*e];
    // cout<<flow<<endl;
    if (flow == 1) {
      cost += cost_map[*e];
    }
  }
  cout << cost << endl;
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
