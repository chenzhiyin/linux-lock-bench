#!/bin/bash
file_name="sh at_bk.sh"
kernel_version="centOS_5.0.2"
#out_file="../data/"$(date +%Y%m%d)$kernel_version"_at_clx.csv"
out_file="../data/2019_3_20_"$kernel_version"_at_clx.csv"
exe_time=5
#t_num=8
for t_num in 1 2 4 6 8
do	
result=""
result=$result$($file_name -e $exe_time -t $t_num -d 0 -f)
# sleep 1
# result=$result$($file_name -e $exe_time -t $t_num -d 0)
# sleep 1
# result=$result$($file_name -e $exe_time -t $t_num -d 0 -p)
# sleep 1
# result=$result$($file_name -e $exe_time -t $t_num -d 0 -c)
# sleep 1
# result=$result$($file_name -e $exe_time -t $t_num -d 0 -p -c)
# sleep 1
# result=$result$($file_name -e $exe_time -t $t_num -d 0 -s)
# sleep 1
# result=$result$($file_name -e $exe_time -t $t_num -d 0 -s -p)
# sleep 1
# result=$result$($file_name -e $exe_time -t $t_num -d 0 -s -c)
# sleep 1
# result=$result$($file_name -e $exe_time -t $t_num -d 0 -s -p -c)
# sleep 1
echo $t_num $result

done

