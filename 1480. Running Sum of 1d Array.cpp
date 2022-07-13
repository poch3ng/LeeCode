// Runtime: 3 ms, faster than 79.12% of C++ online submissions for Running Sum of 1d Array.
// Memory Usage: 8.6 MB, less than 34.90% of C++ online submissions for Running Sum of 1d Array.

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> ans;
        int temp = 0;
        for(int num : nums){
            temp += num;
            ans.push_back(temp);
        }
        
        return ans;
    }
};