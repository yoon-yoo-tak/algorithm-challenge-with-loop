def solution(distance, rocks, n):
    answer = 0
    rocks.sort()

    def ok(x):
        cnt = 0
        prev = 0
        for i in rocks:
            d = i - prev
            if d < x:
                cnt += 1
            else:
                prev = i
        if distance - prev < x:
            cnt += 1
        return cnt <= n

    l = 0
    r = distance

    while l <= r:
        mid = l + r >> 1
        if ok(mid):
            answer = mid
            l = mid + 1
        else:
            r = mid - 1
    return answer