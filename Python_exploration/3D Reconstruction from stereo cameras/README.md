# 3D Reconstruction from Stereo Cameras
Creating depth map and getting corresponding pointcloud can help us visualise the 3D map of the surrounding from a stereo camera pair.
## File description
* get_calibration_images.py : It saves calibration data for camera calibration.
* generate_calibration_data.py : It calibrates the camera pair according to the saved image pairs and saves the calibration data.
* stereovision.py : It generates the depth map from the stereo camera video feeds and generates the point cloud.
## Required softwares
* Python 2.7 or above
* OpenCV 3.2
* MeshLab
