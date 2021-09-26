import sys, pathlib
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow

class Calculator(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi(str(pathlib.Path(__file__).parent.absolute())+'\Calculator.ui', self)
        self.B0.clicked.connect(self.Add)
        self.B1.clicked.connect(self.Add)
        self.B2.clicked.connect(self.Add)
        self.B3.clicked.connect(self.Add)
        self.B4.clicked.connect(self.Add)
        self.B5.clicked.connect(self.Add)
        self.B6.clicked.connect(self.Add)
        self.B7.clicked.connect(self.Add)
        self.B8.clicked.connect(self.Add)
        self.B9.clicked.connect(self.Add)
        self.Plus.clicked.connect(self.Add)
        self.Minus.clicked.connect(self.Add)
        self.Mul.clicked.connect(self.Add)
        self.Del.clicked.connect(self.Add)
        self.Point.clicked.connect(self.Add)
        self.LP.clicked.connect(self.Add)
        self.RP.clicked.connect(self.Add)
        self.Dl.clicked.connect(self.Delete)
        self.Cl.clicked.connect(self.Clear)
        self.Equal.clicked.connect(self.Calculate)
    def Add(self): self.plainTextEdit.setPlainText(self.plainTextEdit.toPlainText()+self.sender().text())
    def Delete(self): self.plainTextEdit.setPlainText(self.plainTextEdit.toPlainText()[:-1:])
    def Clear(self): self.plainTextEdit.setPlainText("")
    def Calculate(self):
        try: self.plainTextEdit.setPlainText(str(eval(self.plainTextEdit.toPlainText())))
        except Exception as e:
            if str(e) != "division by zero": self.plainTextEdit.setPlainText("invalid input")
            else: self.plainTextEdit.setPlainText(str(e))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Calculator()
    ex.show()
    sys.exit(app.exec())