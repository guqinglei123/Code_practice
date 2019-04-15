import xlwings as xw

#打开原始表格，获得所需数据
# app = xw.App(visible=True,add_book=True)
# wb = app.books.open('2019年南机笛声刊稿统计（汇总表）.xls')
wb = xw.Book('456.xls')
sht1 = wb.sheets[0]
department = sht1.range('E3:E300').value
name = sht1.range('F3:F300').value
number = sht1.range('J3:J300').value
department_data = {}

##统计车间数据
i = 0
for j in department:    
    if j == None:
        i = i + 1
        continue
    if j in department_data:
        department_data[j] =  department_data[j] + number[i]
    else:
        department_data[j] = number[i]
    i = i + 1
# print(department_data)

##统计个人数据
i = 0
name_data = {}
for j in name: 
    i = i + 1   
    if j == None:    
        continue
    if j in name_data:
        name_data[j] =  name_data[j] + number[i-1]
    else:
        name_data[j] = number[i-1]
# print(name_data)
# wb.save('456.xls')
# wb.close()



# 填写2018年《南宁铁道报》《南机笛声》刊稿任务完成情况统计表
wb2 = xw.Book('123.xls')
# 处理sheet1中一月份数据
sht21 = wb2.sheets[0]
sht21_department = sht21.range('B4:B33').value
i = 4
for j in sht21_department:
    dex_department = 'D' + str(i)
    if j in department_data.keys():
        if department_data[j] == None:
            sht21.range(dex_department).value = 0
        else:        
            sht21.range(dex_department).value = department_data[j]
    else :
        sht21.range(dex_department).value = 0    
    i = i + 1
# wb21.save('123.xls')
# wb21.close()

# 处理sheet2中数据
sht22 = wb2.sheets[1]
sht22_person = sht22.range('B3:B392').value
i = 3
for j in sht22_person:
    dex_name = 'C' + str(i)
    if j in name_data.keys():
        if name_data[j] == None:
            sht22.range(dex_name).value = 0
        else:        
            sht22.range(dex_name).value = name_data[j]
    else :
        sht22.range(dex_name).value = 0         
    i = i + 1

# 处理sheet3中
sht23 = wb2.sheets[2]
sht23_person = sht23.range('D3:D121').value
i = 3
for j in sht23_person:
    dex_name = 'F' + str(i)
    if j in name_data.keys():
        if name_data[j] == None:
            sht23.range(dex_name).value = 0
        else:        
            sht23.range(dex_name).value = name_data[j]
    else :
        sht23.range(dex_name).value = 0         
    i = i + 1

# 处理sheet4中
sht24 = wb2.sheets[3]
sht24_person = sht24.range('D4:D108').value
i = 4
for j in sht24_person:
    dex_name = 'E' + str(i)
    if j in name_data.keys():
        if name_data[j] == None:
            sht24.range(dex_name).value = 0
        else:        
            sht24.range(dex_name).value = name_data[j]
    else :
        sht24.range(dex_name).value = 0         
    i = i + 1

