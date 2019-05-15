# Jump.py
from PyQt5 import QtCore, QtGui, QtWidgets
from Ui_Manuscript import Ui_Form
from Ui_welcom2 import Ui_Main2
from Deal import DealData


#主界面
class login(QtWidgets.QMainWindow,Ui_Form):
    def __init__(self):
        super(login,self).__init__()
        self.setupUi(self)

    def DepartmentCount(self):
        DealData.Department_data()

    def PersonalCount(self):
        DealData.Personal_data()

    def ClearCache(self):
        DealData.Clear_Cache()

#运行窗口Login
if __name__=="__main__":
    import sys
    app=QtWidgets.QApplication(sys.argv)
    first=login()
    first.show()
    DealData=DealData()
    first.DepartmentButton.clicked.connect(first.DepartmentCount)
    first.PersonalButton.clicked.connect(first.PersonalCount)
    first.ClearCacheButton.clicked.connect(first.ClearCache)
    sys.exit(app.exec_())
