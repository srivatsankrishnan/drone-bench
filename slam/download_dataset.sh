#!/bin/bash

mkdir dataset
cd dataset

mkdir MH01
cd MH01
wget http://robotics.ethz.ch/~asl-datasets/ijrr_euroc_mav_dataset/machine_hall/MH_01_easy/MH_01_easy.zip && unzip MH_01_easy.zip
cd ..

mkdir MH03
cd MH03
wget http://robotics.ethz.ch/~asl-datasets/ijrr_euroc_mav_dataset/machine_hall/MH_03_medium/MH_03_medium.zip && unzip MH_03_medium.zip
cd ..

mkdir MH05
cd MH05
wget http://robotics.ethz.ch/~asl-datasets/ijrr_euroc_mav_dataset/machine_hall/MH_05_difficult/MH_05_difficult.zip && unzip MH_05_difficult.zip
cd ..

cd ..
