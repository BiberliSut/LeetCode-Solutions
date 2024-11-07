class Solution:
    def isMatch(self, s, p):
        # Initialize DP table with False
        dp = [[False] * (len(p) + 1) for _ in range(len(s) + 1)]
        
        # Base case: empty pattern matches empty string
        dp[0][0] = True
        
        # Fill first row for patterns like "a*", "a*b*", etc.
        for j in range(2, len(p) + 1):
            if p[j - 1] == '*':
                dp[0][j] = dp[0][j - 2]

        # Fill the DP table
        for i in range(1, len(s) + 1):
            for j in range(1, len(p) + 1):
                if p[j - 1] == '.' or p[j - 1] == s[i - 1]:
                    # Current characters match
                    dp[i][j] = dp[i - 1][j - 1]
                elif p[j - 1] == '*':
                    # '*' can mean zero of the preceding element
                    dp[i][j] = dp[i][j - 2]
                    # '*' can mean one or more of the preceding element
                    if p[j - 2] == '.' or p[j - 2] == s[i - 1]:
                        dp[i][j] = dp[i][j] or dp[i - 1][j]

        # Result is in the bottom-right corner of the table
        return dp[len(s)][len(p)]
