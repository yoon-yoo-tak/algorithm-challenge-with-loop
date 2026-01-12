class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int answer = 0;
        int n = nums.size();
        for (int i = 0; i < n - 1;i++){
            int left = 0, right = 0;
            for (int j = 0; j <= i; j++) left += nums[j];
            for (int j = i + 1; j < n; j++) right += nums[j];
            if (abs(left - right) % 2 == 0) answer++;
        }
        return answer;
    }
};