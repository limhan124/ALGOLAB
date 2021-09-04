#include<iostream>
#include<vector>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Line_2 L;
typedef K::Segment_2 S;
void test(){
  int m,n;
  cin>>m>>n;
  vector<P> points;
  for(int i=0;i<m;i++){
    int x,y;
    cin>>x>>y;
    points.push_back(P(x,y));
  }
  vector<S> legs;
  for(int i=0;i<m-1;i++){
    legs.push_back(S(points[i],points[i+1]));
  }
  vector<S> segs;
  vector<vector<int>> insides(n);
  for(int i=0;i<3*n;i++){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    segs.push_back(S(P(a,b),P(c,d)));
    if((i+1)%3==0){
      vector<bool> turnR(3,false);
      for(int j=2;j>=0;j--){
        P p1,p2,p3;
        p1=segs[i-j].source();
        p2=segs[i-j].target();
        if(j==0){
          p3=segs[i-2].source();
        }else{
          p3=segs[i-j+1].source();
        }
        // p3=segs[(i-j+1)%3].source();
        if(CGAL::right_turn(p1,p2,p3)){
          turnR[2-j]=true;
        }
      }
      for(int j=0;j<m-1;j++){
        P p1,p2;
        p1=legs[j].source();
        p2=legs[j].target();
        bool inside=true;
        for(int k=0;k<3;k++){
          P p3,p4;
          p3=segs[i-2+k].source();
          p4=segs[i-2+k].target();
          
          if((CGAL::right_turn(p3,p4,p1)!=turnR[k])&&(!CGAL::collinear(p3,p4,p1)) || 
             (CGAL::right_turn(p3,p4,p2)!=turnR[k])&&(!CGAL::collinear(p3,p4,p2))){
            inside=false;
            break;
          }
        }
        if(inside){
          insides[(i-2)/3].push_back(j);
          // cout<<j<<" ";
        }
      }
      // cout<<endl;
    }
  }
  int left=0;
  int right=0;
  int ans=n;
  vector<int> contains(m-1,0);
  for(int i=0;i<insides[0].size();i++){
    contains[insides[0][i]]++;
  }
  while(left<n){
    if(find(contains.begin(),contains.end(),0)!=contains.end()){
      if(right<n-1){
        right++;
        for(int i=0;i<insides[right].size();i++){
          contains[insides[right][i]]++;
        }
      }else{
        break;
      }
    }else{
      int tmp=right-left+1;
      if(tmp<ans){
        ans=tmp;
        if(ans==1){
          break;
        }
      }
      if(left<right){
        left++;
        for(int i=0;i<insides[left-1].size();i++){
          contains[insides[left-1][i]]--;
        }
      }
    }
  }
  cout<<ans<<endl;
}

int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    test();
  }
  return 0;
}