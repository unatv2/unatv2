#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/unattainiumv2.png
ICON_DST=../../src/qt/res/icons/unattainiumv2.ico
convert ${ICON_SRC} -resize 16x16 unattainiumv2-16.png
convert ${ICON_SRC} -resize 32x32 unattainiumv2-32.png
convert ${ICON_SRC} -resize 48x48 unattainiumv2-48.png
convert unattainiumv2-16.png unattainiumv2-32.png unattainiumv2-48.png ${ICON_DST}

