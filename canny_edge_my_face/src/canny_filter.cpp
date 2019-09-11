#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class CannyEdge
{
  ros::NodeHandle n;
  image_transport::ImageTransport it;
  image_transport::Subscriber sub;
  image_transport::Publisher pub;

public:
  CannyEdge();
  void process_callback(const sensor_msgs::ImageConstPtr& img);
};

CannyEdge::CannyEdge():it(n)
{
  pub= it.advertise("/canny_edge_out",1);
  sub = it.subscribe("/cv_camera/image_raw",1, &CannyEdge::process_callback, this);

}

void CannyEdge::process_callback(const sensor_msgs::ImageConstPtr& img)
{
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
  return;
  }

  Mat OpenCvImg;
  
  //filter algorithm
  int threshold1 = 20;
  int threshold2 = 50;
  int kernelSize = 3;
  cvtColor(cv_ptr->image, OpenCvImg, CV_BGR2GRAY); //convert to grey
  blur(OpenCvImg, OpenCvImg, Size(3,3)); //smoothing with a kernel size 3
  Canny(OpenCvImg, OpenCvImg, threshold1, threshold2, kernelSize); //canny filter
  cvtColor(OpenCvImg, OpenCvImg, CV_GRAY2BGR); //converting to BGR again
  
  //converting Mat Obj to ROS image and publishing
  sensor_msgs::ImagePtr out = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::RGB8, (cv_ptr->image+OpenCvImg)).toImageMsg();
  pub.publish(out);

}
int main(int argc, char **argv)
{
  ros::init(argc,argv,"canny_edge_my_face");
  CannyEdge Obj;
  ros::spin();

  return 0;
}
