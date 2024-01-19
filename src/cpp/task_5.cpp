#include <iostream>
#include <vector>
#include <algorithm>

bool hasZeroSumTriplet(const std::vector<int>& nums) {
    int n = nums.size();
    if (n < 3) {
        return false;  // There must be at least three numbers
    }

    std::sort(nums.begin(), nums.end());  // Sort the array

    for (int i = 0; i < n - 2; ++i) {
        int left = i + 1;
        int right = n - 1;
        int targetSum = -nums[i];  // To find a triplet whose sum is zero, we look for the opposite of the current element

        while (left < right) {
            int currentSum = nums[left] + nums[right];

            if (currentSum == targetSum) {
                // Triplet found
                return true;
            } else if (currentSum < targetSum) {
                // Move left pointer to increase the sum
                ++left;
            } else {
                // Move right pointer to decrease the sum
                --right;
            }
        }
    }

    return false;  // No distinct triplet with zero sum found
}

int main() {
    // Sample input
    std::vector<int> nums = {-5, -17, 7, -4, 3, -2, 4};

    // Check if there exists a distinct triplet whose sum equals zero
    bool result = hasZeroSumTriplet(nums);

    // Output the result
    std::cout << (result ? "True" : "False") << std::endl;

    return 0;
}
