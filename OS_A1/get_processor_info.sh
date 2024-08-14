#!/bin/bash
echo "Total Number of Processors: $(grep -c '^processor' /proc/cpuinfo)" > CPU_info.txt
echo "Total Number of Physical Cores: $(grep -m 1 'cpu cores' /proc/cpuinfo | awk '{print $4}')" >> CPU_info.txt

if grep -q 'siblings' /proc/cpuinfo; then
    echo "Is Hyperthreading Enabled: Yes" >> CPU_info.txt
    echo "Total Number of Cores with Hyperthreading: $(grep -c 'processor' /proc/cpuinfo)" >> CPU_info.txt
else
    echo "Is Hyperthreading Enabled: No" >> CPU_info.txt
    echo "Total Number of Cores with Hyperthreading: $(grep -c 'processor' /proc/cpuinfo)" >> CPU_info.txt
fi

echo "Processor Model: $(grep -m 1 'model name' /proc/cpuinfo | cut -d ':' -f 2 | sed 's/^ *//')" >> CPU_info.txt

echo "Processor information has been extracted and stored in CPU_info.txt"

