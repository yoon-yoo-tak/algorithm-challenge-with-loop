def solution(board, skill):
    answer = 0
    n = len(board)
    m = len(board[0])

    imos_2d = [[0] * (m + 1) for _ in range(n + 1)]

    for t, x1, y1, x2 ,y2, degree in skill:
        if t == 1: # 공격
            imos_2d[x1][y1] -= degree
            imos_2d[x1][y2 + 1] += degree
            imos_2d[x2 + 1][y1] += degree
            imos_2d[x2 + 1][y2 + 1] -= degree
        else:
            imos_2d[x1][y1] += degree
            imos_2d[x1][y2 + 1] -= degree
            imos_2d[x2 + 1][y1] -= degree
            imos_2d[x2 + 1][y2 + 1] += degree
    N = len(imos_2d)
    M = len(imos_2d[0])
    for i in range(N - 1):
        for j in range(M - 1):
            imos_2d[i][j + 1] += imos_2d[i][j]

    for j in range(M - 1):
        for i in range(N - 1):
            imos_2d[i + 1][j] += imos_2d[i][j]

    for i in range(n):
        for j in range(m):
            board[i][j] += imos_2d[i][j]
            if board[i][j] >0:
                answer += 1
    return answer