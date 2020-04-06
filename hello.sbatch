#!/bin/bash
#SBATCH --cpus-per-task=...      # number of threads
#SBATCH --mem-per-cpu=1024M      # memory; default unit is megabytes
#SBATCH --time=0-00:05           # time (DD-HH:MM)
#SBATCH --job-name=hello
#SBATCH --output=hello.out

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
./hello

