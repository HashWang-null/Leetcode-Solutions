#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

class Solution {
public:
    /**no.4  寻找两个数组的中位数
    算法思路：剪除前 (m+n)/2 个数，第一个或前二个数的平均数为中位数
     */
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        if (!nums1.size()) {
            int sum = nums1.size() + nums2.size();
            return sum & 1 ? nums2[sum>>1] : (nums2[sum>>1] + nums2[(sum>>1)-1]) / 2.0;
        }
        unsigned int  res  = (nums1.size() + nums2.size() -1) >>1;
        unsigned int left1 = 0, left2 = 0;
        while (res > 0) {
            unsigned int a = left1 + (res>>1);
            unsigned int b = left2 + (res>>1);
            //越界处理
            if (a > nums1.size()) {
                a = nums1.size();
                b = res - a + left1;
            } else if (b > nums2.size()) {
                b = nums2.size();
                a = res - b + left2;
            }
            if (a == nums1.size() || nums1[a] >= nums2[b]) {
                if (b == left2) {
                    //避免当在边界时，res值不变
                    res -= 1;
                    left2 = b + 1;
                } else {
                    res -= (b-left2);
                    left2 = b;
                }
            } else if (b== nums2.size() || nums2[b] > nums1[a]) {
                if (a == left1) {
                    res -= 1;
                    left1 = a + 1;
                } else {
                    res -= (a-left1);
                    left1 = a;
                }
            }
        }
        if ((nums1.size() + nums2.size()) & 1) {
            if (left1 == nums1.size()) {
                return nums2[left2];
            }
            if (left2 == nums2.size()) {
                return nums1[left1];
            }
            return min(nums1[left1], nums2[left2]);
        } else {
            if (left2 == nums2.size()) {
                return (nums1[left1] + nums1[left1+1]) / 2.0;
            }
            if (left1+1 < nums1.size() && nums2[left2] > nums1[left1+1]) {
                return (nums1[left1] + nums1[left1+1]) / 2.0;
            }
            if (left1 == nums1.size()) {
                return (nums2[left2] + nums2[left2+1]) / 2.0;
            }
            if (left2+1 < nums2.size() && nums1[left1] > nums2[left2+1]) {
                return (nums2[left2] + nums2[left2+1]) / 2.0;
            }
            return (nums1[left1] + nums2[left2]) / 2.0;
        }
    }

    /**no.11 盛水最多的容器
    算法思路：双指针法
    */
    int maxArea(vector<int>& height) {
        int maxv = -1;
        unsigned int left = 0, right = height.size()-1;
        while (left < right) {
            int v;
            if (height[left] < height[right]) {
                v = height[left] * (right-left);
                ++left;
            } else {
                v = height[right] * (right-left);
                -- right;
            }
            maxv = max(v, maxv);
        }
        return maxv;
    }

    /**no.15 三数之和
     * 思路:排序后双指针
    */
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) return {};
        sort(nums.begin(), nums.end());
        unsigned int left, right;
        vector<vector<int>> result;
        for (int i = 0; i < nums.size()-2; i++) {
            if (nums[i] > 0) return result;
            if (i > 0 && nums[i-1] == nums[i]) continue;
            left = i+1, right = nums.size()-1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum > 0) {
                    --right;
                } else if (sum < 0){
                    ++left;
                } else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[--right] == nums[right+1]);
                    while (left < right && nums[++left] == nums[left-1]);
                } 
            }
        }
        return result;
    }

    /**no.16 最接近的三数之和
     * 思路：先排序，然后双指针法
    */
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        unsigned int left, right;
        int gap = nums[0] + nums[(nums.size()+1)>>1] + nums[nums.size()-1] - target;
        if (!gap) return target;
        for (int i = 0; i < nums.size()-2; i++) {
            if (i > 0 && nums[i-1] == nums[i]) continue;
            left = i + 1;
            right = nums.size()-1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == target) return target;
                if (abs(sum-target) < abs(gap)) {
                    gap = sum - target;
                }
                if (sum > target) {
                    while (right > left && nums[--right] == nums[right+1]);
                } else {
                    while (left < right && nums[++left] == nums[left-1]);
                }
            }
        }
        return gap + target;
    }

    /**no.26 删除有序数组中的重复项
     * 思路：使用unique函数，一行代码不比博人传燃?
     * 原理是不停的把后面不重复的元素移到前面来
    */
    int removeDuplicates(vector<int>& nums) {
        return unique(nums.begin(), nums.end()) - nums.begin();
        // unique原理：
        // if (!nums.size()) return 0;
        // unsigned int left = 0, right = 0;
        // while (++right != nums.size()) {
        //     if (nums[left] != nums[right]) {
        //         nums[++left] = nums[right];
        //     }
        // }
        // return left+1;
    }

    /**no.27 移除元素
     * 
    */
    int removeElement(vector<int>& nums, int val) {
        if (!nums.size()) return 0;
        unsigned int left = 0;
        for (unsigned int right = 0; right < nums.size(); ++right) {
            if (nums[right] != val) {
                nums[left++] = nums[right];
            }
        }
        return left;
    }

    //--------------------------tools-----------------------------
    /*快速排序
        nums: 待排序的数组
        left: 起始索引
        right：终止索引 (注意nums.size()-1)
        ifReverse: 是否反转
    */
    void quickSort(vector<int> &nums, int left, int right) {
        if (left < right) {
            unsigned int i = left, j = right;
            int pivot = nums[left];
            while (i < j) {
                while (j > i && nums[j] > pivot) --j;
                if (i < j) {
                    nums[i] = nums[j];
                    ++i;

                }
                while (i < j && nums[i] <= pivot) ++i;
                if (i < j) {
                    nums[j] = nums[i];
                    --j;
                }
            }
            nums[i] = pivot;
            quickSort(nums, left, i-1);     //caution
            quickSort(nums, i+1, right);    //caution
        }
    }

    /*打印数组*/
    void printArray(const vector<int> &nums) {
        for (unsigned int i = 0; i < nums.size(); i++) {
            cout << nums[i] << " ";
        }
        cout << endl;
    }

    void printArray(const vector<int> &nums, unsigned int beginIndex, unsigned int endIndex) {
        if (beginIndex <= endIndex && endIndex < nums.size()) {
            for (unsigned int i = beginIndex; i <= endIndex; i++) {
                cout << nums[i] << " ";
            }
            cout << endl;
        }
    }

    //-------------------------------------------------------------
    //end
};

int main()
{
    vector<int> nums = {0,1,2,2,3,0,4,2};
    Solution s;
    int result = s.removeElement(nums, 2);
    s.printArray(nums);
    cout << endl << result;

    cout << "\n\ncomplete!";
    getchar();
    return 0;
}
