const string useCameraInput()
{
    VideoCapture cap(0); 

    if(!cap.isOpened()){
    cout << "Error opening video stream" << endl;
        return "error";
    }

    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    const String fileName = "camera.avi";
    VideoWriter video("camera.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, Size(frame_width,frame_height));
    while(1) {

    Mat frame;

    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
        break;
        
    // Write the frame into the file 'outcpp.avi'
    video.write(frame);
    cv::putText(frame, 
            "press ESC to stop recording",
            cv::Point(10, frame.rows / 4),
            cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(118, 185, 0),2);

    // Display the resulting frame    
    imshow( "Frame", frame );

    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 27 ) 
        break;
    }

    // When everything done, release the video capture and write object
    cap.release();
    video.release();

    // Closes all the frames
    destroyAllWindows();
    return fileName;
}