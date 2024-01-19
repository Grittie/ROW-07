# Video Streaming with Flask

This section provides documentation for the video streaming solution implemented in Flask for Beverage Bot.

## Flask Implementation

The video streaming solution utilizes the Flask web framework. The streaming functionality is implemented in the `streaming.py` script. This script includes the necessary code for capturing video frames, performing color detection, and streaming the modified frames to a web interface.

### Requirements

Make sure to install the required dependencies before running the Flask application. You can install the necessary packages using:

```bash
pip install Flask opencv-python numpy
```

### Code Overview

#### `streaming.py`

```python
import cv2
import numpy as np
from flask import Flask, render_template, Response

# Open the video capture device (camera)
video = cv2.VideoCapture(0)
app = Flask('__name__')

# ... (code for cup shape detection and color detection)

def video_stream():
    """
    Generator function to continuously capture video frames,
    perform color detection, and yield frames for streaming.
    """
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

# ... (Flask routes for rendering templates and streaming)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port='5000', debug=False)
```

#### Flask Routes

- `/camera`: Displays a simple HTML template (`camera.html`) to show the camera feed.
- `/`: Welcome page with a link to navigate to the camera feed.

### Running the Application

To run the Flask application, execute the following command in the terminal:

```bash
python streaming.py
```

This will start the Flask development server, and you can access the video stream at `http://localhost:5000/camera`.

## Related Documentation

For additional information and documentation, refer to the following related documents:

- [Video feed (app)](../app/video_feed.md)
- [Computer Vision](../pi/computervision.md)