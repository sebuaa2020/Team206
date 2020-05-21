/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2017-2020, Waterplus http://www.6-robot.com
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the WaterPlus nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  FOOTPRINTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/
/*!******************************************************************
 @author     ZhangWanjie
 ********************************************************************/

#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/surface/convex_hull.h>
#include <pcl/segmentation/extract_polygonal_prism_data.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/segmentation/extract_clusters.h>
#include <image_geometry/pinhole_camera_model.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <sensor_msgs/Image.h>
#include <pcl_ros/transforms.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/String.h>
#include <sound_play/SoundRequest.h>
#include <geometry_msgs/Pose2D.h>
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

// ץȡ�������ڣ���λ���ף�
static float grab_y_offset = 0.0f;          //ץȡǰ����׼��Ʒ�������˵ĺ���λ��ƫ����
static float grab_lift_offset = 0.0f;       //�ֱ�̧��߶ȵĲ���ƫ����
static float grab_forward_offset = 0.0f;    //�ֱ�̧��󣬻�������ǰץȡ��Ʒ�ƶ���λ��ƫ����
static float grab_gripper_value = 0.032;    //ץȡ��Ʒʱ����צ�պϺ����ָ���
// ��е��״̬ 
#define STATE_WAIT           0
#define STATE_FIND_TABLEX     1		//����ƽ��	ȷ��Xֵ
#define STATE_TO_TABLEX     2		//�ҵ�ƽ�����Ƶ�ƽ����� 
#define STATE_FIND_TABLEY       3		//����Ŀ����	ȷ��Yֵ
#define STATE_TO_TABLEY       4		//�ҵ�Ŀ�����������ƶ�����Ӧλ�� 
#define STATE_FIND_OBJ        5
#define STATE_TO_OBJ        6
#define STATE_ADJUST_HEIGHT           7
#define STATE_GRAB         8
#define STATE_BACKWARD       9
#define STATE_DONE           10
static int nStep = STATE_WAIT;	//��е�����ȴ��ڵȴ�״̬ 

static std::string pc_topic;
static ros::Publisher pc_pub;
static ros::Publisher marker_pub;
static ros::Publisher vel_pub;
static ros::Publisher mani_ctrl_pub;
static sensor_msgs::JointState mani_ctrl_msg;	//��е�ۿ�����Ϣ����
static ros::Publisher result_pub;
static tf::TransformListener *tf_listener; 

void DrawBox(float inMinX, float inMaxX, float inMinY, float inMaxY, float inMinZ, float inMaxZ, float inR, float inG, float inB);
void DrawText(std::string inText, float inScale, float inX, float inY, float inZ, float inR, float inG, float inB);
void DrawPath(float inX, float inY, float inZ);
void RemoveBoxes();
void VelCmd(float inVx , float inVy, float inTz);

static visualization_msgs::Marker line_box;
static visualization_msgs::Marker line_follow;
static visualization_msgs::Marker text_marker;

typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloud;
ros::Publisher segmented_plane;
ros::Publisher segmented_objects;
ros::Publisher masking;
ros::Publisher color;
static std_msgs::String result_msg;

static ros::Publisher ctrl_pub;
static std_msgs::String ctrl_msg;
static geometry_msgs::Pose2D pose_diff;

static float fObjGrabX = 0;
static float fObjGrabY = 0;
static float fObjGrabZ = 0;
static float fMoveTargetX = 0;
static float fMoveTargetY = 0;
static bool nPlaneDistMode = 1;
cv::Mat rgb_image;

typedef struct stBoxMarker
{
    float xMax;
    float xMin;
    float yMax;
    float yMin;
    float zMax;
    float zMin;
}stBoxMarker;

static stBoxMarker boxMarker;
static stBoxMarker boxPlane;
static stBoxMarker obj_to_track;


static int nTimeDelayCounter = 0;
static int nFrameCount = 0;
static float fLastPlaneHeight = 0.5;	//��һ�μ���¼�ĸ߶�ֵ
static float fPlaneHeight = 0;			//����һ�μ���¼�ĸ߶�ֵ
static int nPlaneHeightCounter = 0;		//��⵽ƽ�����

static float fPlaneDist = 0;			//������֮���ʵ�ʾ���
static float fTargetPlaneDist = 0.6;    //������֮���Ŀ�����
static float fTargetGrabX = 0.8;        //ץȡʱĿ����Ʒ��x����
static float fTargetGrabY = 0.0;        //ץȡʱĿ����Ʒ��y����

static std::vector<stBoxMarker> vObj;        
static stBoxMarker boxLastObject;
static int nObjDetectCounter = 0;		//��⵽Ŀ����Ʒ������

