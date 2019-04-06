#include <ros/ros.h>
#include "ErServer/ErSocket.h"
#include "ErServer/ErLog.h"
#include "ErServer/ErRobotStatus.h"
#include "ErServer/ErServercClient.h"
#include "ErServer/ErNetPacket.h"


#ifdef debug
husky_state_display()
{
     const char *strToSend="Hello Client";

    if (clientSock.write(strToSend, strlen(strToSend)) == (int) strlen(strToSend))
      ErLog::log(ErLog::Normal, "socketServerExample: Said hello to the client.");
    else
    {
      ErLog::log(ErLog::Normal, "socketServerExample: Error in sending hello string to the client.");
      return(-1);
    }
}
#endif


int main(int argc, char **argv)
{

    //进入ROS
  ros::init(argc, argv, "ErServer_node");
  ros::NodeHandle n;
  ROS_INFO("ErServer_node runing!");
  char buff[100];

  size_t strSize;




/*
  while (ros::ok()) {
     if (serverSock.accept(&clientSock))
        ROS_INFO( "Client  has connected.");
     else
       ROS_INFO(  "Error in accepting a connection from the client.");

   }*/

   //等待客户端连接以及收发数据
   ErServerClient ServerClient;

   if(ServerClient.openTcpSockets())
   {
     if(!ServerClient.acceptTcpSockets())
     {
        ROS_INFO("timeout waitting....");
        exit(-1);
     }
   }

   //
  ErRobotStatus RobotStatus;
  RobotStatus.updateNumbers(&ServerClient);
  ServerClient.sendData();



#ifdef debug
    //接送相关话题，发送相关机器state，激光数据，IMU数据给上位机
     ros::Subscriber husky_state_sub = n.subscribe("husky_node",1000,husky_state_display);

     //定义相关发送的话题
     ros::Publisher  husky_cmd_pub=n.advertise<>("host_comput_cmd",1000);
     ros::Rate loop_rate(10);
     // Read data from the client. read() will block until data is
     // received.

     while(ros::ok())
      {
           strSize=clientSock.read(buff, sizeof(buff));
         // If the amount read is 0 or less, its an error condition.
         if (strSize > 0)
         {
           buff[strSize]='\0';
           ErLog::log(ErLog::Normal, "socketServerExample: Client said: %s.", buff);
         }
         else
         {
           ErLog::log(ErLog::Normal, "socketServerExample: Error in waiting/reading the hello from the client.");
           return(-1);
         }
         ros::spinOnce();
         loop_rate.sleep();
     }

   // And lets close the server port
   serverSock.close();
   ROS_INFO("Server socket closed.");
#endif
   return(0);
}
