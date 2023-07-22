class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        vector<int> result(n, -1);
        set<int> even, odd;
        for (int i = 0; i < n; i++) {
            if (i & 1) {
                odd.insert(i);
            } else {
                even.insert(i);
            }
        }
        result[p] = 0;
        // kaldırılan dugum icin
        odd.erase(p);
        even.erase(p);
        for (int v : banned) {
            odd.erase(v);
            even.erase(v);
        }
        queue<int> q;
        q.push(p);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            // dogru parametreyi secmek icin yap
            set<int> &s = (v + k) & 1 ? even : odd;
            auto it = s.lower_bound(abs(v - k + 1));
            vector<int> temp;
            // ayni paritedeki tum dugumler icin [abs(v - k + 1), (n - 1 - abs(v + k - n)] 
            while (it != s.end() && (*it) <= (n - 1 - abs(v + k - n))) {
                temp.push_back((*it));
                it++;
            }
            for (int t: temp) {
                result[t] = result[v] + 1;
                q.push(t);
                // erisilen dugumu sil
                s.erase(t);
            }
        }
        return result;
    }
};