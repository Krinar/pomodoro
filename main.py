import sys
import threading
import time

from PyQt5 import QtWidgets
import pomodoro_gui


class App(QtWidgets.QMainWindow, pomodoro_gui.ui_pomodoro):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.stopped = False
        self.skipped = False
        self.timer = True
        self.pomodoros = 1
        self.pushButton.clicked.connect(self.start_timer_thread)
        self.pushButton_2.clicked.connect(self.stop_timer)
        

    def start_timer_thread(self):
        self.t = threading.Thread(target=self.start_timer())
        self.t.start()

    def stop_timer(self):
        self.t.stop()

    def start_timer(self):
        if self.pomodoros % 4 == 0:
            full_seconds = 60 * 2 # 60 * 15
        else:
            full_seconds = (60 * 3 if self.timer == True else 60 * 1)
        while full_seconds > 0 and not self.stopped:
            minutes, seconds = divmod(full_seconds, 60)
            print("{0:02d}:{1:02d}".format(minutes, seconds))
            #self.label.setText("{0:02d}:{1:02d}".format(minutes, seconds))
            time.sleep(1)
            full_seconds -= 1
        if self.timer:
            self.pomodoros += 1
        self.timer = not self.timer
        self.start_button()


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = App()
    window.show()
    app.exec_()

if __name__ == '__main__':
    main()

