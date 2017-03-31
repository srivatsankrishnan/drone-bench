#!/bin/bash

wget ftp://ftp.inrialpes.fr/pub/lear/douze/data/INRIAPerson.tar
tar -xvf INRIAPerson.tar

mkdir dataset
mv INRIAPerson/Train/pos/ dataset/

echo >dataset/pos.lst
while read p; do
	echo dataset/pos/$(basename $p) >>dataset/pos.lst
done <INRIAPerson/Train/pos.lst
