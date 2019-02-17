#1.函数定义示例
def say_hello():
    # 属于该函数的语句块
    print('hello world')
# 函数结束

say_hello()  # 调用函数
say_hello()  # 再次调用函数

#2.函数参数示例
def print_max(a, b):
    if a > b:
        print(a, 'is maximum')
    elif a == b:
        print(a, 'is equal to', b)
    else:
        print(b, 'is maximum')

# 直接传递字面量
print_max(3, 4)

x = 5
y = 7

# 传递变量作为实参
print_max(x, y)


#3.局部变量
x = 50

def func(x):
    print('x is', x)
    x = 2
    print('Changed local x to', x)

func(x)
print('x is still', x)