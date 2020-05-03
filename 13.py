INF = 2**62+1

def simulate(n, h0, square):
    h = h0
    ans = (n if square else n+1) * n * h
    h -= 2
    step = 1
    while h > 0:
        border = 0
        if square:
            border = 4*(n+2*step) - 4
        else:
            border = 2*(n+2*step) + 2*(n+1+2*step) - 4

        ans += border * h
        if ans >= INF:
            return INF

        if step % 2 == 1:
            h += 1
        else:
            h -= 2
        step += 1
    return ans

def solve(P, square):
    # Binary search maximum height, using smallest central tower
    l = 3
    r = INF
    h = 0
    while l <= r:
        m = (l+r)//2
        s = simulate(1, m, square)
        if s <= P:
            h = m
            l = m+1
        else:
            r = m-1

    if h == 0: # no solution
        return (0, 0)

    # Now we have a fixed height, so we binary search maximum central tower
    l = 1
    r = INF
    max_packs = 0
    while l <= r:
        m = (l+r)//2
        s = simulate(m, h, square)
        if s <= P:
            max_packs = s
            l = m+1
        else:
            r = m-1

    return (h, max_packs)


C = int(input())
for tc in range(C):
    P = int(input())
    H, M = max(solve(P, True), solve(P, False))
    if H == 0:
        print(f"Case #{tc+1}: IMPOSSIBLE")
    else:
        print(f"Case #{tc+1}: {H} {M}")