#include <vector>
#include <iostream>
using namespace std;
int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = 0;
        int result = n + 1;
        int sum=0;
        while(left<n&&right<n)
        {
            while(sum<target&&right<n)
            {
                sum+=nums[right];
                right++;
            }
            if(sum>=target)right--;
            while(sum>=target&&left<right)
            {
                result=((right-left+1)<result)?(right-left+1):result;
                sum-=nums[left];
                left++;
            }
        }
        return result;
    }
int main()
{
    vector<int> nums={2,3,1,2,4,3};
    int target=7;
    cout << "目标和: " << target << endl;
    cout << "数组: ";
    for(int num : nums) cout << num << " ";
    cout << endl;
    cout << "最小子数组长度: " << minSubArrayLen(target,nums) << endl;
    return 0;
}