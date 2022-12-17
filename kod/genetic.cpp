#include <iostream>
#include <vector>
#include <algorithm>
#include "polaczenie.hpp"
void krzyzowanie(std::vector<std::vector<int>> &tasks)
{
    int n=tasks.size();
    for(int i=0;i<n;i++)
    {
        int perm1=(std::rand()%tasks.size()); //losuje dwie rozne permutacje
        int perm2=(std::rand()%tasks.size());
        int k1=std::rand()%tasks[0].size(); //losuje index
        int k2=tasks[perm1].size()-k1;
        while(perm1==perm2)
            perm2=(std::rand()%tasks.size());

        std::vector<int> child1(tasks[perm1].size(),0); // tworze dzieci
        std::vector<int> child2(tasks[perm2].size(),0);

        for(int j=0;j<tasks[i].size();j++)
        {
            if(j<=k1) child1[j]=tasks[perm1][j];
            else child1[j]=tasks[perm2][j];

            if(j<k2) child2[j]=tasks[perm2][j];
            else child2[j]=tasks[perm1][j];
        }
        tasks.push_back(child1);
        tasks.push_back(child2);
        child1.clear();
        child2.clear();
    }
}
void mutacja(std::vector<std::vector<int>> t, std::vector<std::vector<int>> &tasks)
{
    int x=std::rand()%tasks.size(); //losujemy liczbe permutacji do zmutowania
    for(int i=0;i<x;i++)
    {
        int y=std::rand()%tasks.size(); // losuje permutajce do mutacji
        int z1=std::rand()%tasks[x].size(); // losuje index do permutacji (zmieniam maszyne procesu w tasks)
        int z2=(std::rand()%(t[z1+1].size()-2))+2; // losuje index na jaka inna maszyne wymienic w procesie vector t
        while(tasks[y][z1]==t[z1+1][z2])
            z2=(std::rand()%(t[z1+1].size()-2))+2;

        tasks[y][z1]=t[z1+1][z2];
    }
}
void populacja(std::vector<std::vector<int>>t, std::vector<std::vector<int>> &tasks)
{
    std::vector<int> machines(t[0][1],0); // wybor cmax
    std::vector<std::vector<int>> res(10, std::vector<int>(t[0][0]+1,0));
    for(int j=0;j<tasks[0].size();j++)
        machines[tasks[0][j]-1]+=t[j+1][1];
    int cmax=cMax(machines);
    tasks[0].push_back(cmax);
    machines.clear();
    
    for(int i=1;i<tasks.size();i++)// obliczam cmax
    {
        std::vector<int> machines(t[0][1],0);
        for(int j=0;j<tasks[i].size();j++)
            machines[tasks[i][j]-1]+=t[j+1][1];
        cmax=cMax(machines);
        tasks[i].push_back(cmax);        
        machines.clear();
    }
    std::sort(tasks.begin(), tasks.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[a.size()-1] < b[b.size()-1];});

    for(int i=0;i<10;i++)
    {
        if(i<5) // 5 najlepszych
        {
            for(int j=0;j<tasks[i].size();j++)
                res[i][j]=tasks[i][j];
        }
        else // 5 losowych
        {
            int x=std::rand()%tasks.size();
            for(int j=0;j<tasks[x].size();j++)
                res[i][j]=tasks[x][j];
        }
    }
    tasks.clear();
    tasks=res;
}

void geneticAlgorithm(std::vector<std::vector<int>> t,std::vector<std::vector<int>> popOfTask,std::vector<std::vector<int>> &wynik)// calosc O(n^2*i) n = 30 - populacja, i - ilosc iteracji
{   
    for(int i=0;i<10;i++)
    {
        krzyzowanie(popOfTask); // a teraz bedziemy krzyzowac permutacje + O(n^2)
        mutacja(t,popOfTask); // O(x), x - ilosc mutacji 
        populacja(t,popOfTask); // wybieramy 5 najlepszych i 5 losowych O(n^2)
        if(i!=9)
            for(int j=0;j<popOfTask.size();j++)
                popOfTask[j].resize(popOfTask[j].size()-1);
    }
    wynik.push_back(popOfTask[0]);
}
