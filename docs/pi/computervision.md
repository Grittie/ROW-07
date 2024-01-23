# Computer Vision with OpenCV

This section provides documentation for the computer vision solution implemented using OpenCV for Beverage Bot.

## Objective: Cup Detection

The primary objective of the computer vision solution in Beverage Bot is to detect and identify cups in the video feed. This process involves utilizing OpenCV for real-time video analysis, specifically focusing on the recognition of turquoise-colored objects in the frame, which are indicative of cups.

### Target Features

The cup detection algorithm is designed to identify objects with the following features:

1. **Turquoise Color Detection:**
   - The algorithm looks for pixels within the turquoise color range in the HSV color space.
   - The lower and upper bounds for turquoise color in HSV are set to `[80, 50, 50]` and `[120, 255, 255]` respectively.

2. **Contour Analysis:**
   - Contours are extracted from the binary mask created after color detection.
   - Contours with an area greater than 100 pixels are considered for further analysis.

3. **Cup Shape Recognition:**
   - The circularity of each contour is calculated based on the perimeter and area.
   - Contours with circularity between 0.5 and 1.0 are considered as potential cup shapes.

### Implementation Details

The `streaming.py` script contains functions for capturing video frames, performing color detection, and identifying cup shapes in the video feed. The script uses Flask to create a web interface for streaming the modified video feed.

```python
# ... (Code for video capture, color detection, and streaming)

def is_cup_shape(contour):
    """
    Check if the contour represents a cup shape based on circularity.
    Adjust the circularity threshold as needed.
    """
    perimeter = cv2.arcLength(contour, True)
    area = cv2.contourArea(contour)
    circularity = 4 * np.pi * area / (perimeter ** 2)
    return 0.5 < circularity < 1.0  # Adjust the circularity threshold as needed

def color_detection(frame):
    """
    Perform color detection for turquoise objects in the frame.
    Draw blue rectangles and label "Cup" around each detected turquoise object.
    """
    # ... (Color detection and contour analysis)

def video_stream():
    """
    Generator function to continuously capture video frames,
    perform color detection, and yield frames for streaming.
    """
    # ... (Video streaming code)

# ... (Flask routes for rendering templates and streaming)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port='5000', debug=False)
```

### Running the Application

To initiate the Flask application with computer vision capabilities, execute the following command in the terminal:

```bash
python streaming.py
```

This will start the Flask development server, and you can access the video stream at `http://localhost:5000/camera`.

## Related Documentation

For additional information and documentation, refer to the following related documents:

- [Video feed (app)](../app/video_feed.md)
- [Video streaming](../pi/streaming.md)