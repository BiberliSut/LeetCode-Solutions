public class Solution {
    public int[] BuildArray(int[] nums) {
        return nums.Select(x => nums[x]).ToArray();
    }
}