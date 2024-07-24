import serial
import pandas as pd
import time

# Serial port configuration
serial_port = 'COM8'  # Replace with your serial port
baud_rate = 115200  # Replace with your baud rate

grip = 'PointTripod'

ser = serial.Serial(serial_port, baud_rate)

ser.setRTS(False)
ser.setDTR(False)

file_name = grip + '_' + time.strftime('%m_%d_%H_%M_%S') + ".xlsx"

# Create a DataFrame with the appropriate columns
columns = ['sample', 'ax', 'ay', 'az', 'gx', 'gy', 'gz', 't', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 's8']
df = pd.DataFrame(columns=columns)

def add_to_dataframe(data):
    global df
    # Split the received data into individual data points
    data_points = data.split(',')

    # Create a list with the timestamp followed by the data points
    # row = [time.strftime('%H:%M:%S')] + data_points
    row = data_points

    # Append the new row to the DataFrame
    df.loc[len(df)] = row

def main():
    global df
    try:
        while True:
            # Read data from the serial port
            if ser.in_waiting > 0:
                data = ser.readline().decode('utf-8').strip()
                print(f"Data: {data}")
                add_to_dataframe(data)
                # time.sleep(0.001)
    except KeyboardInterrupt:
        print("Exiting program.")
    finally:
        # Save the DataFrame to an Excel file when the program is closed
        df.to_excel(file_name, index=False)
        ser.close()

if __name__ == '__main__':
    main()
