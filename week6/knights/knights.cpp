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
  int m,n,k,c;
  cin>>m>>n>>k>>c;
  graph G(2*n*m);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      int p=i*m+j;
      if(i==0||i==n-1){
        adder.add_edge(p, v_sink, 1);
      }
      if(j==0||j==m-1){
        adder.add_edge(p, v_sink, 1);
      }
      if(j!=0){
        adder.add_edge(p-1, p+n*m, 1);//in-vertex upper layer
        adder.add_edge(p, p-1+n*m, 1);//out-vertex lower layer
      }
      if(i!=0){
        adder.add_edge(p-m, p+n*m, 1);
        adder.add_edge(p, p-m+n*m, 1);
      }
      adder.add_edge(p+n*m, p, c);
    }
  }
  for(int i=0;i<k;i++){
    int x,y; cin>>x>>y;
    int p=y*m+x;
    adder.add_edge(v_source, p+n*m, 1);
  }
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  cout<<flow<<endl;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int c;
  cin>>c;
  for(;c;c--){
    test();
  }
}