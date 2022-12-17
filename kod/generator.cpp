#include "polaczenie.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>

void wypisz(std::vector< std::vector<int>> t)
{
    for(int i=0;i<t.size();i++)
    {
        for(int j=0;j<t[i].size();j++)
            std::cout<<t[i][j]<<" ";
        std::cout<<"\n";
    }
}
char interfejs()
{
    char wybor;
    std::cout<<"Program rozwiazuje proble P|Cmax|Mj przy uzyciu algorytmu genetycznego, greedy i brute force wybierz jak chcesz je spradzic\n";
    std::cout<<"a) Algorytmy dla malej ilosci danych (z brute force)\n";
    std::cout<<"b) Algorytmy dla duzej ilosci danych (bez brute force)\n";
    std::cout<<"Wybor: \n";
    std::cin>>wybor;
    return wybor;
}
void wypisz_male(std::vector<int> t)
{
    for(int i=0;i<t.size();i++)
        std::cout<<t[i]<<" ";
    
    std::cout<<"\n";
}
void zapisz(std::vector< std::vector<int>> t)
{
    std::fstream plik("/home/wiktoria/Dokumenty/python/kod/dane.txt", std::ios::trunc | std::ios::out);
    if(plik.good())
    {
        plik<<t[0][0]<<" "<<t[0][1]<<'\n';
        plik.flush();
        for(int i=1;i<t.size();i++)
        {
            for(int j=0;j<t[i].size();j++)
            {
                plik << t[i][j]<<" ";
                plik.flush();
            }
            plik<<'\n';
            plik.flush();
        }
        plik.close();
    }
}
void zapisz_male(std::vector<int> t)
{
    std::fstream plik("/home/wiktoria/Dokumenty/python/kod/dane.txt", std::ios::app);
    if(plik.good())
    {
        for(int i=0;i<t.size();i++)
        {
            plik << t[i]<<" ";
            plik.flush();
        }
        plik<<'\n';
        plik.close();
    }
}
void zapisz_czas(double t,int koniec)
{
    std::fstream plik("/home/wiktoria/Dokumenty/python/kod/czasy.txt", std::ios::app);
    if(plik.good())
    {
        plik <<t<<" ";
        plik.flush();
        if(koniec) plik<<'\n';
        plik.close();
    }
}
void generator(std::vector< std::vector<int>> &t) // losuje n - procesow, m - maszyn, niektore procesy moga byc przydzielone do pewnych maszyn
{
    //int n= (std::rand() % 7)+3;
    int n=7;
    int m= (std::rand() % std::min(n-1,7))+2;
    while (n==m) 
        m= (std::rand() % std::min(n-1,7))+2;
    
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