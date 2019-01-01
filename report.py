#!/usr/bin/python


import os
import sys
from pathlib import Path
import subprocess as sp


correct_log_level = [
    'all',
    'success',
    'test_suite',
    'message',
    'warning',
    'error',
    'cpp_exception',
    'system_error',
    'fatal_error',
    'nothing'
]


def contains(collection, key):
    for c in collection:
        if(c == key):
            return True
    return False

def run_ut(command, level):
    sp.call([command, level])

#check argv and assign log_level
if len(sys.argv) == 1:
    log_level = "" 


elif len(sys.argv) == 2:
    if(contains(correct_log_level, sys.argv[1])):
       log_level = "--log_level=" + sys.argv[1]
    else:
        print("Wrong log level arguments!")
        quit()
    
else:
    print("Wrong number of arguments!")
    quit()


#Search unit tests exec files
ROOT = '.'
unit_tests = sorted(Path(ROOT).glob('**/ut_*'))

#is exec?
exec_file = []
for x in unit_tests:
    if x.is_file() and os.access(x, os.X_OK):
        exec_file.append(x)
        
print(log_level)
#output
for x in exec_file:
    run_ut(x, log_level)
