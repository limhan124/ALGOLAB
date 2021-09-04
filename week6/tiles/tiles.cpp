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
  int w,h;
  cin>>w>>h;
  graph G(w*h);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  vector<string> ss(h);
  for(int i=0;i<h;i++){
    cin>>ss[i];
  }
  int count=0;
  for(int i=0;i<ss.size();i++){
    for(int j=0;j<ss[i].size();j++){
      if(ss[i][j]=='.'){
        count++;
        //白色！
        int p=i*w+j;
        if((i%2)==(j%2)){
          adder.add_edge(v_source, p, 1);
          // cout<<"white"<<" ";
          //向上
          if(i!=0){
            if(ss[i-1][j]=='.'){
              adder.add_edge(p, p-w, 1);
            }
          }
          if(j!=0){
            if(ss[i][j-1]=='.'){
              adder.add_edge(p, p-1, 1);
            }
          }
          if(i!=h-1){
            if(ss[i+1][j]=='.'){
              adder.add_edge(p, p+w, 1);
            }  
          }
          if(j!=w-1){
            if(ss[i][j+1]=='.'){
              adder.add_edge(p, p+1, 1);
            }
          }
        }else{
          adder.add_edge(p, v_sink, 1);
          // cout<<"black"<<" ";
        }
        
      }
    }
  }
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow*2==count){
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