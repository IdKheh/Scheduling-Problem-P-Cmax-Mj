#include <iostream>
#include <algorithm>
#include "polaczenie.hpp"

void dane(std::vector<std::vector<int>> t,std::vector<std::vector<int>> &perm)
{
    std::vector<int> pop;
    for(int i=1;i<t.size();i++)
    {
        pop.push_back(t[i][2]);
    }
    perm.push_back(pop);


    for(int i=0;i<100;i++)
    {
        int z1=std::rand()%pop.size(); // losuje index do permutacji (zmieniam maszyne procesu w perm)
        int z2=(std::rand()%(t[z1+1].size()-2))+2; // losuje index na jaka inna maszyne wymienic w procesie vector t
        while(pop[z1]==t[z1+1][z2])
            z2=(std::rand()%(t[z1+1].size()-2))+2;

        pop[z1]=t[z1+1][z2];
        perm.push_back(pop);
    }
}
void generatorN(std::vector<std::vector<int>> &t) // losuje n - procesow, m - maszyn, niektore procesy moga byc przydzielone do pewnych maszyn
{
    //int n= (std::rand() % 7)+3;
    int n=50000;
    int m= (std::rand() % std::min(n-1,50))+30;
    while (n==m) 
        int m= (std::rand() % std::min(n-1,50))+30;
    
    std::vector<int> para;
    para.push_back(n);
    para.push_back(m);
    t.push_back(para);
    para.clear();

    for(int i=1;i<n+1;i++)
    {
        para.push_back(i);
        para.push_back((std::rand() % 50)+1); // losujemy czas jaki procesor potrzebuje na prace
        
        int x;

        if(m==2) x=2;
        else x= (std::rand() % (m-2))+2; // z ilu procesorow moze korzystac

        para.resize(x+2);
        para[2]=(std::rand() % m) +1;
        x--;
        while(x>0)
        {
            int y= (std::rand() % m) +1; // kolejne numery procesorow
            for(int j=3;para.size();j++)
            {
                if(para[j-1]==y) break;
                else if(para[j]==0 && para[j-1]!=y)
                {
                    x--;
                    para[j]=y;
                    break;
                }
            }
        }
        t.push_back(para);
        para.clear();
    }
}
void populacjaN(std::vector<std::vector<int>> t, std::vector<std::vector<int>> &tasks,int n)
{
    std::vector<int> machines(t[0][1],0); // wybor cmax
    std::vector<std::vector<int>> res(n, std::vector<int>(t[0][0]+1,0));
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
    int ile = n/2;
    for(int i=0;i<n;i++)
    {
        if(i<ile) // 5 najlepszych
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
void geneticAlgorithmN(std::vector<std::vector<int>> t,std::vector<std::vector<int>> popOfTask,int n,std::vector<int> &wynik)// calosc O(n^2*i) n = 30 - populacja, i - ilosc iteracji
{   
    int petle=500;
    for(int i=0;i<petle;i++)
    {
        krzyzowanie(popOfTask); // a teraz bedziemy krzyzowac permutacje + O(n^2)
        mutacja(t,popOfTask); // O(x), x - ilosc mutacji 
        populacjaN(t,popOfTask,n); // wybieramy 5 najlepszych i 5 losowych O(n^2)
        if(i!=petle-1)
            for(int j=0;j<popOfTask.size();j++)
                popOfTask[j].resize(popOfTask[j].size()-1);
    }
    wynik.push_back(popOfTask[0][popOfTask[0].size()-1]);
}
