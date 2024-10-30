# Infinit8I-UI

INTERFACE FOR USER DATA ACQUISITION

Instructions:

There are two scripts!

A)Infinite Plot
    This script is for make EMG plot in three possible ways
    Suchs as:
        1. Full plot
        2. By channels
        3. Extracting with given time


B) InfiniteV3
    This a script to measure, acquire and plot the data from INFINIT8I

    It works by threads and tkinter. The following steps would be: 1. Change to .EXE 2. Change to POO  3. Config menu to change the Times in sesions

    To start to plot, acquire or both, first it's necessary to conect the serial:
        COM -> Choose the Serial port (By link or Bluethooh Classic)
        Baudarte -> This case is 115200
        And then push -> CONNECT
        if there is the case that there isn't the port, push Update COM

    TO PLOT
        This will plot the 8-EMG channels through Spider plot and plot IMU-gyroscope and IMU-accelerometer 
        1. Check  "Plot" box
        2. Push Process
        3. It's possible to stop the plot o resume it, by push the corresponding Button


    TO ACQUIRE
        1. Fulfill all the necesary data -> Name, Grip, Tag
        2. Choose between by sets or normal time by pushing "Sets" box (if not  will be Normal time in SECONDS)
        3. Check "Data ACQ" box
        4. Push Process
        5. Wait until the end (by pushing exit before the end, the software will not save the data) (The data will save in the same dossier, please change this in futher versions )
        6. Push Exit and repeat the flow


    BOTH!
    Combine "To plot" and "To acquire" instructions

   


Desarrollado por: Paul Benavides; PYBL2001@GMAIL.COM, Medellín 2024

MIT LICENSE - Not distributed for commercial or medical use; research and education use encouraged.


