import threading  # Import threading to run face verification in parallel
import cv2  # Import OpenCV for image and video processing
from deepface import DeepFace  # Import DeepFace for face recognition
import serial  # Import serial for communication with Arduino
import time  # Import time for delays

# Define the serial port and baud rate
port = "COM9"
baudrate = 9600

# Initialize serial communication with Arduino
ser = serial.Serial(port, baudrate)

# Initialize the webcam
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

# Set the video frame width and height
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 800)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 600)

# Counter for frame processing
counter = 0

# Flag to indicate if face is matched
face_match = False

# Load the reference image for face recognition
reference_image = cv2.imread("reference.jpg")

# Function to check if the current frame matches the reference image
def check_face(frame):
    global face_match
    try:
        # Verify the face using DeepFace
        if DeepFace.verify(frame, reference_image.copy())['verified']:
            face_match = True
        else:
            face_match = False
    except ValueError:
        face_match = False

# Main loop to read video frames and process them
while True:
    ret, frame = cap.read()  # Read a frame from the webcam

    if ret:
        # Every 30 frames, check for face match
        if counter % 30 == 0:
            try:
                # Start a new thread to check the face match
                threading.Thread(target=check_face, args=(frame.copy(),)).start()
            except ValueError:
                pass
        counter += 1

        # Display match or no match on the video frame
        if face_match:
            cv2.putText(frame, "MATCH!", (20, 450), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)
        else:
            cv2.putText(frame, "NO MATCH!", (20, 450), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 3)

        # If face is matched, send signal to Arduino to unlock
        if face_match:
            ser.write(bytes('1', "utf-8"))
            time.sleep(0.5)

        # Show the video frame with text
        cv2.imshow("video", frame)

    # Break the loop if 'q' is pressed
    key = cv2.waitKey(1)
    if key == ord("q"):
        break

# Release the video capture and close all OpenCV windows
cv2.destroyAllWindows()
