import serial
import keyboard

# Define the serial port and baud rate
ser = serial.Serial("COM5", 115200)  # Replace 'COM5' with your serial port

running = True  # Flag to control the loop

while running:
    try:
        # Read data from the serial port
        data = ser.read().strip().decode("utf-8")
        
        
        if data == "D":
            keyboard.press_and_release("d")
        elif data == "F":
            keyboard.press_and_release("f")
        elif data == "J":
            keyboard.press_and_release("j")
        elif data == "K":
            keyboard.press_and_release("k")
        
        elif data == "U":
            keyboard.press_and_release("up")
        elif data == "O":
            keyboard.press_and_release("down")
        elif data == "L":
            keyboard.press_and_release("left")
        elif data == "R":
            keyboard.press_and_release("right")

        elif data == "E":
            keyboard.press_and_release("enter")
        elif data == "B":
            keyboard.press_and_release("backspace")    
        #Add more key mappings as need
    except Exception as e:
        print(f"Error: {e}")

# Close the serial port when done (you can use a better exit condition)
ser.close()