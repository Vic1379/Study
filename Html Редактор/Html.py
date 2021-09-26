import sys, pathlib
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow

class HtmlRed(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi(str(pathlib.Path(__file__).parent.absolute())+'\HtmlEditor.ui', self)
        self.textEdit.textChanged.connect(self.TextChanged)
    def TextChanged(self): self.textBrowser.setHtml(self.textEdit.toPlainText())

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = HtmlRed()
    ex.show()
    sys.exit(app.exec())