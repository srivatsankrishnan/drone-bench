import numpy as np
import cv2
import time

def init_find_target():
    global targetCascade, hog

    targetCascade = cv2.CascadeClassifier("haarcascade_fullbody.xml")

    hog = cv2.HOGDescriptor() #(48,96), (16,16), (8,8), (8,8), 9)
    hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

def find_target_haar_cpu(frame):
    #detect targets

    start = time.time()

    rects = targetCascade.detectMultiScale(
        frame,
        scaleFactor=1.05,
        minNeighbors=3
    )

    end = time.time()

    # Only return the location of the first target we see
    target = rects[0] if len(rects) > 0 else (-1, -1, -1, -1)

    # Return (target_x, target_y, target_w, target_h)
    return ((target[0], target[1], target[2], target[3]), end-start)

def find_target_hog_cpu(frame):
    # detect people in the image

    start = time.time()

    rects, weights = hog.detectMultiScale(frame) #, winStride=(4, 4),
    #    padding=(8, 8), scale=1.05)

    end = time.time()

    # Only return the location of the first target we see
    target = rects[0] if len(rects) > 0 else (-1, -1, -1, -1)

    # Return (target_x, target_y, target_w, target_h)
    return ((target[0], target[1], target[2], target[3]), end-start)

