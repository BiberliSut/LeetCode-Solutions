public class Solution {
    Dictionary<int, IList<TreeNode>> memo = new Dictionary<int, IList<TreeNode>>();
    
    public IList<TreeNode> AllPossibleFBT(int n) {
        if (!memo.ContainsKey(n)) {
            List<TreeNode> list = new List<TreeNode>();
            if (n == 1) {
                list.Add(new TreeNode(0));
            } else if (n % 2 == 1) {
                for (int i = 0; i < n; ++i) {
                    int j = n - 1 - i;
                    foreach (TreeNode left in AllPossibleFBT(i)) {
                        foreach (TreeNode right in AllPossibleFBT(j)) {
                            TreeNode root = new TreeNode(0);
                            root.left = left;
                            root.right = right;
                            list.Add(root);
                        }
                    }
                }
            }
            memo[n] = list;
        }
        return memo[n];
    }
}