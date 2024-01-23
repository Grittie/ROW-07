import cv2
import numpy as np
from flask import Flask, render_template, Response

video = cv2.VideoCapture(0)
app = Flask('__name__')

def is_cup_shape(contour):
    perimeter = cv2.arcLength(contour, True)
    area = cv2.contourArea(contour)
    circularity = 4 * np.pi * area / (perimeter ** 2)
    return 0.5 < circularity < 1.0  # Adjust the circularity threshold as needed

def color_detection(frame):
    # Convert the BGR frame to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Define the lower and upper bounds for the turquoise color in HSV
    lower_turquoise = np.array([80, 50, 50])
    upper_turquoise = np.array([120, 255, 255])

    # Create a binary mask for turquoise pixels
    mask = cv2.inRange(hsv, lower_turquoise, upper_turquoise)

    # Find contours in the mask
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Filter contours based on area and circularity
    filtered_contours = [cnt for cnt in contours if cv2.contourArea(cnt) > 100 and is_cup_shape(cnt)]

    # Draw a blue rectangle and label "Cup" around each detected turquoise object
    for contour in filtered_contours:
        x, y, w, h = cv2.boundingRect(contour)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)  # Change color to blue (255, 0, 0)
        cv2.putText(frame, "Cup", (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2, cv2.LINE_AA)  # Change color to blue (255, 0, 0)

    return frame

def video_stream():
    while True:
        ret, frame = video.read()
        if not ret:
            break
        else:
            # Perform color detection, draw blue rectangles, and add labels
            modified_frame = color_detection(frame)

            # Encode the modified frame to JPEG format
            ret, buffer = cv2.imencode('.jpeg', modified_frame)
            frame = buffer.tobytes()

            # Yield the frame with boundary for streaming
            yield (b' --frame\r\n' b'Content-type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/camera')
def camera():
    print("showing camera feed")
    return render_template('templates/camera.html')

@app.route('/')
def home():
    return "Welcome to the stream! <a href='/camera'>Go to Camera</a>"

@app.route('/video_feed')
def video_feed():
    return Response(video_stream(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port='5000', debug=False)
