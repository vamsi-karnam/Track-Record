#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Initialize the video device
    cv::VideoCapture cap(0); // 0 is the default camera
    cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
    if (!cap.isOpened())
    {
        std::cerr << "Unable to open the camera." << std::endl;
        return -1;
    }

    // Loading face detection model
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"))
    {
        std::cerr << "Unable to load the face detection model." << std::endl;
        return -1;
    }

    // Capture frames from the webcam
    cv::Mat frame;
    while (cap.read(frame))
    {
        // face detection works better on grayscale images
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect faces in the grayscale image
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        // Draw a rectangle around each face
        for (const auto& face : faces)
        {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        // Output the frame
        cv::imshow("Webcam Feed", frame);

        // Exit on pressing 'c' inside the frame
        if (cv::waitKey(1) == 'c')
        {
            break;
        }
    }

    return 0;
}
