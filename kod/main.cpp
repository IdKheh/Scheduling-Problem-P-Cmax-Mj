#include <iostream>
#include <vector>
#include "polaczenie.hpp"
#include <chrono>

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> t;
    std::vector<std::vector<int>> wynik;
    
    char wybor=interfejs();
    if(wybor == 'a' || wybor == 'A')
    {
        srand(time(NULL));
        std::cout<<"Genetuje dane. Prosze czekac...\n\n";
        generator(t);
        wypisz(t);
        zapisz(t);
        
        std::vector<std::vector<int>> perm;
        std::vector<int> posibility;
        for(int i=0;i<t[0][0];i++)
        {
            if(i<t[0][1]) posibility.push_back(i+1);
            else posibility.push_back(1);
        }
        std::vector<int> permutations(posibility.size(),0);
        std::cout<<"\nGeneruje permutacje. Prosze czekac...\n";
        permutation(t,posibility,permutations,perm,posibility.size()-1,0);
        posibility.clear();
        permutations.clear();


        std::cout<<"\n\nBRUTE FORCE - szukam cmaxa. Prosze czekac...\n";
        auto start = std::chrono::high_resolution_clock::now();
            bruteForce(t,perm,wynik);
        auto stop = std::chrono::high_resolution_clock::now();
        double czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        czas *= 1e-9;
        zapisz_czas(czas,0);
        wypisz(wynik);
        zapisz_male(wynik[0]);
        wynik.clear();

        std::vector<std::vector<int>> populations; //to musi być po bnb i brute force bo usuwam perm
        for(int i=0;i<10;i++)
        {
            int x=std::rand()%perm.size();
            populations.push_back(perm[x]);
        }
        perm.clear();

        std::cout<<"\n\nGENETIC ALGORITHM - szukam cmaxa. Prosze czekac...\n";
        start = std::chrono::high_resolution_clock::now();
            geneticAlgorithm(t,populations,wynik);
        stop = std::chrono::high_resolution_clock::now();
        czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        czas *= 1e-9;
        populations.clear();
        wypisz(wynik);
        wynik[0].resize(wynik[0].size()-1);
        zapisz_male(wynik[0]);
        zapisz_czas(czas,0);
        wynik.clear();

        std::cout<<"\n\nGREEDY- szukam cmaxa. Prosze czekac...\n\n";
        start = std::chrono::high_resolution_clock::now();
            greedy(t,wynik);
        stop = std::chrono::high_resolution_clock::now();
        czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        czas *= 1e-9;
        zapisz_czas(czas,1);
        wypisz(wynik);
        zapisz_male(wynik[0]);
        wynik.clear();
    }
    else if(wybor == 'b' || wybor == 'B')
    {
        srand(time(NULL));
        std::vector<std::vector<int>> perm;
        std::vector<std::vector<int>> wynik;
        std::vector<int> cel;
        std::cout<<"Genetuje dane. Prosze czekac...\n\n";
        generatorN(t);
        wypisz(t);

        std::cout<<"\nGeneruje permutacje. Prosze czekac...\n";
        dane(t,perm);

        std::vector<std::vector<int>> populations; //to musi być po bnb i brute force bo usuwam perm
        for(int i=10;i<50;i+=10)
        {
            for(int j=0;j<i;j++)
            {
                int x=std::rand()%perm.size();
                populations.push_back(perm[x]);
            }

            std::cout<<"\n\nGENETIC ALGORITHM dla "<<i<<" danych - szukam cmaxa. Prosze czekac...\n\n";
            auto start = std::chrono::high_resolution_clock::now();
            geneticAlgorithmN(t,populations,i, cel);
            auto stop = std::chrono::high_resolution_clock::now();
            double czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
            czas *= 1e-9;
            populations.clear();
            zapisz_czas(czas,0);
            zapisz_czas(cel[0],1);
            cel.clear();
        }
        perm.clear();
        std::cout<<"\n\nGREEDY- szukam cmaxa. Prosze czekac...\n\n";
        auto start = std::chrono::high_resolution_clock::now();
            greedy(t,wynik);
        auto stop = std::chrono::high_resolution_clock::now();
        double czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        czas *= 1e-9;
        zapisz_czas(czas,0);
        zapisz_czas(cMax(wynik[1]),1);
        
    }
    return 0;
}
