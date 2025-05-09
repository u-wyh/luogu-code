def multiply(a, b, mod):
    """����˷�������� mod ȡģ"""
    n = len(a)
    m = len(b[0])
    k = len(a[0])
    ans = [[0] * m for _ in range(n)]  # ��ʼ���������
    for i in range(n):
        for j in range(m):
            for p in range(k):
                ans[i][j] = (ans[i][j] + a[i][p] * b[p][j]) % mod
    return ans

def power(a, p, mod):
    """��������ݣ������ mod ȡģ"""
    n = len(a)
    base = [[0] * n for _ in range(n)]  # ��ʼ����λ����
    for i in range(n):
        base[i][i] = 1
    while p:
        if p & 1:
            base = multiply(base, a, mod)
        p >>= 1
        a = multiply(a, a, mod)
    return base

def main():
    # ����
    n, a, b, c, mod = map(int, input().split())
    
    # ��ʼ�� nums �� base ����
    nums = [[1, 1, 1]]  # 1x3 ����
    base = [
        [a + b, 0, 0],
        [b, a + b, 0],
        [c, 0, 1]
    ]  # 3x3 ����
    
    # ���� base �� (n-1) ����
    base_pow = power(base, n - 1, mod)
    
    # ���� nums * base^(n-1)
    result = multiply(nums, base_pow, mod)
    
    # ������
    print(result[0][0])

if __name__ == "__main__":
    main()