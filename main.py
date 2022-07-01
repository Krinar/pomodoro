import sys
import threading
import time

from PyQt5 import QtWidgets
import pomodoro_gui


class App(QtWidgets.QMainWindow, pomodoro_gui.ui_pomodoro):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

class pomodoro():
    def __init__(self):
        self.stopped = False
        self.skipped = False
        self.timer = True
        self.pomodoros = 1

    def start_button(self):
        t = threading.Thread(target=self.start_timer)
        t.start()


    def start_timer(self):
        '''
            Start Pomodoro timer with 25 minutes (default) and 5 minutes timeout.
            Every 3 Pomodoro timeout is 15 minutes
        '''
        if self.pomodoros % 4 == 0:
            full_seconds = 60 * 2 # 60 * 15
        else:
            full_seconds = (60 * 3 if self.timer == True else 60 * 1)
        while full_seconds > 0 and not self.stopped:
            minutes, seconds = divmod(full_seconds, 60)
            print("{0:02d}:{1:02d}".format(minutes, seconds))
            time.sleep(1)
            full_seconds -= 1
        if self.timer:
            self.pomodoros += 1
        self.timer = not self.timer
        self.start_button()

def main():
    p = pomodoro()
    p.start_button() 
    app = QtWidgets.QApplication(sys.argv)  # Новый экземпляр QApplication
    window = App()  # Создаём объект класса ExampleApp
    window.show()  # Показываем окно
    app.exec_()  # и запускаем приложение

if __name__ == '__main__':
    main()

