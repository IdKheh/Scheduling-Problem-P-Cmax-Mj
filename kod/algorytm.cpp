#include <iostream>
#include <algorithm>
#include "polaczenie.hpp"

int cMax(std::vector<int> machines)
{
    int cmax=0;
    for(int i=0;i<machines.size();i++)
        cmax=std::max(cmax,machines[i]);
    return cmax;
}
void permutation(std::vector<std::vector<int>> t,std::vector<int> posib, std::vector<int> permutations,std::vector<std::vector<int>> &perm, int last, int index)
{
    for(int i=0;i<t[0][0]+1;i++)
    {
        permutations[index]=posib[i];
        if(index== last) 
        {
            bool rightPermutation=false;
            for(int j=0;j<permutations.size();j++)
            {
                for(int k=2;k<t[j+1].size();k++)   //t[j+1].size()
                    if(t[j+1][k]==permutations[j])
                    {
                        rightPermutation= true;
                        break;
                    }
                    else rightPermutation= false;
                if(rightPermutation == false) break;
            }
            if(rightPermutation) perm.push_back(permutations);
        }
        else permutation(t,posib,permutations,perm,last,index+1);
    }
}
void bruteForce(std::vector<std::vector<int>> t,std::vector<std::vector<int>> perm, std::vector<std::vector<int>> &wynik) 
{
    int n=t[0][0], m=t[0][1], cmax; //n procesorow, m- maszyn
    std::vector<int> bestOfTask(n,0);
    std::vector<int> bestOfMachines(m,0);
    std::vector<int> machines (m,0);
    for(int i=1;i<n+1;i++)// ustawienie stanu poczatkowego
    {
        bestOfTask[i-1]=t[i][2];
        bestOfMachines[t[i][2]-1]+=t[i][1];
    }
    cmax=cMax(bestOfMachines);  


    for(int i=0;i<perm.size();i++)
    {
        for(int j=0;j<perm[i].size();j++)
                machines[perm[i][j]-1]+=t[j+1][1];

        int suma=cMax(machines);
        if(suma<cmax) 
        {
            bestOfMachines=machines;
            bestOfTask=perm[i];
            cmax=suma;
        }
        for(int j=0;j<machines.size();j++)
            machines[j]=0;
    }
    //std::cout<<cmax<<"\n";
    wynik.push_back(bestOfTask);
    wynik.push_back(bestOfMachines);
}

void greedy(std::vector<std::vector<int>> t,std::vector<std::vector<int>> &wynik) // O(n^2)
{
    //int cmax;
    std::vector<int> machines (t[0][1],0);
    std::vector<int> tasks (t[0][0],0);
    std::sort(t.begin()+1, t.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] > b[1];});
    for(int i=1;i<t.size();i++)
    {
        int indexM=0, indexT=0,work=50000;
        for(int j=2;j<t[i].size();j++)
        {
            if(work>machines[t[i][j]-1])
            {
                work=machines[t[i][j]-1];
                indexM=t[i][j]-1;
                indexT=t[i][0];
            }
        }
        tasks[indexT-1]=indexM+1;
        machines[indexM]+=t[i][1];
    }
    //cmax=cMax(machines);
    wynik.push_back(tasks);
    wynik.push_back(machines);
}