from fractions import Fraction
from math import floor


def compute_outcomes(n):
    outcomes = [0] * (n + 1)
    outcomes[-1] = 1
    outcomes[-2] = 1  # outcomes represents values of outcome tree after i turns

    for i in range(2, n + 1):  # looping through levels i of tree
        for j in range(n):
            outcomes[j] = outcomes[j + 1]  # number of ways to get to given node is above right node plus i*(above left node)

        outcomes[n] = 0  # far right node initialized to 0 since only contribution is from above left node

        for j in range(n, 0, -1):  # not including node 0 since it doesn't have contribution from above left
            outcomes[j] += outcomes[j - 1] * i  # contribution from above left node of tree

    return outcomes


def compute_price(outcomes):
    n = len(outcomes) - 1
    k = (n + 1) // 2
    return Fraction(sum(outcomes), sum(outcomes[:k]))


T = int(input())
for j in range(T):
    N = int(input())
    outcomes = compute_outcomes(N)
    s = compute_price(outcomes)
    print (floor(s))
