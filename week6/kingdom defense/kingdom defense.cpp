#include<iostream>
#include<vector>
#include<cstring>
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
  int l,q;
  cin>>l>>q;
  graph G(l);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  // vector<int> demands(l);
  // for(int i=0;i<l;i++){
  //   int num_1,num_2;
  //   cin>>num_1>>num_2;
  //   demands[i]=num_2-num_1;
  // }
  // for(int i=0;i<q;i++){
  //   int from,to,min_t,max_t;
  //   cin>>from>>to>>min_t>>max_t;
  //   adder.add_edge(from,to,max_t-min_t);
  //   demands[from]+=min_t;
  //   demands[to]-=min_t;
  // }
  // int total=0;
  // for(int i=0;i<l;i++){
  //   if(demands[i]<0){
  //     adder.add_edge(v_source,i,-demands[i]);
  //   }else{
  //     adder.add_edge(i,v_sink,demands[i]);
  //     total+=demands[i];
  //   }
  // }
  vector<pair<int,int>> soldiers;
  for(int i=0;i<l;i++){
    int num_1,num_2;
    cin>>num_1>>num_2;
    soldiers.push_back(make_pair(num_1,num_2));
  }
  for(int i=0;i<q;i++){
    int from,to,min_t,max_t;
    cin>>from>>to>>min_t>>max_t;
    adder.add_edge(from,to,max_t-min_t);
    soldiers[from].second+=min_t;
    // soldiers[to].first+=min_t;
    soldiers[to].second-=min_t;
  }
  int total=0;
  for(int i=0;i<l;i++){
    if(soldiers[i].second<0){
      adder.add_edge(v_source,i,-soldiers[i].second);
    }
    else{
      adder.add_edge(i,v_sink,soldiers[i].second);
      total+=soldiers[i].second;
    }
    adder.add_edge(v_source,i,soldiers[i].first);
  }
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow==total){
    cout<<"yes"<<endl;
  }else{
    cout<<"no"<<endl;
  }
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int c;
  cin>>c;
  for(;c;c--){
    test();
  }
}