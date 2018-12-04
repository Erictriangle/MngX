#!/usr/bin/python


import os
from pathlib import Path
import subprocess as sp


#Search unit tests

ROOT = '.'
unit_tests = sorted(Path(ROOT).glob('**/control_*'))

#is exec?
exec_file = []
for x in unit_tests:
    if x.is_file() and os.access(x, os.X_OK):
        exec_file.append(x)

#gather output
def run_ut(command):
    process = sp.Popen([command], stdout=sp.PIPE)
    process.stdout
    process.stderr

#output
for x in exec_file:
    run_ut(x)
