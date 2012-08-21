#!/bin/bash
clear 
echo "-----------------------------------"
echo "removing old file..."
rm -f hdd.img

echo "creating 500mb image"
dd if=/dev/zero of=hdd.img bs=516096c count=1000 

echo "use o (create new table), n (new partition, primary, 1), a (set bootable), t (set type), p (print table), w (save)"
echo "when printing the table, note the start and blocks numbers"
fdisk -u -C1000 -S63 -H16 hdd.img

echo "losetup, number is start*512"
losetup -o1048576 /dev/loop0 hdd.img

echo "make fat32-fs, number is blocks"
mkdosfs -F32 /dev/loop0 502976 

echo "trying to mount"
mount -t vfat /dev/loop0 /media/hdd

echo "putting files onto image!"
touch /media/hdd/abc.txt
echo "mooo" >> /media/hdd/abc.txt
mkdir /media/hdd/some_test_dir

echo "unmounting"
umount /dev/loop0
losetup -d /dev/loop0
losetup -d /dev/loop0
losetup -d /dev/loop0
