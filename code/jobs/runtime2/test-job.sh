#!/bin/bash
#PBS -N runtime-test
#PBS -M fabian.koehler@tu-dortmund.de
#PBS -m abe
##PBS -m n
#PBS -j oe
#PBS -l walltime=00:45:00
#PBS -l nodes=1:ppn=8
#PBS -l vmem=2gb

# output at begin of exectution
echo "${PBS_JOBNAME}"
cat ${PBS_NODEFILE}
echo
date
echo "--- START ---"
cd ${PBS_O_WORKDIR}
pwd

# the command to run as a job
python run-test.py

# output after completion
echo "--- END ---"
date
echo
echo "$(whoami) is leaving from $(hostname) ..."
echo
