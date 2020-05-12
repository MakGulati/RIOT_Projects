#!/usr/bin/env python
# coding: utf-8

import argparse
import sys 

defaultCSVFile="parse.csv"
parser = argparse.ArgumentParser()
#parser.add_argument('-i','--input',nargs=1, help='Input file name. (Default: stdin)',default=sys.stdin,required=False)
parser.add_argument('-o','--output',help='Output csvfile name (Default: `input`.csv)', required=False)
parser.add_argument('-n','--no-dots',help='Disable dots', action='store_true',default=True)
parser.add_argument('input', nargs='?', help='Input file name. (Default: stdin)',default=sys.stdin)
args = parser.parse_args()

class Bench:
    def __init__(self, label, n=-1, i=-1, time=-1, unit=-1, average=-1):
        self.label=label
        self.n=n
        self.i=i
        self.time=time
        self.unit=unit
        self.average=average

    def __str__(self):
        return ("label: {label}," 
        "n: {n}, i: {i}," 
        "time:{time}," 
        "average: {average}"
        ).format(**self.__dict__)

import re

# BENCH(01/10): cp_rsa_dec                       = 7676 microsec
rePattern_subBench=r"BENCH\((\d+)/(\d+)\): (.*)= (\d+) (.*)$"
# #AVERAGE                                      #= 8222 microsec
rePattern_subBenchAverage=r".*/(\d+)= (\d+) (.*)$"
# BENCH: cp_rsa_gen                       = 312636 microsec
rePattern_oneBench=r"BENCH: (.*)= (\d+) (.*)$"

re_subBench = re.compile(rePattern_subBench)
re_subBenchAverage = re.compile(rePattern_subBenchAverage)
re_oneBench = re.compile(rePattern_oneBench)

def parse(line,bench):
    m = re_oneBench.search(line)
    if m is None:
        m = re_subBench.search(line)
        if m is None:
            m = re_subBenchAverage.search(line)
            if m is None:
                return None,bench
            else:#subbenchAverage average unit 
                bench=Bench(bench.label,n=m.group(1),average=m.group(2),unit=m.group(3))
                return 3,bench
        else:#subbench i n label time unit
            bench=Bench(
                i=m.group(1),
                n=m.group(2),
                label=m.group(3).strip(),
                time=m.group(4),
                unit=m.group(5))
            return 2,bench
    else:#oneBench lable time unit
        bench = Bench(m.group(1).strip(),time=m.group(2),unit=m.group(3))
        return 1,bench

# def getLogFileInCWD():
#     for file in os.listdir('.'):
#         if fnmatch.fnmatch(file, '*.log'):
#             return file
#     print("No .log file found!")

import csv
import sys

print("Input: ",end='')
if args.input == sys.stdin:
    logInput = sys.stdin
    print("stdin",end=' ')
else:
    logInput = open(args.input)
    print(args.input,end=' ')

import os 
if not args.output:
    if logInput == sys.stdin:
        csvfile = "stdin.csv"
    else:
        csvfile = os.path.splitext(args.input)[0] + ".csv"
else:
    csvfile = args.output
print("\nOutput: "+csvfile)

with open(csvfile,'w') as csvfile, logInput as logInput:
    fieldnames=['label','i','n','time','average','time-unit']
    writer = csv.DictWriter(csvfile,fieldnames)
    writer.writeheader()
    
    def writeBenchOnes(bench):
        writer.writerow({'label':bench.label,'time':bench.time,'time-unit':bench.unit})

    def writeSubBench(bench):
        writer.writerow({'label':bench.label,'n':bench.n,'i':bench.i,'time':bench.time,'time-unit':bench.unit})

    def writeSubBenchAverage(bench):
        writer.writerow({'label':bench.label,'n':bench.n,'average':bench.average,'time-unit':bench.unit})
        
    b=Bench("init")
    for line in logInput:
        i,b=parse(line,b)
        # overcomplicated switch/case thx to python not supporting switch/case
        switcher = {
            1: writeBenchOnes,
            2: writeSubBench,
            3: writeSubBenchAverage,
        }.get(i,None)
        if switcher is not None: 
            switcher(b)# call of appropriate function
        if not args.no_dots:
            print(".",end='')
    print("\nDone!")    