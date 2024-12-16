#!/bin/bash

if [ -f /proc/sys/kernel/pid_max ]; then
	max_pid=$(cat /proc/sys/kernel/pid_max)
	echo "the maximum value for a process ID on this system is: $max_pid"
else
	echo "Unable to determine the maximum PID value"
fi
