#include<iostream>
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>
#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>
#include<vector>
using namespace std;
typedef CGAL::Exact_predicates_exact_constructions_kernel EK;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;
typedef CGAL::Min_circle_2_traits_2<EK> Traits_E;
typedef CGAL::Min_circle_2_traits_2<SK> Traits_S;
typedef CGAL::Min_circle_2<Traits_E> Min_circle_E;
typedef CGAL::Min_circle_2<Traits_S> Min_circle_S;
typedef EK::Point_2 P_E;
typedef SK::Point_2 P_S;
double ceil_to_double(const SK::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}
void test(int n)
{
  vector<P_S> points;
  for(int i=0;i<n;i++){
    long p_x,p_y;
    cin>>p_x>>p_y;
    P_S tmpP(p_x,p_y);
    points.push_back(tmpP);
  }
  Min_circle_S mc(points.begin(), points.end(), true);//乱序
  cout<<fixed<<setprecision(0)<<ceil_to_double(CGAL::sqrt(mc.circle().squared_radius()))<<endl;
}
double ceil_to_double2(const EK::FT& x)
{
  double a = std::ceil(std::sqrt(CGAL::to_double(x)));
  while (a*a<x) a+=1;
  while ((a-1)*(a-1)>=x) a-=1;
  return a;
}
void test2(int n)
{
  vector<P_E> points;
  for(int i=0;i<n;i++){
    long p_x,p_y;
    cin>>p_x>>p_y;
    P_E tmpP(p_x,p_y);
    points.push_back(tmpP);
  }
  Min_circle_E mc(points.begin(), points.end(), true);//乱序
  cout<<fixed<<setprecision(0)<<ceil_to_double2(mc.circle().squared_radius())<<endl;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int n;
  cin>>n;
  while(n!=0){
    if(n<100000){
      test(n);
    }else{
      test2(n);
    }
    cin>>n;    
  }
}