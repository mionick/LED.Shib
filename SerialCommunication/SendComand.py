import time
import serial

print "VALID INPUTS: R255 G255 B255 S1.0 r1 s1 b1.0"


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
        command = input("Enter a Light string or 'q' to stop: ")
        print command
        
        ser.write(command.encode())
finally:
    ser.close()
