#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int maxProfit1(vector<int>& prices) {
        int n = prices.size();
        if(n == 0) return 0;

        int maxPft = INT_MIN;
        for(int i = 0 ; i < n ; i++){
            for(int  j = i + 1; j < n ; j++){
                if(maxPft < (prices[j]-prices[i])) maxPft = (prices[j]-prices[i]);
            }
        }
        return (maxPft < 0 ? 0 : maxPft);
    }
    int maxProfit2(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        vector<int> mini(n);
        vector<int> maxi(n);

        mini[0] = prices[0];
        maxi[n - 1] = prices[n - 1];

        // Fill the mini array with minimum prices from the start
        for (int i = 1; i < n; i++) {
            mini[i] = min(mini[i - 1], prices[i]);
        }

        // Fill the maxi array with maximum prices from the end
        for (int i = n - 2; i >= 0; i--) {
            maxi[i] = max(maxi[i + 1], prices[i]);
        }

        int profit = 0;
        // Calculate the maximum profit
        for (int i = 0; i < n; i++) {
            profit = max(profit, maxi[i] - mini[i]);
        }

        return profit;
    }
    int maxProfit3(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        int mini = prices[0];
        int profit = 0;

        for (int i = 1; i < n; i++) {
            int cost = prices[i] - mini;
            profit = max(profit, cost);
            mini = min(prices[i], mini);
        }

        return profit;
    }

};