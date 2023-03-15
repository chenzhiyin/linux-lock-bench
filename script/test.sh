#!/bin/bash

# for i in $(seq 1200000 100000 2800000 )
#for i in 1500000 2500000
# do	
	# sudo ../../micro-benchmark/tools/powerManagement.sh  -f $i
	#for j in '0x0c0c' '0x1818' '0x0c18'
	#do
		#wrmsr -p 0 0x620 $j
		file=test-$(date +"%Y-%m-%d-%H-%M")
		sleep 3
		sh test_at.sh >> ../data/$file 2>&1
		sleep 3
		sh test_sl.sh >> ../data/$file 2>&1
		sleep 3
		sh test_mt.sh >> ../data/$file 2>&1
		sleep 3
		sh test_rw.sh >> ../data/$file 2>&1
	#done
# done
