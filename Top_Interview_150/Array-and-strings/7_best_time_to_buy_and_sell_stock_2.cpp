#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int solve(int index, int canBuy, vector<int>& prices) {
        if (index == prices.size()) 
            return 0;

        int profit = 0;

        // If we are allowed to buy
        if (canBuy) {
            int buy = -prices[index] + solve(index + 1, 0, prices);
            int skip = solve(index + 1, 1, prices);
            profit = max(buy, skip);
        } 
        // If we are currently holding stock -> we can sell
        else {
            int sell = prices[index] + solve(index + 1, 1, prices);
            int skip = solve(index + 1, 0, prices);
            profit = max(sell, skip);
        }

        return profit;
    }
    int calculateMaxProfit(int dayIndex, int holdingStock,
                           vector<int>& stockPrices,
                           vector<vector<int>>& memo) {
        if (dayIndex == stockPrices.size()) return 0;

        if (memo[dayIndex][holdingStock] != -1)
            return memo[dayIndex][holdingStock];

        int maxProfit = 0;

        if (holdingStock == 1) {
            // Option 1: Buy
            // Option 2: Skip
            maxProfit = max(-stockPrices[dayIndex] +
                                calculateMaxProfit(dayIndex + 1, 0, stockPrices, memo),
                            0 + calculateMaxProfit(dayIndex + 1, 1, stockPrices, memo));
        } else {
            // holdingStock == 0 → already bought, so either sell or hold
            maxProfit = max(stockPrices[dayIndex] +
                                calculateMaxProfit(dayIndex + 1, 1, stockPrices, memo),
                            0 + calculateMaxProfit(dayIndex + 1, 0, stockPrices, memo));
        }

        return memo[dayIndex][holdingStock] = maxProfit;
    }

    int calculateMaxProfitUsingTabulation(vector<int>& stockPrices) {
        int n = stockPrices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));

        dp[n][0] = 0;
        dp[n][1] = 0;

        for (int i = n - 1; i >= 0; i--) {
            for (int holding = 0; holding <= 1; holding++) {
                int maxProfit = 0;

                if (holding == 1) {
                    maxProfit = max(-stockPrices[i] + dp[i + 1][0],
                                    0 + dp[i + 1][1]);
                } else {
                    maxProfit = max(stockPrices[i] + dp[i + 1][1],
                                    0 + dp[i + 1][0]);
                }

                dp[i][holding] = maxProfit;
            }
        }

        return dp[0][1];
    }

    int spaceOptimized(vector<int>& stockPrices) {
        int n = stockPrices.size();
        vector<int> next(2, 0), curr(2, 0);

        for (int i = n - 1; i >= 0; i--) {
            for (int holding = 0; holding <= 1; holding++) {
                int maxProfit = 0;

                if (holding == 1) {
                    maxProfit = max(-stockPrices[i] + next[0],
                                    0 + next[1]);
                } else {
                    maxProfit = max(stockPrices[i] + next[1],
                                    0 + next[0]);
                }

                curr[holding] = maxProfit;
            }
            next = curr;
        }

        return curr[1];
    }

    int maxProfit(vector<int>& stockPrices) {
        int n = stockPrices.size();
        vector<vector<int>> memo(n + 1, vector<int>(2, -1));

        return calculateMaxProfit(0, 1, stockPrices, memo);
    }
};
