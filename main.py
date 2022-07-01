import threading
import time
#    TODO Timeout 15 minutes after more pomodoroses
class pomodoro():
    def __init__(self):
        self.stopped = False
        self.skipped = False
        self.timer = True
        self.pomodoros = 0

    def start_button(self):
        t = threading.Thread(target=self.start_timer)
        t.start()


    def start_timer(self):
        '''
            Start Pomodoro timer with 25 minutes (default) and 5 minutes timeout
        '''
        full_seconds = (60 * 25 if self.timer == True else 60 * 5)
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

if __name__ == '__main__':
    main()

