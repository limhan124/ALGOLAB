#include<iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_weight_t, int>
                              > weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
using namespace std;
int dijkstra_dist(int n,const weighted_graph &G,int s,int t) {
  vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G,s,
                        boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
                        boost::get(boost::vertex_index, G))));
  return dist_map[t];
}
void kruskal(weighted_graph G,weight_map W,weighted_graph &finalG,weight_map &weights){
  std::vector<edge_desc> mst; // vector to store MST edges (not a property map!)
  boost::kruskal_minimum_spanning_tree(G,back_inserter(mst));
  
  for(vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it){
    auto e=boost::add_edge(boost::source(*it,G),boost::target(*it,G),finalG).first;
    weights[e]=W[*it];
  }
}

void test(){
  int n,e,s,a,b;
  cin>>n>>e>>s>>a>>b;
  vector<weighted_graph> Gs(s, weighted_graph(n));
  vector<weight_map> Ws(s);
  for(int i=0;i<s;i++) {
    Ws[i] = boost::get(boost::edge_weight,Gs[i]);
  }
  for(int i=0;i<e;i++){
    int v_1,v_2;
    cin>>v_1>>v_2;
    for(int j=0;j<s;j++){
      int weight; cin>>weight;
      auto e = boost::add_edge(v_1,v_2,Gs[j]).first;
      Ws[j][e]=weight;
    }
  }
  weighted_graph finalG(n);
  weight_map weights=boost::get(boost::edge_weight, finalG);
  for(int i=0;i<s;i++){
    int hive;
    cin>>hive;
    kruskal(Gs[i],Ws[i],finalG,weights);
  }
  cout<<dijkstra_dist(n,finalG,a,b)<<endl;
}
int main(){
  int cases; cin>>cases;
  for(;cases;cases--){
    test();
  }
}