#!/bin/sh
xterm -e "source /opt/ros/melodic/setup.bash; roscore" &
sleep 2
xterm -e "rosrun rqt_image_view rqt_image_view"
