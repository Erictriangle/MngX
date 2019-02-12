#!/usr/bin/python3

import os
import sys
from pathlib import Path
import subprocess as sp
from fnmatch import fnmatch
import re


#report.py is script to gather output from
#unit test module and check //TODO comment
#from .c/.cc/.cpp and.h/.hpp file.


extension = {
    '*.c',
    '*.cc',
    '*.cpp',
    '*.h',
    '*.hpp'
    }

correct_log_level = {
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
    }


ROOT = '.'
path_list = []
output = []


#TODO function


def gather_output(filename):
    with open(filename, 'r') as fn:
        lines = fn.readlines()
        for l in lines:
            append_line_with_TODO(filename, l)

def append_line_with_TODO(filename, line):
    match = re.search('//TODO(.+?)\n',line)
    if match:
        output.append(filename.name + ' ' +  match.group(0))


#UT function

def check_log_level(key):
    return key in correct_log_level

def run_ut(command, log_level):
    sp.call([command, log_level])

def set_log_level():
    if len(sys.argv) == 2:
        if check_log_level(sys.argv[1]):
            return "--log_level=" + sys.argv[1]
        else:
            print("Wrong log level arguments!")
            sys.exit()
    elif len(sys.argv) > 1:
        print('''
            Wrong number of arguments!

            Usage: report.py <log_level>

            Log level:  all
                        success
                        test_suite
                        message
                        warrning
                        error
                        cpp_exception
                        system_error
                        fatal_error
                        nothing
        ''')
        sys.exit()
    else:
        return "--log_level=error"

#Main

if __name__ == '__main__':
    log_level = set_log_level()

    for ext in extension:
        path_list += sorted(Path(ROOT).glob('**/' + ext))
    ut_list = sorted(Path(ROOT).glob('Debug/*ut_*'))

    for pl in path_list:
        gather_output(pl)

    print('UT Module:')
    for ut in ut_list:
        if ut.is_file() and os.access(ut, os.X_OK):
            run_ut(ut, log_level)

    print('\nTODO list:')
    if not output:
        print('  -nothing to report')
    for o in output:
        print(o)
