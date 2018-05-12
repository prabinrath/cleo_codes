import numpy as np
import thread
from sklearn.preprocessing import normalize
import cv2

capl = cv2.VideoCapture(2)
capr = cv2.VideoCapture(3)

data_path='/home/prabin/python/openCV_samples/stereovision/final/calibration/'
undistortion_maps_left=np.load(data_path+'undistortion_map_left.npy')
undistortion_maps_right=np.load(data_path+'undistortion_map_right.npy')
rectification_maps_left=np.load(data_path+'rectification_maps_left.npy')
rectification_maps_right=np.load(data_path+'rectification_maps_right.npy')
disparity_to_depth=np.load(data_path+'disparity_to_depth.npy')

save=False
index=1
ply_header = '''ply
format ascii 1.0
element vertex %(vert_num)d
property float x
property float y
property float z
property uchar red
property uchar green
property uchar blue
end_header
'''

def save_input(inp):
    global save
    while True:
        x=input('Enter 1 to save')
        if x==1:
            save=True
        else:
            save=False

def nothing(x):
    pass

def write_ply(fn, verts, colors):
    verts = verts.reshape(-1, 3)
    colors = colors.reshape(-1, 3)
    verts = np.hstack([verts, colors])
    with open(fn, 'wb') as f:
        f.write((ply_header % dict(vert_num=len(verts))).encode('utf-8'))
        np.savetxt(f, verts, fmt='%f %f %f %d %d %d ')

stereoMatcher = cv2.StereoSGBM_create(0,128,5)
cv2.namedWindow("Track Bar Window")
cv2.createTrackbar("Number of Disparities", "Track Bar Window", 128, 255,nothing);
cv2.createTrackbar("Pre Filter Cap", "Track Bar Window", 0, 63,nothing);
cv2.createTrackbar("Minimum Disparity", "Track Bar Window", 0, 100,nothing);
cv2.createTrackbar("Uniqueness Ratio", "Track Bar Window", 0, 15,nothing);
cv2.createTrackbar("Disp12MaxDiff", "Track Bar Window", 0, 100,nothing);
cv2.createTrackbar("Block Size", "Track Bar Window", 5, 100,nothing);
cv2.createTrackbar("Speckle Range", "Track Bar Window", 0, 5,nothing);
cv2.createTrackbar("Speckle Window Size", "Track Bar Window", 0, 200,nothing);
cv2.createTrackbar("SADwindowSize", "Track Bar Window", 5, 255,nothing);
'''
right_matcher = cv2.ximgproc.createRightMatcher(stereoMatcher)
# FILTER Parameters
lmbda = 80000
sigma = 1.2
visual_multiplier = 1.0
wls_filter = cv2.ximgproc.createDisparityWLSFilter(matcher_left=stereoMatcher)
wls_filter.setLambda(lmbda)
wls_filter.setSigmaColor(sigma)
'''
stereoMatcher.setMode(cv2.STEREO_SGBM_MODE_SGBM_3WAY);
thread.start_new_thread(save_input,(True,))

while True:
    retl,img_l = capl.read()
    retr,img_r = capr.read()
    if not(retl) or not(retr):
    	print('Camera feed unavailable')
    	break
    gray_l = cv2.cvtColor(img_l, cv2.COLOR_BGR2GRAY)
    gray_r = cv2.cvtColor(img_r, cv2.COLOR_BGR2GRAY)
    rectified_l = cv2.remap(gray_l, undistortion_maps_left,rectification_maps_left,cv2.INTER_LANCZOS4)#cv2.INTER_NEAREST)
    rectified_r = cv2.remap(gray_r, undistortion_maps_right,rectification_maps_right,cv2.INTER_LANCZOS4)#cv2.INTER_NEAREST)
    cv2.imshow("left", rectified_l)
    cv2.imshow("right", rectified_r)
    
    SADWindowSize=cv2.getTrackbarPos("SADwindowSize", "Track Bar Window")
    numDisparities=cv2.getTrackbarPos("Number of Disparities", "Track Bar Window")

    if (SADWindowSize % 2 == 0):
        SADWindowSize = SADWindowSize + 1
    if (numDisparities % 16 != 0):
        numDisparities = numDisparities + (16 - numDisparities % 16)
    
    stereoMatcher.setPreFilterCap(cv2.getTrackbarPos("Pre Filter Cap", "Track Bar Window"));
    stereoMatcher.setMinDisparity(cv2.getTrackbarPos("Minimum Disparity", "Track Bar Window"));
    stereoMatcher.setSpeckleRange(cv2.getTrackbarPos("Speckle Range", "Track Bar Window"));
    stereoMatcher.setSpeckleWindowSize(cv2.getTrackbarPos("Speckle Window Size", "Track Bar Window"));
    stereoMatcher.setUniquenessRatio(cv2.getTrackbarPos("Uniqueness Ratio", "Track Bar Window"));
    stereoMatcher.setBlockSize(cv2.getTrackbarPos("Block Size", "Track Bar Window"));
    stereoMatcher.setDisp12MaxDiff(cv2.getTrackbarPos("Disp12MaxDiff", "Track Bar Window"));
    stereoMatcher.setP1(8*1*cv2.getTrackbarPos("SADwindowSize", "Track Bar Window")**2);
    stereoMatcher.setP2(32*1*cv2.getTrackbarPos("SADwindowSize", "Track Bar Window")**2);
    '''
    displ = stereoMatcher.compute(rectified_l, rectified_r)
    dispr = right_matcher.compute(rectified_l, rectified_r)
    displ = np.int16(displ)
    dispr = np.int16(dispr)
    disparity_scaled = wls_filter.filter(displ, rectified_l, None, dispr)
    disparity_scaled = cv2.normalize(src=disparity_scaled, dst=disparity_scaled, beta=0, alpha=255, norm_type=cv2.NORM_MINMAX);
    disparity_scaled = np.uint8(disparity_scaled)
    '''

    disparity = stereoMatcher.compute(rectified_l,rectified_r)
    disparity_scaled = (disparity / 16).astype(np.uint8) + abs(disparity.min())
    cv2.filterSpeckles(disparity_scaled,0,400,128)
    cv2.imshow("disparity", disparity_scaled)
    
    '''
    h, w = img_l.shape[:2]
    f = 0.5*w                          # guess for focal length
    disparity_to_depth = np.float32([[1, 0, 0, -0.5*w],
                    [0,-1, 0,  0.5*h], # turn points 180 deg around x-axis,
                    [0, 0, 0,     -f], # so that y-axis looks up
                    [0, 0, 1,      0]])
    '''
    if save==True:
        print('creating point cloud and saving...')
        points = cv2.reprojectImageTo3D(disparity_scaled, disparity_to_depth)
        colors = cv2.cvtColor(img_l, cv2.COLOR_BGR2RGB)
        mask = disparity_scaled > disparity_scaled.min()
        out_points = points[mask]
        out_colors = colors[mask]
        out_fn = '/home/prabin/python/openCV_samples/stereovision/final/pointclouds/out'+str(index)+'.ply'
        write_ply(out_fn, out_points, out_colors)
        index+=1
        save=False
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()

