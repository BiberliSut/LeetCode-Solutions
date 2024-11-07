class Solution:
    def kthFactor(self, n, k):
        # Find all factors up to sqrt(n)
        factors = []
        
        for i in range(1, int(n**0.5) + 1):
            if n % i == 0:
                factors.append(i)
                # Check for its corresponding factor if it's distinct
                if i != n // i:
                    factors.append(n // i)
        
        # Sort the factors in ascending order
        factors.sort()
        
        # Return the kth factor or -1 if k is out of range
        if k <= len(factors):
            return factors[k - 1]
        else:
            return -1

# Usage
solution = Solution()
print(solution.kthFactor(12, 3))  # Output: 3
print(solution.kthFactor(7, 2))   # Output: 7
print(solution.kthFactor(4, 4))   # Output: -1
