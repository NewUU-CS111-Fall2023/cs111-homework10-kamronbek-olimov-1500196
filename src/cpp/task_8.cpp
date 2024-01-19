#include <iostream>
#include <vector>

using namespace std;

bool canPartition(vector<int>& nums) {
    int totalSum = 0;

    for (int num : nums) {
        totalSum += num;
    }

    // If the total sum is odd, it cannot be partitioned into two equal subsets
    if (totalSum % 2 != 0) {
        return false;
    }

    int targetSum = totalSum / 2;
    int n = nums.size();

    // dp[i][j] represents whether a subset of the first i elements can form a sum of j
    vector<vector<bool>> dp(n + 1, vector<bool>(targetSum + 1, false));

    // Base case: an empty subset can always form a sum of 0
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }

    // Fill the dp table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= targetSum; ++j) {
            dp[i][j] = dp[i - 1][j];

            if (j >= nums[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
            }
        }
    }

    // The answer is in the bottom-right cell of the dp table
    return dp[n][targetSum];
}

int main() {
    // Sample input
    vector<int> nums = {1, 5, 11, 5};

    // Check if it is possible to partition the array into two subsets with equal sum
    bool result = canPartition(nums);

    // Output the result
    cout << (result ? "True" : "False") << endl;

    return 0;
}
