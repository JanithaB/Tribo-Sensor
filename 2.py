import serial
import matplotlib.pyplot as plt
from collections import deque

# Configure the serial port
ser = serial.Serial('COM10', 9600)  # Replace 'COMX' with your Arduino's serial port

# Initialize data storage
max_data_points = 200  # Adjust as needed
x_data = deque(maxlen=max_data_points)
y_data = deque(maxlen=max_data_points)

# Create a figure and axis for the plot
plt.ion()  # Turn on interactive mode
fig, ax = plt.subplots()
line, = ax.plot(x_data, y_data)

# Read and process the data
for i in range(200):
    serial_line = ser.readline().decode('utf-8').strip()  # Read a line from serial
    if serial_line:
        yn_value = float(serial_line)  # Extract the 'yn' value
        x_data.append(len(x_data) + 1)  # Index for x-axis
        y_data.append(yn_value)  # Append the 'yn' value

        # Update the plot
        line.set_xdata(x_data)
        line.set_ydata(y_data)
        ax.relim()
        ax.autoscale_view()
        plt.pause(0.01)  # Pause for a short interval
print(y_data)
