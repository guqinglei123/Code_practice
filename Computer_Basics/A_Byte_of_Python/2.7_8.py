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


#4. 全局变量

def func1():
    global x
    print('x is', x) # 如果前面不申明global，那么这句话将会报错，
                     # 同时下一句话是重新定义了一个局部变量，并且赋值
    x = 3
    print('Changed local x to', x)

func1()
print('x is still', x) #注意这里和上面相比，变为2了

#5.默认参数值
def	say(message,	times=1):
	print(message * times)
say('Hello')
say('World ',5)

#6.关键字参数
def func(a,	b=5,	c=10):
	print('a is',a,'and	b is', b, 'and c is', c)
func(3,	7)
func(25, c=24)
func(c=50, a=100)

#6.可变参数
def total(a=5, *numbers, **phonebook):
    print('a', a)

    # 遍历元组中的所有项
    for single_item in numbers:
        print('single_item', single_item)

    # 遍历字典中的所有项
    for first_part, second_part in phonebook.items():
        print(first_part,second_part)

print(total(10,1,2,3,Jack=1123,John=2231,Inge=1560))


#7.return语句
def maximum(x, y):
    if x > y:
        return x
    elif x == y:
        return 'The numbers are equal'
    else:
        return y

print(maximum(2, 3))

#7.DocStrings
def print_max(x, y):
    '''Prints the maximum of two numbers.
The two values must be integers.'''#这个被称为DocStrings
    # 如果有必要，将参数转为整数
    x = int(x)
    y = int(y)

    if x > y:
        print(x, 'is maximum')
    else:
        print(y, 'is maximum')

print_max(3, 5)
print(print_max.__doc__)

#7.模块
import sys #python本身的模块

print('The command line arguments are:')
for i in sys.argv:   #硕士该文件中的参数，运行的脚本名称在sys.argv的列表中总会位列第一。
    print(i)

print('\n\nThe PYTHONPATH is', sys.path, '\n') #，搜索python的安装路径。你能观察到sys.path的第一段
                                            #字符串是空的——这一空字符串代表当前目录也是sys.path的一部分

#8.按字节码编译的.pyc文件
#9.	from..import语句
from math import sqrt
print("Square root of 16 is", sqrt(16))

#10.模块的__name__	
if __name__ == '__main__':
    print('This program is being run by itself')  #如果直接运行该py文件，则输出这一句。
else:
    print('I am being imported from another module') #如果该py文件是导入别的文件，则输出这一句。