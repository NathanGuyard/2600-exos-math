# Aucun n'import ne doit être fait dans ce fichier

def nombre_entier(n: int) -> str:
    return 'S' * n + '0'

def S(n: str) -> str:
    return 'S' + n

def addition(a: str, b: str) -> str:
    if a == '0':
        return b
    if b == '0':
        return a
    return 'S' + addition(a[1:], b)

def multiplication(a: str, b: str) -> str:
    if a == '0' or b == '0':
        return '0'
    if a == 'S0':
        return b
    if b == 'S0':
        return a
    return addition(b, multiplication(a[1:], b))

def facto_ite(n: int) -> int:
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result

def facto_rec(n: int) -> int:
    if n == 0:
        return 1
    return n * facto_rec(n - 1)

def fibo_rec(n: int) -> int:
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fibo_rec(n - 1) + fibo_rec(n - 2)

def fibo_ite(n: int) -> int:
    if n == 0:
        return 0
    if n == 1:
        return 1
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b

def golden_phi(n: int) -> float:
    a, b = 1, 1
    for _ in range(n):
        a, b = a + b, a
    return a / b

def sqrt5(n: int) -> int:
    return golden_phi(n)*2-1

def pow(a: float, n: int) -> float:
    result = 1.0
    for _ in range(n):
        result *= a
    return result
