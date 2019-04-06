#1.if语句
number = 23
guess = int(input('Enter an integer : '))

if guess == number:
    # 新程序块的开始处
    print('Congratulations, you guessed it.')
    print('(but you do not win any prizes!)')
    # 新程序块的结尾处
elif guess < number:
    # 另一个程序块
    print('No, it is a little higher than that')
    # 你可以在程序块中“为所欲为”——做任何你想做的事情
else:
    print('No, it is a little lower than that')
    # 只有当猜测数大于给定数的时候，才会执行此处

print('Done')

#2.while 语句
number = 23
running = True

while running:
    guess = int(input('Enter an integer : '))

    if guess == number:
        print('Congratulations, you guessed it.')
        # 这会导致 while 循环停止
        running = False
    elif guess < number:
        print('No, it is a little higher than that.')
    else:
        print('No, it is a little lower than that.')
else:
    print('The while loop is over.')
    # 你可以在此处继续进行其它你想做的操作

print('Done')

#3.for 循环
for i in range(1, 5):
    print(i)
else:
    print('The for loop is over')

#4.break语句
while True:
    s = input('Enter something : ')
    if s == 'quit':
        break
    print('Length of the string is', len(s))
print('Done')

#5.continue语句
while True:
    s = input('Enter something : ')
    if s == 'quit':
        break
    if len(s) < 3:
        print('Too small')
        continue
    print('Input is of sufficient length')