void ProcCloudCB(const sensor_msgs::PointCloud2 &input)
{
    //ROS_WARN("ProcCloudCB");

    //to footprint
    sensor_msgs::PointCloud2 pc_footprint;
    tf_listener->waitForTransform("/base_footprint", input.header.frame_id, input.header.stamp, ros::Duration(5.0));  //return value always  false!
    pcl_ros::transformPointCloud("/base_footprint", input, pc_footprint, *tf_listener);

    //source cloud
    pcl::PointCloud<pcl::PointXYZRGB> cloud_src;
    pcl::fromROSMsg(pc_footprint , cloud_src);
    //ROS_INFO("cloud_src size = %d",cloud_src.size()); 
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_source_ptr;
    //////////////////////////////////////////////////
    //1��ԭʼ����
    //cloud_source_ptr = cloud_src.makeShared(); 
    /////////////////////////////////////////////////
    //2���¹���һ�����ƣ�ֻȡһ����
    pcl::PointCloud<pcl::PointXYZRGB> new_point_cloud;
    int nSize = cloud_src.points.size();
    for(int i=0;i<nSize;i++)
    {
        pcl::PointXYZRGB p = cloud_src.points[i];
        if(
            p.x < 1.2 &&
            p.y > -1.0 &&
            p.y < 1.0
        )
        {
            new_point_cloud.push_back(p);
        }
    }
    cloud_source_ptr = new_point_cloud.makeShared(); 
    //////////////////////////////////////////////////
    
    /*һ�����ݴ��� *************************************************************************************************/
    if( nStep == STATE_FIND_TABLEX || nStep == STATE_FIND_TABLEY)
    {
        // Process
        //ROS_INFO("Cloud: width = %d, height = %d\n", input.width, input.height);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr plane(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr convexHull(new pcl::PointCloud<pcl::PointXYZRGB>);

        // Get the plane model, if present.
        pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
        pcl::SACSegmentation<pcl::PointXYZRGB> segmentation;
        segmentation.setInputCloud(cloud_source_ptr);
        segmentation.setModelType(pcl::SACMODEL_PLANE);
        segmentation.setMethodType(pcl::SAC_RANSAC);
        segmentation.setDistanceThreshold(0.005);
        segmentation.setOptimizeCoefficients(true);
        pcl::PointIndices::Ptr planeIndices(new pcl::PointIndices);
        segmentation.segment(*planeIndices, *coefficients);
        //ROS_INFO_STREAM("Num_Of_Planes = " << planeIndices->indices.size());
        pcl::ExtractIndices<pcl::PointXYZRGB> extract;

        RemoveBoxes();
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZRGB>);
        int i = 0, nr_points = (int) cloud_source_ptr->points.size ();
        // While 30% of the original cloud is still there
        while (cloud_source_ptr->points.size () > 0.03 * nr_points)
        {
            // Segment the largest planar component from the remaining cloud
            segmentation.setInputCloud (cloud_source_ptr);
            segmentation.segment (*planeIndices, *coefficients);
            if (planeIndices->indices.size () == 0)
            {
                ROS_WARN("Could not estimate a planar model for the given dataset.");
                break;
            }

            // Extract the planeIndices
            extract.setInputCloud (cloud_source_ptr);
            extract.setIndices (planeIndices);
            extract.setNegative (false);
            extract.filter (*plane);
            float plane_height = 0;
            for(int k=0; k<plane->width * plane->height ;k ++ )
            {
                plane_height += plane->points[k].z;
            }
            plane_height /= plane->width * plane->height;
            //ROS_WARN("%d - plane: %d points. height =%.2f" ,i, plane->width * plane->height,plane_height);
            fPlaneHeight = plane_height;
           
            bool bFirstPoint = true;
            for (int j = 0; j < plane->points.size(); j++) 
            {
                pcl::PointXYZRGB p = plane->points[j];
                if(bFirstPoint == true)
                {
                    boxPlane.xMax = boxPlane.xMin = p.x;
                    boxPlane.yMax = boxPlane.yMin = p.y;
                    boxPlane.zMax = boxPlane.zMin = p.z;
                    bFirstPoint = false;
                }

                if(p.x < boxPlane.xMin) { boxPlane.xMin = p.x;}
                if(p.x > boxPlane.xMax) { boxPlane.xMax = p.x;}
                if(p.y < boxPlane.yMin) { boxPlane.yMin = p.y;}
                if(p.y > boxPlane.yMax) { boxPlane.yMax = p.y;}
                if(p.z < boxPlane.zMin) { boxPlane.zMin = p.z;}
                if(p.z > boxPlane.zMax) { boxPlane.zMax = p.z;}
            } 
            //////////////////////////////////
            //���ԣ���ƽ���ÿ�������
            DrawBox(boxPlane.xMin, boxPlane.xMax, boxPlane.yMin, boxPlane.yMax, boxPlane.zMin, boxPlane.zMax, 1, 0, 1);
            //ROS_WARN("[FIND_PLANE] x= (%.2f , %.2f) y=(%.2f , %.2f) z=(%.2f , %.2f)" ,boxPlane.xMin,boxPlane.xMax,boxPlane.yMin,boxPlane.yMax,boxPlane.zMin,boxPlane.zMax);
            ///////////////////////////////////
            if(plane_height > 0.5 && plane_height < 0.85) 
            break;

            // Create the filtering object
            extract.setNegative (true);
            extract.filter (*cloud_f);
            cloud_source_ptr.swap (cloud_f);
            i++;
        }

        if (planeIndices->indices.size() == 0)
            std::cout << "Could not find a plane in the scene." << std::endl;
        else
        {
            // Copy the points of the plane to a new cloud.
            extract.setInputCloud(cloud_source_ptr);
            extract.setIndices(planeIndices);
            extract.filter(*plane);

            // Retrieve the convex hull.(����͹��)
            pcl::ConvexHull<pcl::PointXYZRGB> hull;
            hull.setInputCloud(plane);
            // Make sure that the resulting hull is bidimensional.
            hull.setDimension(2);
            hull.reconstruct(*convexHull);

            // Redundant check.
            if (hull.getDimension() == 2)
            {
                segmented_plane.publish(plane); //��RVIZ����ʾƽ��
                if(nStep == STATE_FIND_TABLEY )
                {
                    pcl::PointCloud<pcl::PointXYZRGB>::Ptr objects(new pcl::PointCloud<pcl::PointXYZRGB>);
                    // Prism object.(���ڷָ������ģ���ڲ��ĵ㼯)
                    pcl::ExtractPolygonalPrismData<pcl::PointXYZRGB> prism;
                    prism.setInputCloud(cloud_source_ptr);
                    prism.setInputPlanarHull(convexHull);
                    prism.setHeightLimits(-0.30, -0.05); //height limit objects lying on the plane (����߶ȷ�Χ)
                    pcl::PointIndices::Ptr objectIndices(new pcl::PointIndices);

                    //Get and show all points retrieved by the hull.
                    prism.segment(*objectIndices);
                    extract.setIndices(objectIndices);
                    extract.filter(*objects);
                    segmented_objects.publish(objects); //������Ʒ�ĵ㼯

                    // run clustering extraction on "objects" to get several pointclouds
                    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
                    pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
                    std::vector<pcl::PointIndices> cluster_indices;
                    ec.setClusterTolerance (0.02);  //���������������뾶
                    ec.setMinClusterSize (500);     //����������Ҫ�����ٵ���Ŀ
                    ec.setMaxClusterSize (10000000);//����������Ҫ��������Ŀ
                    ec.setSearchMethod (tree);      //���õ��Ƶ���������
                    ec.setInputCloud (objects);     //������Ʒ������
                    ec.extract (cluster_indices);   //�ӵ�������ȡ����

                    pcl::ExtractIndices<pcl::PointXYZRGB> extract_object_indices;//������Ʒ��ȡ����
                    std::vector<pcl::PointCloud<pcl::PointXYZRGB> > objectf;
                    cv::Mat element;

                    vObj.clear();
                    int nObjCnt = 0;
                    for(int i = 0; i<cluster_indices.size(); ++i)
                    {
                        pcl::PointCloud<pcl::PointXYZRGB>::Ptr object_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
                        extract_object_indices.setInputCloud(objects);          //����Ʒ������ȫ������
                        extract_object_indices.setIndices(boost::make_shared<const pcl::PointIndices>(cluster_indices[i]));
                        extract_object_indices.filter(*object_cloud);           //��ȡ����洢��object_cloud
                        objectf.push_back(*object_cloud);

                        //ͳ�Ƹ���Ʒ���ƵĿռ䷶Χ
                        bool bFirstPoint = true;
                        for (int j = 0; j < object_cloud->points.size(); j++) 
                        {
                            pcl::PointXYZRGB p = object_cloud->points[j];
                            if(bFirstPoint == true)
                            {
                                boxMarker.xMax = boxMarker.xMin = p.x;
                                boxMarker.yMax = boxMarker.yMin = p.y;
                                boxMarker.zMax = boxMarker.zMin = p.z;
                                bFirstPoint = false;
                            }

                            if(p.x < boxMarker.xMin) { boxMarker.xMin = p.x;}
                            if(p.x > boxMarker.xMax) { boxMarker.xMax = p.x;}
                            if(p.y < boxMarker.yMin) { boxMarker.yMin = p.y;}
                            if(p.y > boxMarker.yMax) { boxMarker.yMax = p.y;}
                            if(p.z < boxMarker.zMin) { boxMarker.zMin = p.z;}
                            if(p.z > boxMarker.zMax) { boxMarker.zMax = p.z;}

                        }
                        if(boxMarker.xMin < 1.5 && boxMarker.yMin > -0.5 && boxMarker.yMax < 0.5)   //��Ʒ�����Ŀռ��޶�
                        {
                            DrawBox(boxMarker.xMin, boxMarker.xMax, boxMarker.yMin, boxMarker.yMax, boxMarker.zMin, boxMarker.zMax, 0, 1, 0);

                            std::ostringstream stringStream;
                            stringStream << "obj_" << nObjCnt;
                            std::string obj_id = stringStream.str();
                            DrawText(obj_id,0.08, boxMarker.xMax,(boxMarker.yMin+boxMarker.yMax)/2,boxMarker.zMax + 0.04, 1,0,1);
                            nObjCnt++;
                            //ROS_WARN("[obj_%d] xMin= %.2f yMin = %.2f yMax = %.2f",i,boxMarker.xMin, boxMarker.yMin, boxMarker.yMax);
                            vObj.push_back(boxMarker);
                        } 
                    }
                    //����Ʒ��������д���
                    if(nObjCnt > 0)
                    {
                        if(nObjDetectCounter == 0)
                        {
                            //��һ֡��¼��м����Ʒ
                            int nNumObj = vObj.size();
                            if(nNumObj > 0)
                            {
                                float fMidY = (vObj[0].yMin + vObj[0].yMax)/2;
                                boxLastObject = vObj[0];
                                for(int i=0;i<nNumObj;i++)
                                {
                                    float fTmpMidY = (vObj[i].yMin + vObj[i].yMax)/2;
                                    if(fabs(fTmpMidY) < fabs(fMidY))
                                    {
                                        boxLastObject = vObj[i];
                                    }
                                }
                                nObjDetectCounter ++;
                            }
                            else
                            {
                                ROS_WARN("[FIND_OBJ] nNumObj <= 0 ...");  //������Ч��
                            }
                        }
                        else
                        {
                            //�����֡���֮ǰ��¼����Ʒ���ڲ���
                            float fMidY = (boxLastObject.yMin + boxLastObject.yMax)/2;
                            int nNearIndex = 0;
                            float fNearDiff = fabs((vObj[0].yMin + vObj[0].yMax)/2 - fMidY);
                            int nNumObj = vObj.size();
                            if(nNumObj > 0)
                            {
                                for(int i=0;i<nNumObj;i++)
                                {
                                    float fTmpMidY = (vObj[i].yMin + vObj[i].yMax)/2;
                                    float fTmpDiff = fabs(fTmpMidY - fMidY);
                                    //ROS_WARN("[4_FIND_OBJ] fTmpMidY = %.2f  fTmpDiff = %.2f",fTmpMidY,fTmpDiff);
                                    if( fabs(fTmpDiff) <= fNearDiff )
                                    {
                                        boxLastObject = vObj[i];
                                        fNearDiff = fabs(fTmpDiff);
                                        if(nStep == STATE_FIND_TABLEY)
                                        {
                                            nObjDetectCounter ++;
                                            ROS_WARN("[FIND_OBJ] nObjDetectCounter = %d",nObjDetectCounter);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        nObjDetectCounter = 0;
                        ROS_WARN("[FIND_OBJ] nObjCnt <= 0 No object detected ...");
                    }
                }
                else
                {
                    //����Ҫ�����Ʒʱ����������ƽ�����ݼ���
                    segmented_plane.publish(plane); 
                }
                

            }
            else std::cout << "The chosen hull is not planar." << std::endl;
        }
    }

    /*��������״̬�� *************************************************************************************************/
    //1��ͳ��ʶ�������ȷ��ƽ��
    if(nStep == STATE_FIND_TABLEX)  //(���ƴ����㷨������)
    {
        mani_ctrl_msg.position[0] = 0;
        mani_ctrl_msg.position[1] = 0.16;
        mani_ctrl_pub.publish(mani_ctrl_msg);
        VelCmd(0,0,0);
        ctrl_msg.data = "pose_diff reset";
        ctrl_pub.publish(ctrl_msg);
        if(fabs(fPlaneHeight - fLastPlaneHeight) < 0.05)
        {
            nPlaneHeightCounter ++;				//���Ȳ�����0.05�����ɹ��ҵ�
        }
        else
        {
            nPlaneHeightCounter = 0;
        }
        fLastPlaneHeight = fPlaneHeight;
        ROS_WARN("[FIND_PLANE] z= %.2f xm= %.2f y=(%.2f , %.2f) counter= %d" ,fPlaneHeight,boxPlane.xMin,boxPlane.yMin,boxPlane.yMax,nPlaneHeightCounter);
        if(nPlaneHeightCounter > 10)			//����ʮ�β���ֵ��������0.05��Ĭ���ҵ�
        {
            nPlaneHeightCounter = 0;
            nTimeDelayCounter = 0;
            nStep = STATE_TO_TABLEX;			//X��������������һ����Ҫ����X������ƶ�
            fMoveTargetX = boxPlane.xMin - 0.7;		
            fMoveTargetY = 0;
        }
        result_msg.data = "find plane";
        result_pub.publish(result_msg);
    }

    //2��ǰ���˶����Ƶ�ƽ��ľ���
    if(nStep == STATE_TO_TABLEX && nPlaneDistMode == 1)
    {
        float fMinDist = 100;
        for (int i = 0; i < cloud_source_ptr->points.size(); i++) 
        {
            pcl::PointXYZRGB p = cloud_source_ptr->points[i];
            if(
                p.y > -0.2 && p.y < 0.2 && 
                p.z > fPlaneHeight-0.05 && p.z < fPlaneHeight+0.05 && 
                p.x < fMinDist)
            {
                fMinDist = p.x;
            }
        }
        fPlaneDist = fMinDist;
        ROS_WARN("[PLANE_DIST] dist= %.2f" ,fPlaneDist);
        float diff = fPlaneDist - fTargetPlaneDist;
        if(fabs(diff) < 0.02)		//X����ǰ����Ŀ��ƽ������0.02ʱ����ΪX���򵽴�ָ��λ��
        {
            nObjDetectCounter = 0;
            nStep = STATE_FIND_TABLEY;		//��һ��ȷ��Y����λ��
            VelCmd(0,0,0);
        } 
        else			//X�����ϻ����˽����˶�
        {
            if(diff > 0)
            {
                //���뻹̫Զ��ǰ��
                VelCmd(0.1,0,0);
            }
            else
            {
                //���뻹̫��������
                VelCmd(-0.1,0,0);
            }
        }

        result_msg.data = "plane dist";
        result_pub.publish(result_msg);
    }

    //3�������Ʒ����ѡ��׼��ץȡ��Ŀ����Ʒ
    if(nStep == STATE_FIND_TABLEY)  //(���ƴ����㷨������)
    {
        VelCmd(0,0,0);
        ctrl_msg.data = "pose_diff reset";
        ctrl_pub.publish(ctrl_msg);
        if(nObjDetectCounter > 3)			//�����⵽��Ŀ���ﳬ��3������С��ⷶΧ��������Ŀ����
        {
            nObjDetectCounter = 0;
            // Ŀ����Ʒ������
            fObjGrabX = (boxLastObject.xMin + boxLastObject.xMax)/2;                              //Changed
            fObjGrabY = (boxLastObject.yMin+boxLastObject.yMax)/2;		//x��y������ȡ�м�ֵ
            fObjGrabZ = boxLastObject.zMax;                        //Changed��z����ȡĿ�������ֵ
            ROS_WARN("[OBJ_TO_GRAB] x = %.2f y= %.2f ,z= %.2f w= %.2f" ,fObjGrabX, fObjGrabY, fObjGrabZ,boxLastObject.yMin - boxLastObject.yMax);

            // �ж�һ����Ʒ�����ӱ�Ե�ľ��룬����ŵ�̫�������ץȡ���������ײ������
            if(fabs(fObjGrabX - fTargetPlaneDist) > 0.4 )   //Ŀ����Ʒ�������ӵı�Ե
            {
                ROS_WARN("[OBJ_TO_GRAB] Object is hard to reach !!!");
                nStep = STATE_DONE;
            }
            else
            {
                fMoveTargetX = 0.0f;
                fMoveTargetY = fObjGrabY - fTargetGrabY + grab_y_offset;
                //ROS_WARN("[MOVE_TARGET] x = %.2f y= %.2f " ,fMoveTargetX, fMoveTargetY);
                nStep = STATE_TO_TABLEY;		//Y�������������һ����Ҫ����Y������ƶ�
            }
        }

        result_msg.data = "find objects";
        result_pub.publish(result_msg);
    }

    //5��̧���ֱ�
    if(nStep == STATE_FIND_OBJ)
    {
        if(nTimeDelayCounter == 0)
        {
            mani_ctrl_msg.position[0] = fPlaneHeight + grab_lift_offset;
            mani_ctrl_msg.position[1] = 0.16;
            mani_ctrl_pub.publish(mani_ctrl_msg);
            ROS_WARN("[MANI_CTRL] lift= %.2f  gripper= %.2f " ,mani_ctrl_msg.position[0], mani_ctrl_msg.position[1]);
            result_msg.data = "hand up";
            result_pub.publish(result_msg);
        }
        nTimeDelayCounter ++;
        VelCmd(0,0,0);
        if(nTimeDelayCounter > 50)			//ͨ��50����Ϣ����ȷ��׼ȷ��
        {
            fMoveTargetX = fObjGrabX -0.55 + grab_forward_offset;
            fMoveTargetY = 0;
            ROS_WARN("[STATE_TO_OBJ] x = %.2f y= %.2f " ,fMoveTargetX, fMoveTargetY);
            nTimeDelayCounter = 0;
            nStep = STATE_TO_OBJ;			//��е��X�������ƶ�
        }
    }
   
    //7��ץȡ��Ʒ
    if(nStep == STATE_ADJUST_HEIGHT)
    {
        if(nTimeDelayCounter == 0)
        {
            result_msg.data = "grab";
            result_pub.publish(result_msg);
        }
        mani_ctrl_msg.position[1] = grab_gripper_value;      //ץȡ��Ʒ��צ�պϿ��
        mani_ctrl_pub.publish(mani_ctrl_msg);
        //ROS_WARN("[MANI_CTRL] lift= %.2f  gripper= %.2f " ,mani_ctrl_msg.position[0], mani_ctrl_msg.position[1]);

        nTimeDelayCounter++;
        VelCmd(0,0,0);
        if(nTimeDelayCounter > 30)			//ͨ��30����Ϣ����ȷ����צ�պϿ���趨��׼ȷ�ԴӶ�ץ����Ʒ
        {
            nTimeDelayCounter = 0;
            nStep = STATE_GRAB;
        }
    }
    //8��������Ʒ
    if(nStep == STATE_GRAB)
    {
        if(nTimeDelayCounter == 0)
        {
            mani_ctrl_msg.position[0] += 0.03;
            mani_ctrl_pub.publish(mani_ctrl_msg);
            //ROS_WARN("[MANI_CTRL] lift= %.2f  gripper= %.2f " ,mani_ctrl_msg.position[0], mani_ctrl_msg.position[1]);
            result_msg.data = "object up";
            result_pub.publish(result_msg);
        }
        nTimeDelayCounter++;
        VelCmd(0,0,0);
        if(nTimeDelayCounter > 10)
        {
            fMoveTargetX = -(fTargetGrabX-0.4);
            fMoveTargetY = 0;
            //ROS_WARN("[STATE_BACKWARD] x= %.2f y= %.2f " ,fMoveTargetX, fMoveTargetY);

            nTimeDelayCounter = 0;
            nStep = STATE_BACKWARD;			
        }
    }
    
    //10��ץȡ�������
    if(nStep == STATE_DONE)
    {
        result_msg.data = "done";
        result_pub.publish(result_msg);
    }
}

void PoseDiffCallback(const geometry_msgs::Pose2D::ConstPtr& msg)
{
    pose_diff.x = msg->x;
    pose_diff.y = msg->y;
    pose_diff.theta = msg->theta;
}

void DrawBox(float inMinX, float inMaxX, float inMinY, float inMaxY, float inMinZ, float inMaxZ, float inR, float inG, float inB)
{
    line_box.header.frame_id = "base_footprint";
    line_box.ns = "line_box";
    line_box.action = visualization_msgs::Marker::ADD;
    line_box.id = 0;
    line_box.type = visualization_msgs::Marker::LINE_LIST;
    line_box.scale.x = 0.005;
    line_box.color.r = inR;
    line_box.color.g = inG;
    line_box.color.b = inB;
    line_box.color.a = 1.0;

    geometry_msgs::Point p;
    p.z = inMinZ;
    p.x = inMinX; p.y = inMinY; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMaxY; line_box.points.push_back(p);

    p.x = inMinX; p.y = inMaxY; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMaxY; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMaxY; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMinY; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMinY; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMinY; line_box.points.push_back(p);

    p.z = inMaxZ;
    p.x = inMinX; p.y = inMinY; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMaxY; line_box.points.push_back(p);

    p.x = inMinX; p.y = inMaxY; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMaxY; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMaxY; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMinY; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMinY; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMinY; line_box.points.push_back(p);

    p.x = inMinX; p.y = inMinY; p.z = inMinZ; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMinY; p.z = inMaxZ; line_box.points.push_back(p);

    p.x = inMinX; p.y = inMaxY; p.z = inMinZ; line_box.points.push_back(p);
    p.x = inMinX; p.y = inMaxY; p.z = inMaxZ; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMaxY; p.z = inMinZ; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMaxY; p.z = inMaxZ; line_box.points.push_back(p);

    p.x = inMaxX; p.y = inMinY; p.z = inMinZ; line_box.points.push_back(p);
    p.x = inMaxX; p.y = inMinY; p.z = inMaxZ; line_box.points.push_back(p);
    marker_pub.publish(line_box);
}

static int nTextNum = 2;
void DrawText(std::string inText, float inScale, float inX, float inY, float inZ, float inR, float inG, float inB)
{
    text_marker.header.frame_id = "base_footprint";
    text_marker.ns = "line_obj";
    text_marker.action = visualization_msgs::Marker::ADD;
    text_marker.id = nTextNum;
    nTextNum ++;
    text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    text_marker.scale.z = inScale;
    text_marker.color.r = inR;
    text_marker.color.g = inG;
    text_marker.color.b = inB;
    text_marker.color.a = 1.0;

    text_marker.pose.position.x = inX;
    text_marker.pose.position.y = inY;
    text_marker.pose.position.z = inZ;
    
    text_marker.pose.orientation=tf::createQuaternionMsgFromYaw(1.0);

    text_marker.text = inText;

    marker_pub.publish(text_marker);
}

void RemoveBoxes()
{
    line_box.action = 3;
    line_box.points.clear();
    marker_pub.publish(line_box);
    line_follow.action = 3;
    line_follow.points.clear();
    marker_pub.publish(line_follow);
    text_marker.action = 3;
    marker_pub.publish(text_marker);
}

void VelCmd(float inVx , float inVy, float inTz)		//�������˶�
{
    geometry_msgs::Twist vel_cmd;
    vel_cmd.linear.x = inVx;
    vel_cmd.linear.y = inVy;
    vel_cmd.angular.z = inTz;
    vel_pub.publish(vel_cmd);
}

void BehaviorCB(const std_msgs::String::ConstPtr &msg)
{
    int nFindIndex = 0;
    nFindIndex = msg->data.find("grab start");
    if( nFindIndex >= 0 )
    {
        VelCmd(0,0,0);
        nStep = STATE_FIND_TABLEX;
        ROS_WARN("[grab_start] ");
    }

    nFindIndex = msg->data.find("grab stop");
    if( nFindIndex >= 0 )
    {
        ROS_WARN("[grab_stop] ");
        nStep = STATE_WAIT;
        geometry_msgs::Twist vel_cmd;
        vel_cmd.linear.x = 0;
        vel_cmd.linear.y = 0;
        vel_cmd.linear.z = 0;
        vel_cmd.angular.x = 0;
        vel_cmd.angular.y = 0;
        vel_cmd.angular.z = 0;
        vel_pub.publish(vel_cmd);
    }

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "wpb_home_grab_108");             //108��Ĺ��ˣ�����wpb_home_grab_108�ڵ�
    ROS_INFO("wpb_home_grab_108");                          //Changed
    tf_listener = new tf::TransformListener(); 

    ros::NodeHandle nh_param("~");
    nh_param.param<std::string>("topic", pc_topic, "/kinect2/sd/points");

    ros::NodeHandle nh;				//nh�ʹ����ʼ�����ɵĽڵ�
    ros::Subscriber pc_sub = nh.subscribe(pc_topic, 10 , ProcCloudCB);	//pc_sub�ǽ���pc_topic��Ϣ�Ľڵ㣬ÿ�ν��պ�ִ��ProcCloudCB����

    pc_pub = nh.advertise<sensor_msgs::PointCloud2>("obj_pointcloud",1); //pc_pub�Ƿ���pc_topic�Ľڵ�
    marker_pub = nh.advertise<visualization_msgs::Marker>("obj_marker", 10);

    segmented_objects = nh.advertise<PointCloud> ("segmented_objects",1);
    segmented_plane = nh.advertise<PointCloud> ("segmented_plane",1);
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 30);
    mani_ctrl_pub = nh.advertise<sensor_msgs::JointState>("/wpb_home/mani_ctrl", 30);	//��е����Ϣ�������󣬸��𴫵�mani_ctrl_msg��Ϣ
    result_pub = nh.advertise<std_msgs::String>("/wpb_home/grab_result", 30);			//�ַ�����Ϣ���ݶ��󣬸��𴫵��ַ�����Ϣ

    ros::Subscriber sub_sr = nh.subscribe("/wpb_home/behaviors", 30, BehaviorCB);
    ctrl_pub = nh.advertise<std_msgs::String>("/wpb_home/ctrl", 30);
    ros::Subscriber pose_diff_sub = nh.subscribe("/wpb_home/pose_diff", 1, PoseDiffCallback);	//λ����Ϣ���ն���

	//��ʼ����е�۲���״̬����
    mani_ctrl_msg.name.resize(2);
    mani_ctrl_msg.position.resize(2);
    mani_ctrl_msg.velocity.resize(2);
    mani_ctrl_msg.name[0] = "lift";
    mani_ctrl_msg.name[1] = "gripper";
    mani_ctrl_msg.position[0] = 0;		 //�����߶� 
    mani_ctrl_msg.velocity[0] = 0.5;     //�����ٶ�(��λ:��/��)
    mani_ctrl_msg.position[1] = 0.16;	 //��צָ��� 
    mani_ctrl_msg.velocity[1] = 5;       //��צ���Ͻ��ٶ�(��λ:��/��)
	

	//ץȡǰ��ȡһЩ������Ϣ
    nh_param.getParam("grab/grab_y_offset", grab_y_offset); //ץȡǰ����׼��Ʒ�������˵ĺ���λ��ƫ����
    nh_param.getParam("grab/grab_lift_offset", grab_lift_offset); //�ֱ�̧��߶ȵĲ���ƫ����
    nh_param.getParam("grab/grab_forward_offset", grab_forward_offset); //�ֱ�̧��󣬻�������ǰץȡ��Ʒ�ƶ���λ��ƫ����
    nh_param.getParam("grab/grab_gripper_value", grab_gripper_value);//ץȡ��Ʒʱ����צ�պϺ����ָ���
	
    bool bActive = false;
    nh_param.param<bool>("start", bActive, false);
    
    //���Կ�ʼ���
    if(bActive == true)
    {
        VelCmd(0,0,0);
        nStep = STATE_FIND_TABLEX;
    }
	
    ros::Rate r(30);		//���ú�Ƶ��Ϊ30HZ��1��30��
    while(nh.ok())			//��ʼѭ�������ýڵ����ʱ�˳�ѭ��
    {
        //2��ǰ���˶����Ƶ�ƽ��ľ���(�ҵ�����(ƽ��)����ƾ���)
        if(nStep == STATE_TO_TABLEX && nPlaneDistMode == 2)
        {
            float vx,vy;
            vx = (fMoveTargetX - pose_diff.x)/2;
            vy = (fMoveTargetY - pose_diff.y)/2;

            VelCmd(vx,vy,0);

            //ROS_INFO("[MOVE] T(%.2f %.2f)  od(%.2f , %.2f) v(%.2f,%.2f)" ,fMoveTargetX, fMoveTargetY, pose_diff.x ,pose_diff.y,vx,vy);

            if(fabs(vx) < 0.01 && fabs(vy) < 0.01)
            {
                VelCmd(0,0,0);
                ctrl_msg.data = "pose_diff reset";
                ctrl_pub.publish(ctrl_msg);
                nStep = STATE_FIND_TABLEY;
            }

            result_msg.data = "plane dist";
            result_pub.publish(result_msg);		//����plane dist�ַ�����ɵ�Message
        }
    
        //4������ƽ�ƶ�׼Ŀ����Ʒ 
        if(nStep == STATE_TO_TABLEY)
        {
            float vx,vy;
            vx = (fMoveTargetX - pose_diff.x)/2;
            vy = (fMoveTargetY - pose_diff.y)/2;

            VelCmd(vx,vy,0);
            //ROS_INFO("[MOVE] T(%.2f %.2f)  od(%.2f , %.2f) v(%.2f,%.2f)" ,fMoveTargetX, fMoveTargetY, pose_diff.x ,pose_diff.y,vx,vy);

            if(fabs(vx) < 0.01 && fabs(vy) < 0.01)
            {
                VelCmd(0,0,0);
                ctrl_msg.data = "pose_diff reset";
                ctrl_pub.publish(ctrl_msg);
                nStep = STATE_FIND_OBJ;			//X��Y�������С��0.01�󣬻����˻�е����X��Y�����Ŀ����ﵽ�غϣ�����ֻ����ƻ�е����Z�����˶�������
            }

            result_msg.data = "object x";
            result_pub.publish(result_msg);
        }

         //6��ǰ��������Ʒ
        if(nStep == STATE_TO_OBJ)
        {
            float vx,vy;
            vx = (fMoveTargetX - pose_diff.x)/2;
            vy = (fMoveTargetY - pose_diff.y)/2;

            VelCmd(vx,vy,0);

            //ROS_INFO("[MOVE] T(%.2f %.2f)  od(%.2f , %.2f) v(%.2f,%.2f)" ,fMoveTargetX, fMoveTargetY, pose_diff.x ,pose_diff.y,vx,vy);

            if(fabs(vx) < 0.01 && fabs(vy) < 0.01)
            {
                VelCmd(0,0,0);
                ctrl_msg.data = "pose_diff reset";
                ctrl_pub.publish(ctrl_msg);
                nStep = STATE_ADJUST_HEIGHT;			//X��Y�������С��0.01�󣬻����˻�е����X��Y�����Ŀ����ﵽ�غϣ�������ƻ�е����Z�����˶�������
            }

            result_msg.data = "forward";
            result_pub.publish(result_msg);
        }

        //9��������Ʒ����
        if(nStep == STATE_BACKWARD)
        {
            //ROS_WARN("[STATE_BACKWARD] nTimeDelayCounter = %d " ,nTimeDelayCounter);
            //nTimeDelayCounter++;
            
            float vx,vy;
            vx = (fMoveTargetX - pose_diff.x)/2;
            vy = (fMoveTargetY - pose_diff.y)/2;

            VelCmd(vx,vy,0);

            //ROS_INFO("[MOVE] T(%.2f %.2f)  od(%.2f , %.2f) v(%.2f,%.2f)" ,fMoveTargetX, fMoveTargetY, pose_diff.x ,pose_diff.y,vx,vy);

            if(fabs(vx) <= 0 && fabs(vy) <= 0)
            {
                VelCmd(0,0,0);
                ctrl_msg.data = "pose_diff reset";
                ctrl_pub.publish(ctrl_msg);
                nStep = STATE_DONE;
            }

            result_msg.data = "backward";
            result_pub.publish(result_msg);
        }

        ros::spinOnce();  //�ڵ��������֮ǰ��������
        r.sleep();	//�����ڵ�
    }

    delete tf_listener; 

    return 0;

}
