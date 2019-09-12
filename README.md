# Canny Edge Detection using ROS and OpenCV

The package canny_edge_my_face uses the machine's webcam (device id 0) to apply canny edge detection using OpenCV and ROS.
Real time images are captured and published as ROS Images using "cv_camera" package (which are then used by this package).

Run using the launch file "canny_edge_my_face.launch" to see canny_edge_my_face package in action.

The output can be seen by selecting the topic "/canny_edge_out" in rqt_image_view.
A sample output is saved in the package as "out_canny_edge_my_face.png"

Cheers!
