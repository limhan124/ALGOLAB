#include<iostream>
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
typedef traits::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

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
using namespace std;
void solve(){
  int c,g,b,k,a;
  cin>>c>>g>>b>>k>>a;
  graph G(c);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  int max_cases=0;
  for(int i=0;i<g;i++){
    int x,y,d,e;
    cin>>x>>y>>d>>e;
    adder.add_edge(x,y,e,d);
    if(x==k){
      max_cases += e;
    }
  }
  adder.add_edge(v_source, k, max_cases, 0);
  adder.add_edge(a, v_sink, max_cases, 0);
  int max_flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  int l=0;
  int u=max_flow;
  while(l<u){
    int mid=(l+u+1)/2;
    c_map[boost::edge(v_source, k, G).first]=mid;
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
    int cost2 = boost::find_flow_cost(G);
    if(cost2<=b){
      l=mid;
    }else{
      u=mid-1;
    }
  }
  cout<<l<<endl;
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
// #include <boost/graph/adjacency_list.hpp>
// #include <boost/graph/cycle_canceling.hpp>
// #include <boost/graph/push_relabel_max_flow.hpp>
// #include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
// #include <boost/graph/find_flow_cost.hpp>

// // Graph Type with nested interior edge properties for Cost Flow Algorithms
// typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
// typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
//     boost::property<boost::edge_capacity_t, long,
//         boost::property<boost::edge_residual_capacity_t, long,
//             boost::property<boost::edge_reverse_t, traits::edge_descriptor,
//                 boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs
// typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
// typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
// typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
// using namespace std;
// // Custom edge adder class
// class edge_adder {
// graph &G;

// public:
//   explicit edge_adder(graph &G) : G(G) {}
//   edge_desc add_edge(int from, int to, long capacity, long cost) {
//     auto c_map = boost::get(boost::edge_capacity, G);
//     auto r_map = boost::get(boost::edge_reverse, G);
//     auto w_map = boost::get(boost::edge_weight, G); // new!
//     const edge_desc e = boost::add_edge(from, to, G).first;
//     const edge_desc rev_e = boost::add_edge(to, from, G).first;
//     c_map[e] = capacity;
//     c_map[rev_e] = 0; // reverse edge has no capacity!
//     r_map[e] = rev_e;
//     r_map[rev_e] = e;
//     w_map[e] = cost;   // new assign cost
//     w_map[rev_e] = -cost;   // new negative cost
//     return e;
//   }
// };
// int binarySearch(graph &G,int min_flow,int max_flow,int max_cost,edge_desc &source,const vertex_desc &v_source,const vertex_desc &v_sink){
//   int middle_flow=(min_flow+max_flow)/2;
//   auto c_map = boost::get(boost::edge_capacity, G);
//   c_map[source]=middle_flow;
//   boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
//   int cost2 = boost::find_flow_cost(G);
//   if(cost2<max_cost){
//     if(middle_flow == max_flow) return middle_flow;
//     return binarySearch(G,middle_flow+1,max_flow,max_cost,source,v_source,v_sink);
//   }
//   if(cost2>max_cost){
//     if(middle_flow == min_flow) return min_flow-1;
//     return binarySearch(G,min_flow,middle_flow-1,max_cost,source,v_source,v_sink);
//   }
//   return middle_flow;
// }

// void test(){
//   int c,g,b,k,a;
//   cin>>c>>g>>b>>k>>a;
//   graph G(c);
//   edge_adder adder(G);
//   auto c_map = boost::get(boost::edge_capacity, G);
//   auto r_map = boost::get(boost::edge_reverse, G);
//   auto rc_map = boost::get(boost::edge_residual_capacity, G);
//   int maxCases=0;
//   for(int i=0;i<g;i++){
//     int x,y,d,e;
//     cin>>x>>y>>d>>e;
//     adder.add_edge(x,y,e,d);
//     maxCases+=e;
//   }
//   const vertex_desc v_source=boost::add_vertex(G),v_sink=boost::add_vertex(G);
//   edge_desc source=adder.add_edge(v_source,k,maxCases,0);
//   adder.add_edge(a,v_sink,maxCases,0);
//   boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
//   int s_flow = 0;
//   out_edge_it e, eend;
//   for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
//     s_flow += c_map[*e] - rc_map[*e];     
//   }
//   int res=binarySearch(G,0,s_flow,b,source,v_source,v_sink);
//   cout<<res<<endl;
// }
// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int cases; cin>>cases;
//   for(;cases;cases--){
//     test();
//   }
// }