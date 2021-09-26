import sys, pathlib
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QHBoxLayout, QVBoxLayout, QCheckBox, QSpinBox, QLabel

ITEMS = ("Hamburger", "Cheseburger", "Nuggets", "Fry", "Cola")
PRICES = (200, 250, 150, 150, 80)

class Receipt(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi(str(pathlib.Path(__file__).parent.absolute())+'\Receipt.ui', self)
        self.items, self.res = [], 0
        for i in range(len(ITEMS)):
            hl, cb, label, sb = QHBoxLayout(), QCheckBox(), QLabel(), QSpinBox()
            cb.setText(ITEMS[i]), label.setText(str(PRICES[i])+" р."), sb.setMinimum(1)
            hl.addWidget(cb), hl.addWidget(label), hl.addWidget(sb)
            self.verticalLayout_1.addLayout(hl), self.items.append((cb, label.text(), sb))
        self.Print.clicked.connect(self.PrintReceipt)
    
    def PrintReceipt(self):
        self.plainTextEdit.setPlainText('')
        self.res = 0
        for i in self.items:
            if i[0].isChecked():
                self.plainTextEdit.appendPlainText(i[0].text()+"-"*(25-len(i[0].text()))+str(i[2].value())+'*'+i[1]+"   |   "+str(i[2].value()*int(i[1].split()[0]))+" р.\n")
                self.res+=i[2].value()*int(i[1].split()[0])
        if self.plainTextEdit.toPlainText() != '': self.plainTextEdit.appendPlainText(' '*35+"Итого: "+str(self.res)+" р.")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Receipt()
    ex.show()
    sys.exit(app.exec())