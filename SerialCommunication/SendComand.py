import time
import serial

# COM3 is displayed at bottom right of Arduino GUI
ser = serial.Serial('COM3', 9600)
#need to delay the start while arduino gets set up becase it restarts when serial connects.
time.sleep(5);

# Set new_name to something other than 'quit'.
command = ''
try:
    # Start a loop that will run until the user enters 'quit'.
    while command != 'q':
        # Ask the user for a name.
        command = input("Please tell me someone I should know, or enter 'quit': ")
        print command
        
        ser.write(command.encode())
finally:
    ser.readlineclose()
