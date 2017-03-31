#!/bin/bash

mv ../py-faster-rcnn/lib/setup.py ../py-faster-rcnn/lib/old_setup.py
cp cpu/setup.py ../py-faster-rcnn/lib/setup.py

mv ../py-faster-rcnn/lib/fast_rcnn/nms_wrapper.py ../py-faster-rcnn/lib/fast_rcnn/old_nms_wrapper.py
cp cpu/nms_wrapper.py ../py-faster-rcnn/lib/fast_rcnn/nms_wrapper.py

mv ../py-faster-rcnn/lib/fast_rcnn/config.py ../py-faster-rcnn/lib/fast_rcnn/old_config.py
cp cpu/config.py ../py-faster-rcnn/lib/fast_rcnn/config.py
