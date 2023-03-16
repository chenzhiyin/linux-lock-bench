path=../src/include/
header_file=$(file_name) $(path)tony_pthread_data.h $(path)nop_delay.h $(path)tony_misc.c $(path)map_cpu.h
target=$(exe_name)
$(target) : $(header_file)
	gcc -O3 -ffast-math $< -o $@ -lpthread





