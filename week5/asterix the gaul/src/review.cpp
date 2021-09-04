#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<pair<long, long> > VP;

bool compare (pair<long, long> p1, pair<long, long> p2) {
    if (p1.second == p2.second) {
        return p1.first > p2.first;
    } 
    return p1.second < p2.second;
}

bool feasible(long inc, long D, long T, VP movements) {
    for (auto& p : movements) {
        p.first += inc;
    }
    int m = movements.size();
    VP S1 = VP(movements.begin(), movements.begin() + m / 2);
    VP S2 = VP(movements.begin() + m / 2, movements.end());
    int n1 = S1.size();
    int n2 = S2.size();

    // cout << "size: " << S1.size() << " " << S2.size() << endl;

    VP sub_S1, sub_S2;
    for (int s = 0; s < 1<<n1; ++s) { // Iterate through all subsets
        long tot_D = 0, tot_T = 0;
        for (int i = 0; i < n1; ++i) {
            if (s & 1<<i) {
                tot_D += S1[i].first;
                tot_T += S1[i].second;
            }
        }
        sub_S1.push_back(make_pair(tot_D, tot_T));
    }

    for (int s = 0; s < 1<<n2; ++s) { // Iterate through all subsets
        long tot_D = 0, tot_T = 0;
        for (int i = 0; i < n2; ++i) {
            if (s & 1<<i) {
                tot_D += S2[i].first;
                tot_T += S2[i].second;
            }
        }
        sub_S2.push_back(make_pair(tot_D, tot_T));
    }

    // cout << "sub size: " << sub_S1.size() << " " << sub_S2.size() << endl;

    sort(sub_S1.begin(), sub_S1.end(), compare);
    sort(sub_S2.begin(), sub_S2.end(), compare);

    long max_d = 0;
    for (auto& p : sub_S1) {
        if (max_d > p.first) {
            p.first = max_d;
        } else {
            max_d = p.first;
        }
    }

    max_d = 0;
    for (auto& p : sub_S2) {
        if (max_d > p.first) {
            p.first = max_d;
        } else {
            max_d = p.first;
        }
    }

    bool found = false;
    int ind1 = 0, ind2 = sub_S2.size() - 1;
    while (ind1 < sub_S1.size() && ind2 >= 0) {
        long tot_D = sub_S1[ind1].first + sub_S2[ind2].first;
        long tot_T = sub_S1[ind1].second + sub_S2[ind2].second;
        // cout << ind1 << " " << ind2 << " " << tot_D << " " << tot_T << endl;
        if (tot_D >= D) {
            ind2--;
            if (tot_T < T) {
                found = true;
                break;
            }
        } else {
            ind1++;
        }
    }

    return found;
}

void testcase() {
    int n, m;
    long D, T;
    cin >> n >> m >> D >> T;
    VP movements;
    for (int i = 0; i < n; i++) {
        long d, t; cin >> d >> t;
        movements.push_back(make_pair(d, t));
    }
    vector<long> increments;
    increments.push_back(0);
    for (int i = 0; i < m; i++) {
        long s; cin >> s;
        increments.push_back(s);
    }

    int l = 0, r = m;
    while (l < r) {
        int mid = (l + r) / 2;
        long inc = increments[mid];
        if (feasible(inc, D, T, movements)) {
            r = mid;
        } else{
            l = mid + 1;
        }
    }

    if (feasible(increments[l], D, T, movements)) {
        cout << l << endl;
    } else {
        cout << "Panoramix captured" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        testcase();
    }
}