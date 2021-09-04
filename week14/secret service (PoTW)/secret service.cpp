#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
using namespace std;
vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}
vector<vertex_desc> maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  return mate_map;
}
bool max_matching(int length,int a,int s,int c,int d,vector<vector<int>> agents_shelf){
  graph G(a+s*c);
  for(int i=0;i<a;i++){
    for(int j=0;j<s;j++){
      if (agents_shelf[i][j] == INT_MAX){
        continue;
      }
      if(agents_shelf[i][j]+d<=length){
        boost::add_edge(i, j+a, G);
      }
      if(c==2){
        if(agents_shelf[i][j]+2*d<=length){
          boost::add_edge(i, j+a+s, G);
        }
      }
    }
  }
  const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();
  vector<vertex_desc> mate_map=maximum_matching(G);
  int count=0;
  for(int i=0;i<a;i++){
    if(mate_map[i]!=NULL_VERTEX){
      count++;
    }
  }
  return count==a;
}
void solve(){
  int n,m,a,s,c,d;
  cin>>n>>m>>a>>s>>c>>d;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  for(int i=0;i<m;i++){
    char w;
    int x,y,z;
    cin>>w>>x>>y>>z;
    if(w=='S'){
      e = boost::add_edge(x, y, G).first; weights[e]=z;
    }else{
      e = boost::add_edge(x, y, G).first; weights[e]=z;
      e = boost::add_edge(y, x, G).first; weights[e]=z;
    }
  }
  vector<vector<int>> agents_dijk(a);
  for(int i=0;i<a;i++){
    int ai;
    cin>>ai;
    agents_dijk[i]=dijkstra_dist(G,ai);
  }
  vector<vector<int>> agents_shelf(a,vector<int>(s));
  for(int i=0;i<s;i++){
    int si;
    cin>>si;
    for(int j=0;j<a;j++){
      agents_shelf[j][i]=agents_dijk[j][si];
    }
  }
  int lower=0;
  int upper=INT_MAX;
  while(lower<upper){
    int mid=lower + (upper-lower)/2;
    if(max_matching(mid,a,s,c,d,agents_shelf)){
      upper=mid;
    }
    else{
      lower=mid+1;
    }
  }
  cout<<lower<<endl;
}
int main(){
  int t=0; cin>>t;
  while(t--){
    solve();
  }
}