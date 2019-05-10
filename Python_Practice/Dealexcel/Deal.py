import xlwings as xw
import os,sys,shutil
class DealData:
    def __init__(self):
        self.department_data = {}
        self.name_data = {}

    def __Judge_Cache(self):
        print("判断缓存数据")
        if os.path.exists("temp.xls"):
            return True
        else:
            if os.path.exists("temp0.xls"):
                shutil.copyfile("temp0.xls","temp.xls")     
            else:
                return False                      
        return True

    def __Judge_goal(self):
        print("判断目标数据")
        if (os.path.exists("goal.xls")):
            os.remove("goal.xls")
        if os.path.exists("goal0.xls"):
            shutil.copyfile("goal0.xls","goal.xls")
        else:
            return False                         
        return True

    def __Deal_Cache(self,data_type=''):
        print("处理缓存数据")
        if not self.__Judge_Cache():
            return False
        if(data_type == ''):
            return False
        #打开原始表格，获得所需数据
        # app = xw.App(visible=True,add_book=True)
        # wb = app.books.open('2019年南机笛声刊稿统计（汇总表）.xls')
        wb = xw.Book('temp.xls')
        sht1 = wb.sheets[0]
        number = sht1.range('J3:J300').value

        ##统计车间数据
        if(data_type == 'department'):
            i = 0
            department = sht1.range('E3:E300').value
            for j in department:    
                if j == None:
                    i = i + 1
                    continue
                if j in self.department_data:
                    self.department_data[j] =  self.department_data[j] + number[i]
                else:
                    self.department_data[j] = number[i]
                i = i + 1
            print(self.department_data)

        ##统计个人数据
        if(data_type == 'Personal'):
            i = 0
            name = sht1.range('F3:F300').value
            for j in name: 
                i = i + 1   
                if j == None:    
                    continue
                if j in self.name_data:
                    self.name_data[j] =  self.name_data[j] + number[i-1]
                else:
                    self.name_data[j] = number[i-1]
            print(self.name_data)
        # wb.save('temp.xls')
        wb.close()
        return False

    def Clear_Cache(self):
        print("开始清除缓存数据")
        if os.path.exists("temp.xls"):
            os.remove("temp.xls")    
        if os.path.exists("temp0.xls"):
            shutil.copyfile("temp0.xls","temp.xls")
        else:
            return False                
        return True

    def Department_data(self):
        print("开始处理部门数据")
        if not self.__Judge_goal():
            return False
        self.__Deal_Cache('department')
        if self.department_data == {}:
            return False
        # 填写2018年《南宁铁道报》《南机笛声》刊稿任务完成情况统计表       
        # 处理sheet1中第一个表格
        wb2 = xw.Book('goal.xls')
        sht21 = wb2.sheets[0]
        sht21_department = sht21.range('B4:B33').value
        i = 4
        for j in sht21_department:
            dex_department = 'D' + str(i)
            if j in self.department_data.keys():
                if self.department_data[j] == None:
                    sht21.range(dex_department).value = 0
                else:        
                    sht21.range(dex_department).value = self.department_data[j]
            else :
                sht21.range(dex_department).value = 0    
            i = i + 1
        # wb2.save('goal.xls')
        # wb2.close()
        return True

    def Personal_data(self):
        print("开始处理个人数据")
        if not self.__Judge_goal():
            return False
        self.__Deal_Cache('Personal')
        if self.name_data == {}:
            return False
        wb2 = xw.Book('goal.xls')
        # 处理sheet2中数据
        sht22 = wb2.sheets[1]
        sht22_person = sht22.range('B3:B392').value
        i = 3
        for j in sht22_person:
            dex_name = 'C' + str(i)
            if j in self.name_data.keys():
                if self.name_data[j] == None:
                    sht22.range(dex_name).value = 0
                else:        
                    sht22.range(dex_name).value = self.name_data[j]
            else :
                sht22.range(dex_name).value = 0         
            i = i + 1

        # 处理sheet3中
        sht23 = wb2.sheets[2]
        sht23_person = sht23.range('D3:D121').value
        i = 3
        for j in sht23_person:
            dex_name = 'F' + str(i)
            if j in self.name_data.keys():
                if self.name_data[j] == None:
                    sht23.range(dex_name).value = 0
                else:        
                    sht23.range(dex_name).value = self.name_data[j]
            else :
                sht23.range(dex_name).value = 0         
            i = i + 1

        # 处理sheet4中
        sht24 = wb2.sheets[3]
        sht24_person = sht24.range('D4:D108').value
        i = 4
        for j in sht24_person:
            dex_name = 'E' + str(i)
            if j in self.name_data.keys():
                if self.name_data[j] == None:
                    sht24.range(dex_name).value = 0
                else:        
                    sht24.range(dex_name).value = self.name_data[j]
            else :
                sht24.range(dex_name).value = 0         
            i = i + 1
        # wb2.save('goal.xls')
        # wb2.close()
        return True












