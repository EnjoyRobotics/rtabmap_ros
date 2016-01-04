/*
Copyright (c) 2010-2014, Mathieu Labbe - IntRoLab - Universite de Sherbrooke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Universite de Sherbrooke nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef UTIL3D_REGISTRATION_H_
#define UTIL3D_REGISTRATION_H_

#include <rtabmap/core/RtabmapExp.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <rtabmap/core/Transform.h>
#include <opencv2/core/core.hpp>

namespace rtabmap
{

namespace util3d
{

int RTABMAP_EXP getCorrespondencesCount(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud_source,
							const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud_target,
							float maxDistance);

Transform RTABMAP_EXP transformFromXYZCorrespondences(
		const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud1,
		const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud2,
		double inlierThreshold = 0.02,
		int iterations = 100,
		int refineModelIterations = 10,
		double refineModelSigma = 3.0,
		std::vector<int> * inliers = 0,
		double * variance = 0);

void RTABMAP_EXP computeVarianceAndCorrespondences(
		const pcl::PointCloud<pcl::PointNormal>::ConstPtr & cloudA,
		const pcl::PointCloud<pcl::PointNormal>::ConstPtr & cloudB,
		double maxCorrespondenceDistance,
		double & variance,
		int & correspondencesOut);
void RTABMAP_EXP computeVarianceAndCorrespondences(
		const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloudA,
		const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloudB,
		double maxCorrespondenceDistance,
		double & variance,
		int & correspondencesOut);

Transform RTABMAP_EXP icp(
		const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud_source,
		const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud_target,
		double maxCorrespondenceDistance,
		int maximumIterations,
		bool & hasConverged,
		pcl::PointCloud<pcl::PointXYZ> & cloud_source_registered);

Transform RTABMAP_EXP icpPointToPlane(
		const pcl::PointCloud<pcl::PointNormal>::ConstPtr & cloud_source,
		const pcl::PointCloud<pcl::PointNormal>::ConstPtr & cloud_target,
		double maxCorrespondenceDistance,
		int maximumIterations,
		bool & hasConverged,
		pcl::PointCloud<pcl::PointNormal> & cloud_source_registered);

Transform RTABMAP_EXP icp2D(
		const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud_source,
		const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud_target,
		double maxCorrespondenceDistance,
		int maximumIterations,
		bool & hasConverged,
		pcl::PointCloud<pcl::PointXYZ> & cloud_source_registered);

pcl::PointCloud<pcl::PointXYZ>::Ptr RTABMAP_EXP getICPReadyCloud(
		const cv::Mat & depth,
		float fx,
		float fy,
		float cx,
		float cy,
		int decimation,
		double maxDepth,
		float voxel,
		int samples,
		const Transform & transform = Transform::getIdentity());

} // namespace util3d
} // namespace rtabmap

#endif /* UTIL3D_REGISTRATION_H_ */