import matplotlib.pyplot as plt  
import serial
import threading

global val

lightValue = []
arduinoAnalog = serial.Serial('port',9600)
data_rate = 10
plot_rate = 10
num_samples = 50 
cancellation_token = threading.Event()


def plot(get_val):
    def makeFigure():
        plt.ylim(50,850)
        plt.plot(lightValue, 'ro-')
        plt.title('Photoresistor Reading')
        plt.ylabel('lumens')
        plt.xlabel('time')

    def fetch_data():
        while not cancellation_token.is_set():
            try:
                val = get_val()
            except Exception as e:
                print(str(e)
                time.sleep(1)
                continue
            lightValue.append(val)
            if len(lightValue) > num_samples:
                lightValue = lightValue[-num_samples:]
            time.sleep(1/data_rate) 
    def plot_data():
        plt.ion()
        def did_close(evt):
            cancellation_token.set()
        fig.canvas.mpl_connect('close_event', did_close)
        fig = plt.figure()
        while not cancellation_token.is_set():
            plt.clf()
            plt.plot(lightValue)
            fig.canvas.draw()
            fig.canvas.start_event_loop(1/plot_rate)
    fetch_t = threading.Thread(target=fetch_data)
    fetch_t.daemon = True
    fetch_t.start() 
    plot_t = threading.Thread(target= plot_data)
    plot_t.daemon = True
    plot_t.start()

    return cancellation_token


plot(lambda : [int(arduinoData.readline().decode('utf-8'))])
