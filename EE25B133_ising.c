/*
EE25B133 SOUMYADEEP DAS
#Used chatgpt for theoretical clarity and then fix logical errors
#Used Gemini to convert my python code to C code
#Asked TAs about the irrelevant plots generated previously
#Tried asking a few friends regarding some doubts

Final Compilation Date: Sep 17, 2025
Version Number: hadn't keep track of that but tried 5 or 6 codes before this
*/
//-------------------------------------------------------------------------------//
//Code for 2D Ising Model using Metropolis Algorithm👇 ©Gemini 2.5 Flash
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to calculate the change in energy
int delta_energy(int **l, int n, int i, int j, float J) {
    return 2 * J * l[i][j] * (l[(i + 1) % n][j] + l[i][(j + 1) % n] + l[(i - 1 + n) % n][j] + l[i][(j - 1 + n) % n]);
}

// Metropolis sweep function
void metropolis_sweep(int **lattice, int n, float T, float J) {
    for (int k = 0; k < n * n; k++) {
        int i = rand() % n;
        int j = rand() % n;
        int dE = delta_energy(lattice, n, i, j, J);
        if (dE <= 0 || (float)rand() / RAND_MAX < exp(-dE / T)) {
            lattice[i][j] *= -1;
        }
    }
}

// Function to swap pointers to 2D arrays
void swap_lattices(int ***l1, int ***l2) {
    int **temp = *l1;
    *l1 = *l2;
    *l2 = temp;
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Usage: %s <n> <tstart> <tend> <tstep> <J> <p> <dmavg>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int n = atoi(argv[1]);
    float tstart = atof(argv[2]);
    float tend = atof(argv[3]);
    float tstep = atof(argv[4]);
    float J = atof(argv[5]);
    int p = atoi(argv[6]);
    float dmavg = atof(argv[7]);

    // Dynamic memory allocation for the lattice
    int **l1 = (int **)malloc(n * sizeof(int *));
    int **l2 = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        l1[i] = (int *)malloc(n * sizeof(int));
        l2[i] = (int *)malloc(n * sizeof(int));
    }
    
    // Initialize the lattice randomly
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            l1[i][j] = (rand() % 2 == 0) ? 1 : -1;
        }
    }

    float T = tstart;

    // Main loop for temperature sweep
    while (T <= tend) {
        // Perform initial sweeps to reach equilibrium
        for (int x = 0; x < p; x++) {
            metropolis_sweep(l1, n, T, J);
        }

        // Calculate magnetization and check for convergence
        float avg_Mold = 0.0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                avg_Mold += l1[i][j];
            }
        }
        avg_Mold /= (n * n);

        float mag_sum = 0.0;
        int count = 0;
        while (count < 1000) {
            metropolis_sweep(l1, n, T, J);
            float avg_Mnew = 0.0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    avg_Mnew += l1[i][j];
                }
            }
            avg_Mnew /= (n * n);
            
            mag_sum += fabs(avg_Mnew);
            
            if (fabs(avg_Mnew - avg_Mold) < dmavg) {
                break;
            }
            avg_Mold = avg_Mnew;
            count++;
        }

        float Mavg = mag_sum / (count > 0 ? count : 1);
        printf("T=%.2f, <M>=%f\n", T, Mavg);
        T += tstep;
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(l1[i]);
        free(l2[i]);
    }
    free(l1);
    free(l2);

    return 0;
}

// -------------------------------------------------------------------------------//
//Actual code used to generate EE25B133_MT.png👇
/*
import random as r
import copy as c
import math as m
import matplotlib.pyplot as plt
import numpy as np
#from datetime import datetime as d
#now = d.now()
#dd=now.day
#time=now.strftime("%Hh%Mm")
#f_ising=open(f'ising_output({time} Sep{dd}).dat','w')
n=32
tstart=1 
tend=6
tstep=0.01   
p=1000 #number of sweeps to perform  
dmavg=0.0001
Js=[1,1.5,2]
def delta_energy(l,i,j,J):
    return 2*J*l[i][j]*(l[(i+1)%n][j]+l[i][(j+1)%n]+l[(i-1)%n][j]+l[i][(j-1)%n]) 
def metropolis_sweep(lattice, T, J):
    for _ in range(n*n):
        i, j = r.randint(0, n-1), r.randint(0, n-1)
        dE = delta_energy(lattice, i, j, J)
        if dE <= 0 or np.random.rand() < np.exp(-dE / T):
            lattice[i][j] *= -1
    return lattice
for J in Js:
    temp=[]
    magn=[]
    T=tstart
    l1=[[r.choice([1, -1]) for i in range(n)] for i in range(n)]
    while T<=tend:
        for x in range(p):
            l1=metropolis_sweep(l1, T, J)
        mag=[]
        avg_Mold=sum(sum(x) for x in l1)/(n*n)
        x=0
        while x<1000:
            l1=metropolis_sweep(l1, T, J)
            avg_Mnew=sum(sum(x) for x in l1)/(n*n)
            mag.append(abs(avg_Mnew)) 
            if abs(avg_Mnew-avg_Mold)<dmavg: 
                break
            avg_Mold=avg_Mnew
            x+=1
        Mavg=np.mean(mag)
        magn.append(Mavg)
        temp.append(T)
        print(f'T={T}, <M>={Mavg}')
        T+=tstep
    f=open(f'ising_output(J={J}).dat','w')
    f.write(f'J={J}\n{temp}\n{magn}')
    f.close()
'''plt.plot(temp, magn, color='blue', linestyle='-', linewidth=1, label='Line')
plt.xlabel("Temperature")
plt.ylabel("Magnetization")
plt.show()'''
*/