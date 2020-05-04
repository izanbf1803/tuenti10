c = int(input())

def solve(n):
    if n < 20:
        return -1
    d = n//20
    if 20*d <= n and n <= 29*d:
        return d
    return -1

for tc in range(c):
    n = int(input())
    ans = solve(n)
    if ans == -1:
        print(f"Case #{tc+1}: IMPOSSIBLE")
    else:
        print(f"Case #{tc+1}: {ans}")