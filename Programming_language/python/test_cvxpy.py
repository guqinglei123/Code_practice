from cvxpy import *
# Create variables and parameters.
#建立变量与参数
x, y = Variable(), Variable()
a, b = Parameter(), Parameter()

# Examples of CVXPY expressions.
#cvxpy表达式：
print(3.69 + b/3)
print(x - 4*a)
print(sqrt(x) - min_elemwise(y, x - a))
print(max_elemwise(2.66 - sqrt(y), square(x + 2*y)))