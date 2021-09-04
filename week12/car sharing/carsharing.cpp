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
struct request{
  int s,t,d,a,p;
};
using namespace std;
void solve(){
  int n,s;
  cin>>n>>s;
  int max_t=100000;
  int max_p=100;
  vector<int> cars(s);
  vector<request> reqs;
  vector<set<int>> times_on_si(s);
  for(int i=0;i<s;i++){
    cin>>cars[i];
    times_on_si[i].insert(0);
    times_on_si[i].insert(max_t);
  }
  for(int i=0;i<n;i++){
    int s,t,d,a,p;
    cin>>s>>t>>d>>a>>p;
    s--; t--;
    reqs.push_back({s,t,d,a,p});
    times_on_si[s].insert(d);
    times_on_si[t].insert(a);
  }
  vector<map<int,int>> time_to_index(s);
  vector<int> prefix(s+1,0);
  int timestamps=0;
  for(int i=0;i<s;i++){
    int count=0;
    for(auto j:times_on_si[i]){
      time_to_index[i][j]=count;
      count++;
    }
    prefix[i+1]=prefix[i]+times_on_si[i].size();
    timestamps+=times_on_si[i].size();
  }
  
  graph G(timestamps);
  edge_adder adder(G);  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
    
  for(int i=0;i<s;i++){
    adder.add_edge(v_source, prefix[i], cars[i], 0);
    int count=0;
    int lastj=0;
    for(auto j:times_on_si[i]){
      if(count){
        int from=prefix[i]+count-1;
        int to=prefix[i]+count;
        int duration=j-lastj;
        adder.add_edge(from, to, INT_MAX, max_p*duration);      
      }
      count++;
      lastj=j;
    }
    adder.add_edge(prefix[i+1]-1, v_sink, INT_MAX, 0);
  }
  for(int i=0;i<n;i++){
    int from=time_to_index[reqs[i].s][reqs[i].d]+prefix[reqs[i].s];
    int to=time_to_index[reqs[i].t][reqs[i].a]+prefix[reqs[i].t];
    int duration=reqs[i].a-reqs[i].d;
    adder.add_edge(from,to,1,max_p*duration-reqs[i].p);
  }
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost2 = boost::find_flow_cost(G);
  int s_flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
    s_flow += c_map[*e] - rc_map[*e];
  }
  cout<<s_flow*max_p*max_t-cost2<<endl;
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
// #include<vector>
// #include<set>
// #include<climits>
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

// typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
// typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// // Custom edge adder class
// class edge_adder {
// graph &G;

// public:
//   explicit edge_adder(graph &G) : G(G) {}
//   void add_edge(int from, int to, long capacity, long cost) {
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
//   }
// };
// struct request{
//   int s,t,d,a,p;
// };

// using namespace std;
// void test(){
//   int n,m; cin>>n>>m;
//   vector<int> cars(m);
//   for(int i=0;i<m;i++){
//     int x; cin>>x;
//     cars[i]=x;
//   }
//   int sum=0;
//   for(int i=0;i<m;i++){
//     sum += cars[i];
//   }

//   vector<request> rs;
//   vector<set<int>> times(m);  //m个station
//   for(int i=0;i<m;i++){
//     times[i].insert(0);
//     times[i].insert(100000);
//   }
//   for(int i=0;i<n;i++){
//     int s,t,d,a,p;
//     cin>>s>>t>>d>>a>>p;
//     s--; t--;
//     times[s].insert(d);
//     times[t].insert(a);
//     rs.push_back({s,t,d,a,p});
//   }
//   vector<map<int,int>> times_to_index(m);
//   vector<int> prefix(m+1,0);
//   for(int i=0;i<m;i++){
//     int index=0;
//     for(auto j:times[i]){
//       times_to_index[i][j]=index;
//       index++;
//     }
//     prefix[i+1]=times[i].size()+prefix[i];
//   }
//   int timestamps=prefix[m];
//   graph G(timestamps);
//   edge_adder adder(G);  
//   auto c_map = boost::get(boost::edge_capacity, G);
//   auto r_map = boost::get(boost::edge_reverse, G);
//   auto rc_map = boost::get(boost::edge_residual_capacity, G);
//   auto v_source=timestamps;
//   auto v_sink=timestamps+1;
//   for(int i=0;i<m;i++){
//     adder.add_edge(v_source,prefix[i],cars[i],0);
//     int count=-1;
//     int lastj=0;
//     int out=times[i].size();
//     for(auto j:times[i]){
//       if(count!=-1){
//         adder.add_edge(prefix[i]+count,count+1+prefix[i],INT_MAX,(j-lastj)*100);
//       }
//       count++;
//       lastj=j;
//     }
//     adder.add_edge(prefix[i+1]-1,v_sink,INT_MAX,0);
//   }
//   for(int i=0;i<n;i++){
//     int tmp=rs[i].a-rs[i].d;
//     adder.add_edge(times_to_index[rs[i].s][rs[i].d]+prefix[rs[i].s],
//     times_to_index[rs[i].t][rs[i].a]+prefix[rs[i].t],
//     1,tmp*100-rs[i].p);
//     // cout<<tmp*100-rs[i].p<<" ";
//   }
//   boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
//   long cost2 = boost::find_flow_cost(G);
//   long s_flow = 0;
//   out_edge_it e, eend;
//   for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
//     s_flow += c_map[*e] - rc_map[*e];     
//   }
//   long res=100000*100*s_flow-cost2;
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