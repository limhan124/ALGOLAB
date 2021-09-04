#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool mysort_a(const pair<int, int> &i, const pair<int, int> &j) {
    if(i.first == j.first) return i.second < j.second;
    return i.first < j.first;
}

bool mysort_b(const pair<int, int> &i, const pair<int, int> &j) {
    if(i.second == j.second) return i.first < j.first;
    return i.second < j.second;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;

    while(t--) {
        int n, m;
        cin >> n >> m;

        vector<pair<int, int>> jedis_a(n), jedis_b(n);
        pair<int, int> best_seg(0, 1); //best_seg.first is the number of jedi protecting the best_seg.second segment
        for(int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            int incremented_b = b;
            incremented_b == m ? incremented_b = 1 : incremented_b++;
            jedis_a[i] = pair<int, int>(a, b);
            jedis_b[i] = pair<int, int>(a, incremented_b); //jedis_b has every right end-point increased by one, because this wau the segment research will be easier (the right end-point of every jedi will not be covered).
            if(a == 1 || (a >= incremented_b && incremented_b != 1)) best_seg.first++;
        }

        sort(jedis_a.begin(), jedis_a.end(), mysort_a);
        sort(jedis_b.begin(), jedis_b.end(), mysort_b);
        int index_a = 0, index_b = 0;
        while(index_a < n && jedis_a[index_a].first == 1) index_a++;
        while(best_seg.first > 10) {
            if(jedis_a[index_a].first <= jedis_b[index_b].second) {
                best_seg.first++;
                best_seg.second = jedis_a[index_a].first;
                index_a++;
            } else {
                best_seg.first--; //as the right end-point has been incremented, I can already decrease the number of jedis protecting the segment
                best_seg.second = jedis_b[index_b].second;
                index_b++;
            }
        }
        // cout<<index_a<<" "<<index_b<<" "<<best_seg.first<<" "<<best_seg.second<<endl;

        vector<pair<int, int>> jedis, starters;
        starters.push_back(pair<int, int>(-1, -1));
        for(int i = 0; i < n; i++) {
            int new_a = jedis_a[i].first - best_seg.second, new_b = jedis_a[i].second - best_seg.second;
            if(new_a < 1) new_a = m + new_a;
            if(new_b < 1) new_b = m + new_b;
            if(new_a > new_b) {
              starters.push_back(pair<int, int>(new_a, new_b));
              // cout<<m<<" "<<new_a<<" "<<new_b<<endl;
            }
            else jedis.push_back(pair<int, int>(new_a, new_b));
        }
        sort(jedis.begin(), jedis.end(), mysort_b);

        int number_of_jedis = INT32_MIN;
        // cout<<starters.size()<<" "<<best_seg.first<<endl;
        for(int i = 0; i < (int)starters.size(); i++) {
            int counter = 1, max_b = starters[i].first, position = starters[i].second, index = 0;
            //why??????
            //这个是不带自己玩的意思吗？？？？？？？
            if(i == 0) {
                counter = 0;
                max_b = m+1;
                position = 0;
            }
            while(index < (int)jedis.size()) {
                while(index < (int)jedis.size() && jedis[index].first <= position) index++;
                if(index < (int)jedis.size() && jedis[index].second < max_b) {
                    counter++;
                    position = jedis[index].second;
                    index++;
                } else index = (int)jedis.size();
            }
            number_of_jedis = max(number_of_jedis, counter);
        }

        cout << number_of_jedis << "\n";
    }
}
// #include<iostream>
// #include<vector>
// #include<algorithm>
// #include<climits>
// using namespace std;
// bool my_sort(pair<int,int> i,pair<int,int> j){
//   if(i.first == j.first) return i.second < j.second;
//   return i.first < j.first;
// }
// void test(){
//   int n,m; cin>>n>>m;
//   vector<pair<int,int>> js;
//   for(int i=0;i<n;i++){
//     int a,b; cin>>a>>b;
//     js.push_back(make_pair(a,b));
//   }
//   sort(js.begin(),js.end(),my_sort);
//   int start=js[0].first;
//   int prev_end=js[0].second;
//   int end=js[0].second;
//   int res=1;
//   int final_res=0;
//   int again_start=INT_MAX;
//                       // cout<<res<<":"<<0<<" "<<js[0].first<<" "<<js[0].second<<" "<<end<<endl;

//   again:
//   for(int i=1;i<n;i++){
//     if(js[i].first>js[i].second){
//       if(js[i].first>end){
//         if(js[i].second<start){
//           end=js[i].second+m;
//           res++;
//         }else if(js[i].second>=start && (js[i].second<prev_end||js[i].first>again_start)){
//           final_res=max(res,final_res);
//           // cout<<final_res<<endl;
//           res=1;
//           start=1;
//           end=js[i].second;
//           prev_end=end;
//           again_start=js[i].first;
//           // cout<<res<<":"<<i<<" "<<js[i].first<<" "<<js[i].second<<endl;
//           i=1;
//           goto again;
//         }
//       }
//     }else{
//       if(js[i].first>end && js[i].second<again_start){
        
//         end=js[i].second;
//         res++;
//       }else{
//         if(js[i].second<end){
//           end=js[i].second;
//           if(res==1){
//             start=js[i].first;
//             prev_end=js[i].second;
//           }
//                     // cout<<res<<":"<<i<<" "<<js[i].first<<" "<<js[i].second<<" "<<end<<endl;

//         }
//       }
//     }
//   }
//   final_res=max(res,final_res);
//   cout<<final_res<<endl;
// }
// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(0);
//   int  cases;
//   cin>>cases;
//   for(;cases;cases--){
//     test();
//   }
//   return 0;
// }