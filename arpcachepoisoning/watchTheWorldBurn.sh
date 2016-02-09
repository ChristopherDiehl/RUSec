#!/bin/bash
#Must be in root session!
echo 1 > /proc/sys/net/ipv4/ip_forward
local_mac=$(ifconfig |grep HWaddr |grep wlan0)
local_mac=${local_mac#*r }
echo "local_mac ${local_mac}"