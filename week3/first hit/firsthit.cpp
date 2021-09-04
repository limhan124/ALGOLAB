#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef std::result_of<K::Intersect_2(K::Ray_2,K::Segment_2)>::type IT;

// round down to next double (as defined in the tutorial)
double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

// clip/set target of s to o
void shorten_segment(K::Segment_2& s, const IT& o) {
  if (const K::Point_2* p = boost::get<K::Point_2>(&*o))
    s = K::Segment_2(s.source(), *p);
  else if (const K::Segment_2* t = boost::get<K::Segment_2>(&*o))
  // select endpoint of *t closer to s.source()
    if (CGAL::collinear_are_ordered_along_line(s.source(), t->source(), t->target()))
      s = K::Segment_2(s.source(), t->source());
    else
      s = K::Segment_2(s.source(), t->target());
  else
    throw std::runtime_error("Strange␣segment␣intersection.");
}

void find_hit(std::size_t n) {
  // read input
  long x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  K::Ray_2 r(K::Point_2(x1, y1), K::Point_2(x2, y2));
  std::vector<K::Segment_2> segs;
  segs.reserve(n);
  for (std::size_t i = 0; i < n; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    segs.push_back(K::Segment_2(K::Point_2(x1,y1), K::Point_2(x2,y2)));
  }
  std::random_shuffle(segs.begin(), segs.end());

 // clip the ray at each segment hit (cuts down on the number of intersection
 // points to be constructed: for a uniformly random order of segments, the
 // expected number of constructions is logarithmic in the number of segments
 // that intersect the initial ray.)
  K::Segment_2 rc(r.source(), r.point(1));

 // find some segment hit by r
  std::size_t i = 0;
  for (; i < n; ++i)
    if (CGAL::do_intersect(segs[i], r)) {
      shorten_segment(rc, CGAL::intersection(segs[i], r));
    break;
  }
  if (i == n) { std::cout << "no\n"; return; }
  // check remaining segments against rc
  while (++i < n)
    if (CGAL::do_intersect(segs[i], rc))
      shorten_segment(rc, CGAL::intersection(segs[i], r)); // not rc!

    std::cout << floor_to_double(rc.target().x()) << " "<< floor_to_double(rc.target().y()) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  for (std::size_t n; std::cin >> n && n > 0;)
    find_hit(n);
}
// #include<iostream>
// #include<climits>
// #include<CGAL/Exact_predicates_exact_constructions_kernel.h>
// typedef CGAL::Exact_predicates_exact_constructions_kernel K;
// typedef K::Point_2 P;
// typedef K::Segment_2 S;
// typedef K::Ray_2 R;
// using namespace std;

// double floor_to_double(const K::FT& x)
// {
//   double a = std::floor(CGAL::to_double(x));
//   while (a > x) a -= 1;
//   while (a+1 <= x) a += 1;
//   return a;
// }
// void findMin(K::FT& res_x,K::FT& res_y,P p,bool larger){
//   if(larger && p.x()<res_x){
//     res_x=p.x();
//     res_y=p.y();
//   }
//   if(!larger && p.x()>res_x){
//     res_x=p.x();
//     res_y=p.y();
//   }
// }

// int main(){
//   std::ios_base::sync_with_stdio(false);
//   int segs;
//   cin>>segs;
//   while(segs!=0){
//     bool hit=false;
//     long x,y,a,b;
//     cin>>x>>y>>a>>b;
//     bool larger=false;
//     if(a-x>0){
//       larger=true;
//     }
//     P standP(x,y),casualP(a,b);
//     R ray(standP,casualP);
//     K::FT res_x=LONG_MIN;
//     K::FT res_y=LONG_MIN;
//     if(larger){
//       res_x=LONG_MAX;
//       res_y=LONG_MAX;
//     }
//     for(int i=0;i<segs;i++){
//       long r,s,t,u;
//       cin>>r>>s>>t>>u;
//       P end_1(r,s),end_2(t,u);
//       S seg(end_1,end_2);
//       if(CGAL::do_intersect(ray,seg)){
//         hit=true;
//         auto o = CGAL::intersection(ray,seg);
//         if (const P* op = boost::get<P>(&*o)){
//           findMin(res_x,res_y,*op,larger);
//         }
//         else if (const S* os = boost::get<S>(&*o)){
//           findMin(res_x,res_y,os->source(),larger);
//           findMin(res_x,res_y,os->target(),larger);
//         }
//       }
//     }
//     if(!hit){
//       cout<<"no"<<endl;  
//     }else{
//       // P& p = min_inter.get();
//       cout<<fixed<<setprecision(0)<<floor_to_double(res_x)<<" "<<floor_to_double(res_y)<<endl;
//     }
//     cin>>segs;
//   }
//   return 0;
// }
// #include<iostream>
// #include<climits>
// #include<CGAL/Exact_predicates_exact_constructions_kernel.h>
// typedef CGAL::Exact_predicates_exact_constructions_kernel K;
// typedef K::Point_2 P;
// typedef K::Segment_2 S;
// typedef K::Ray_2 R;
// using namespace std;

// double floor_to_double(const K::FT& x)
// {
//   double a = std::floor(CGAL::to_double(x));
//   while (a > x) a -= 1;
//   while (a+1 <= x) a += 1;
//   return a;
// }

// void replace_min_intersection(boost::optional<P> &curr_min_inter, const P &maybe, const P &standP) {
//     // Compute the distance to the intersection
//     // If it's smaller than the current min dist, then reset the new min_pt
//     if (curr_min_inter) {
//         if (CGAL::has_smaller_distance_to_point(standP, maybe, *curr_min_inter)){
//             curr_min_inter = maybe;
//         }
//     } else {
//         curr_min_inter = maybe;
//     }
// }

// int main(){
//   int segs;
//   cin>>segs;
//   while(segs!=0){
//     // bool larger=false;
//     long x,y,a,b;
//     cin>>x>>y>>a>>b;
    
//     P standP(x,y),casualP(a,b);
//     R ray(standP,casualP);
//     boost::optional<P> min_inter;
//     for(int i=0;i<segs;i++){
//       long r,s,t,u;
//       cin>>r>>s>>t>>u;
//       P end_1(r,s),end_2(t,u);
//       S seg(end_1,end_2);
//       if(CGAL::do_intersect(ray,seg)){
//         auto o = CGAL::intersection(ray,seg);
//         if (const P* op = boost::get<P>(&*o))
//           replace_min_intersection(min_inter,*op,standP);
//         else if (const S* op = boost::get<S>(&*o)){
//           replace_min_intersection(min_inter, op->source(), standP);
//           replace_min_intersection(min_inter, op->target(), standP);
//         }
//       }
//     }
//     if(!min_inter){
//       cout<<"no"<<endl;  
//     }else{
//       P& p = min_inter.get();
//       cout<<fixed << setprecision(0)<<floor_to_double(p.x())<<" "<<floor_to_double(p.y())<<endl;
//     }
//     cin>>segs;
//   }
//   return 0;
// }