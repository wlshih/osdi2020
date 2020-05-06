#! /bin/bash

# This script is for the 3rd bootloader of OSDI lab kernel.
# Run this script after running the 'loadimg' command.
# The host side will send image informations and image file to the target.
# 
# Please run in sudo.


location=$((0x80000))
kernel="kernel8.img"
dev="/dev/ttyUSB0"

while getopts 'f:l:' opt; do
	case "$opt" in
		f)	kernel=$OPTARG ;;
		l)	location=$OPTARG ;;
	esac
done

shift $(($OPTIND-1))

# check priviledge
if [ $UID != 0 ]; then
	echo "[ Transfer ended, please run with root ]"
	exit
fi


# start send image
size=$(wc -c ${kernel} | awk '{print $1}')

printf "Start sending image...\n\n"
printf "image name:      %s\n" $kernel
printf "image size:      %d\n" $size
printf "target:          %s\n" $dev
printf "target address:  0x%x\n\n" $location

printf "%d\r" $location > $dev
sleep 0.1
printf "%d\r" $size > $dev
sleep 0.1
printf "1\r" > $dev # start signal

dd status=progress if=$kernel of=$dev || echo "[ Transfer error ]"

echo -ne "\a"

exit


