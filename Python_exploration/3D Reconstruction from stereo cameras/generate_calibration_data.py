import numpy as np
import glob
import cv2

ROWS=9;COLS=6;SQUARE_SIZE=2.5;
train_path='/home/prabin/python/openCV_samples/stereovision/final/calibration_pictures/'
data_path='/home/prabin/python/openCV_samples/stereovision/final/calibration/'
images_right = glob.glob(train_path + 'right_*.jpg')
images_left = glob.glob(train_path + 'left_*.jpg')
images_left.sort()
images_right.sort()

objp = np.zeros((COLS*ROWS,3), np.float32)
objp[:,:2] = np.mgrid[0:ROWS,0:COLS].T.reshape(-1,2)
objp *= SQUARE_SIZE # SQUARE_SIZE is the size of the chessboard squares in cm
image_points = {};image_points["left"]=[];image_points["right"]=[];
object_points=[]

print('Calibrating Please Wait...')
for i in range(len(images_right)-1):
    img_l = cv2.imread(images_left[i+1])
    img_r = cv2.imread(images_right[i+1])

    gray_l = cv2.cvtColor(img_l, cv2.COLOR_BGR2GRAY)
    gray_r = cv2.cvtColor(img_r, cv2.COLOR_BGR2GRAY)

    # Find the chess board corners
    ret_l, corners_l = cv2.findChessboardCorners(gray_l, (ROWS,COLS), True)
    ret_r, corners_r = cv2.findChessboardCorners(gray_r, (ROWS,COLS), True)

    # If found, add object points, image points (after refining them)
    object_points.append(objp)

    if ret_l is True:
        cv2.cornerSubPix(gray_l, corners_l,(11, 11), (-1, -1),(cv2.TERM_CRITERIA_MAX_ITER + cv2.TERM_CRITERIA_EPS,30, 0.01))
        image_points["left"].append(corners_l)
        # Draw and display the corners
        ret_l = cv2.drawChessboardCorners(img_l, (ROWS,COLS),corners_l, ret_l)
        cv2.imshow('calibrating L', img_l)
        cv2.waitKey(50)

    if ret_r is True:
        cv2.cornerSubPix(gray_r, corners_r,(11, 11), (-1, -1),(cv2.TERM_CRITERIA_MAX_ITER + cv2.TERM_CRITERIA_EPS,30, 0.01))
        image_points["right"].append(corners_r)
        # Draw and display the corners
        ret_r = cv2.drawChessboardCorners(img_r, (ROWS,COLS),corners_r, ret_r)
        cv2.imshow('calibrating R', img_r)
        cv2.waitKey(50)
    img_shape = gray_l.shape[::-1]
cv2.destroyAllWindows()

## Calibrate cameras
(cam_mats, dist_coefs, rect_trans, proj_mats, valid_boxes,undistortion_maps, rectification_maps) = {}, {}, {}, {}, {}, {}, {}
criteria = (cv2.TERM_CRITERIA_MAX_ITER + cv2.TERM_CRITERIA_EPS,100, 1e-5)
flags = (cv2.CALIB_FIX_ASPECT_RATIO + cv2.CALIB_ZERO_TANGENT_DIST + cv2.CALIB_SAME_FOCAL_LENGTH)

rt, M1, d1, r1, t1 = cv2.calibrateCamera(object_points, image_points["left"], img_shape, None, None)
rt, M2, d2, r2, t2 = cv2.calibrateCamera(object_points, image_points["right"], img_shape, None, None)


(ret, cam_mats["left"], dist_coefs["left"], cam_mats["right"],dist_coefs["right"], rot_mat, trans_vec, e_mat,f_mat) = cv2.stereoCalibrate(object_points,image_points["left"], image_points["right"], M1, d1, M2, d2, img_shape, criteria, flags)

print('Camera Matrix Left',cam_mats["left"])
print('Camera Matrix Right',cam_mats["right"])
print('Distortion Coefficient Matrix Left',dist_coefs["left"])
print('Distortion Coefficient Matrix Right',dist_coefs["right"])
print('Rotation Matrix',rot_mat)
print('Translation Matrix',trans_vec)
print('Essential Matrix',e_mat)
print('Fundamental Matrix',f_mat)

(rect_trans["left"], rect_trans["right"],proj_mats["left"], proj_mats["right"],disp_to_depth_mat, valid_boxes["left"],valid_boxes["right"]) = cv2.stereoRectify(cam_mats["left"],dist_coefs["left"],cam_mats["right"],dist_coefs["right"],img_shape,rot_mat, trans_vec, flags=0)

(undistortion_maps["left"],rectification_maps["left"]) = cv2.initUndistortRectifyMap(cam_mats["left"],dist_coefs["left"],rect_trans["left"],proj_mats["left"],img_shape,cv2.CV_32FC1)
(undistortion_maps["right"],rectification_maps["right"]) = cv2.initUndistortRectifyMap(cam_mats["right"],dist_coefs["right"],rect_trans["right"],proj_mats["right"],img_shape,cv2.CV_32FC1)

np.save(data_path+'undistortion_map_left.npy',undistortion_maps["left"])
np.save(data_path+'undistortion_map_right.npy',undistortion_maps["right"])
np.save(data_path+'rectification_maps_left.npy',rectification_maps["left"])
np.save(data_path+'rectification_maps_right.npy',rectification_maps["right"])
np.save(data_path+'valid_box_left.npy',valid_boxes["left"])
np.save(data_path+'valid_box_right.npy',valid_boxes["right"])
np.save(data_path+'camera_matrix_left.npy',cam_mats["left"])
np.save(data_path+'camera_matrix_right.npy',cam_mats["right"])
np.save(data_path+'distortion_left.npy',dist_coefs["left"])
np.save(data_path+'distortion_right.npy',dist_coefs["right"])
np.save(data_path+'disparity_to_depth.npy',disp_to_depth_mat)
np.save(data_path+'rotation_vector.npy',rot_mat)
np.save(data_path+'translation_vector.npy',trans_vec)
np.save(data_path+'essential_matrix.npy',e_mat)
np.save(data_path+'fundamental_matrix.npy',f_mat)

print('Calibration Complete!!!')

