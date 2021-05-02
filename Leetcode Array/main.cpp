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

    /**no.16 最接近的三数之和

    use tools: void quickSort(vector<int>, int);
    */
    int threeSumClosest(vector<int>& nums, int target) {
    }

    //--------------------------tools-----------------------------
    /*快速排序
        nums: 待排序的数组
        left: 起始索引
        right：终止索引 (注意nums.size()-1)
        ifReverse: 是否反转
    */
    void quickSort(vector<int> &nums, unsigned int left, unsigned int right) {
        if (nums.size() <= 1 || left >= right) return;
        unsigned int i = left+1, j = right;
        int temp;
        while (i < j) {
            while (i <= right && nums[i] <= nums[left]) ++i;
            while (j >= left && nums[j] > nums[left]) --j;
            if (i < j) {
                temp = nums[i], nums[i] = nums[j], nums[j] = temp;
            }
        }
        printArray(nums);
        cout << "left, j-1: " << left << " "<< j-1 << endl;
        cout << "j, right: " << j << " " << right << endl;
        quickSort(nums, left, j-1);
        quickSort(nums, j, right);
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
    vector<int> nums = {4, 3, 1, 9, 1, 2, 2, 2, 7, 6, 5};
    //vector<int> nums = {1, 1};
    Solution s;
    s.printArray(nums);
    cout << endl;
    s.quickSort(nums, 0, nums.size()-1);
    cout << "result: ";
    s.printArray(nums);
    return 0;
}
