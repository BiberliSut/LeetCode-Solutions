class Solution {
public:
    double countTotalHours(vector<int> &arr, int N, int K) {
        double ans = 0.0;
        for(int i = 0; i < N - 1; i++) {
            ans += ceil((double)(1.0*arr[i])/K);
        }
        ans += (1.0*arr[N - 1])/K;
        return ans;
    }
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int N = dist.size();
        int ans = INT_MAX;
        int low = 1;
        int high = 10000000;
        while(low <= high) {
            int mid = low + (high - low)/2;
            double count = countTotalHours(dist, N, mid);
            if(count <= hour) {
                ans = min(ans, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return (ans == INT_MAX ? -1 : ans);
    }
};