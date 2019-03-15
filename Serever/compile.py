#!/usr/bin/python3

import os
import sys


os.system("clang++ server.cpp -o Server -I /home/eric/d/Library/boost/include -L /home/eric/d/Library/boost/lib -lpthread")
os.system("scp Server eric@192.168.100.61:/home/eric")

