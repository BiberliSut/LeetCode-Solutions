public class Solution {
    public double SoupServings(int n) {
        if(n>=4800)
            return 1;
        cache = new();
        return DP(n,n);
    }

    private Dictionary<(int,int),double> cache;
    private List<(int serveA, int serveB)> operations = new()
    {
        (100,0),
        (75,25),
        (50,50),
        (25,75)
    };

    private double DP(int a, int b)
    {
        if(a<=0 && b<=0)
            return 0.5;
        if(a<=0)
            return 1.0;
        if(b<=0)
            return 0.0;

        if(cache.ContainsKey((a,b)))
            return cache[(a,b)];

        double total = 0.0;
        foreach(var op in operations)
        {
            int x = a - op.serveA;
            int y = b - op.serveB;
            total += DP(x,y);
        }
        return cache[(a,b)] = total/4;
    }
}