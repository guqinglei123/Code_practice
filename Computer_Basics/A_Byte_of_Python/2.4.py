#5.常量
#三引号构造多行字符串
print('三引号构造多行字符串:')
a='''This is a multi-line string. This is the first line.
This is the second line.
"What's your name?," I asked.
He said "Bond, James Bond."
'''
print(a)


#format 方法构造字符串
print('format 方法构造字符串:')
age = 20
name = 'Swaroop'
print('{0} was {1} years old when he wrote this book'.format(name, age))
print('Why is {0} playing with that python?'.format(name))
#下面这种方式效果一样
#print('{} was {} years old when he wrote this book'.format(name, age))
#print('Why is {} playing with that python?'.format(name))
print('')

#6.打印控制，使用format 控制输出格式
print('使用format 控制输出格式:')
# 取十进制小数点后的精度为 3 ，得到的浮点数为 '0.333'
print('{0:.3f}'.format(1.0/3))
# 填充下划线 (_) ，文本居中
# 将 '___hello___' 的宽度扩充为 11 
print('{0:_^11}'.format('hello'))
# 用基于关键字的方法打印显示 'Swaroop wrote A Byte of Python'
print('{name} wrote {book}'.format(name='Swaroop', book='A Byte of Python'))
print('')


#控制print中的换行符
print('控制print中的换行符：')
#将print中最后的换行符改变为空格
print('a', end=' ')
print('b', end=' ')
print('c')
print('')

#7.转义序列
print('转义序列：')
print('What\'s your name?')#使用转义序列输出'
#print("What's your name?") #同样可以通过“”输出'
print('This is the first line\nThis is the second line')#使用/n实现换行 
#print("What's your name?") #同样可以通过'''  '''进行换行
print("This is the first sentence.\
This is the second sentence.")#使用\连接 
print("Newlines are indicated by \n") 
print(r"Newlines are indicated by \n") #输出转义序列\n
print('')


