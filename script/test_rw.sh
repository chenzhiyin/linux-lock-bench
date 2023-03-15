#!/bin/bash
file_name="sh rw_bk.sh"
kernel_version="centOS_5.0.2"
#out_file="../data/"$(date +%Y%m%d)$kernel_version"_rw_clx.csv"
out_file="../data/2019_3_20_"$kernel_version"_rw_clx.csv"
exe_time=5
wt_num=0
for wt_num in 0 1 2 3 4
do
for rt_num in 0 1 2 3 4
do
#rt_num=8	
result=""
result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0 -f)
# sleep 1
# result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0)
# sleep 1
# result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0 -p)
# sleep 1
# result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0 -c)
# sleep 1
# result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0 -p -c)
# sleep 1
# result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0 -s)
# sleep 1
# result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0 -s -p)
# sleep 1
# result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0 -s -c)
# sleep 1
# result=$result$($file_name -e $exe_time --rt $rt_num --rd 0 --wt $wt_num --wd 0 -s -p -c)
# sleep 1
echo $rt_num $wt_num $result

done
done

