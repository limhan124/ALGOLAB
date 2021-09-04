#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;
using namespace std;
typedef struct{
  R r;
  int index;
  K::FT slope;
}RR;
//按照y0从高到低排序/降序
bool my_y0(RR r_1,RR r_2){
  return r_1.r.source().y()>r_2.r.source().y();
}
bool my_index(RR r_1,RR r_2){
  return r_1.index<r_2.index;
}
void test(){
  long n; cin>>n;
  vector<RR> rays;
  for(int i=0;i<n;i++){
    long y_0,x_1,y_1; cin>>y_0>>x_1>>y_1;
    RR r;
    r.r=R(P(0,y_0),P(x_1,y_1));
    r.index=i;
    r.slope=K::FT(y_1-y_0)/K::FT(x_1);
    rays.push_back(r);
  }
  sort(rays.begin(),rays.end(),my_y0);
  // K::FT best_slope=rays[0].slope;
  vector<RR> res;
  res.push_back(rays[0]);
  for(int i=1;i<n;i++){
    if(rays[i].slope<=res[res.size()-1].slope){
      res.push_back(rays[i]);
      // best_slope=rays[i].slope;
    }else{
      if(abs(rays[i].slope)<=abs(res[res.size()-1].slope)){
        int start_to_delete=res.size()-1;
        while(start_to_delete>=0 && CGAL::do_intersect(rays[i].r,rays[start_to_delete].r) 
        && abs(rays[i].slope)<=abs(rays[start_to_delete].slope)){
          start_to_delete--;
        }
        res.erase(res.begin()+start_to_delete+1,res.end());
        if(start_to_delete==-1 || rays[i].slope<=rays[start_to_delete].slope){
          res.push_back(rays[i]);
          // best_slope=rays[i].slope;
        }
      }
    }
  }
  sort(res.begin(),res.end(),my_index);
  for(int i=0;i<res.size();i++){
    cout<<res[i].index<<" ";
  }
  cout<<endl;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);
  int c; cin>>c;
  for(;c;c--){
    test();
  }
  return 0;
}
