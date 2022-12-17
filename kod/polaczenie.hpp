#include<vector>

extern std::vector<std::vector<int>> t;
extern std::vector<std::vector<int>> perm;
void generator(std::vector< std::vector<int>> &t);
void wypisz(std::vector<std::vector<int>> t);
void wypisz_male(std::vector<int> t);
int cMax(std::vector<int> machines);
void zapisz(std::vector<std::vector<int>> t);
void zapisz_male(std::vector<int> t);
void zapisz_czas(double t,int koniec);

void bruteForce(std::vector<std::vector<int>> t, std::vector<std::vector<int>> perm,std::vector<std::vector<int>> &wynik);
void permutation(std::vector<std::vector<int>> t,std::vector<int> posib, std::vector<int> permutations,std::vector<std::vector<int>> &perm, int last, int index);
void geneticAlgorithm(std::vector<std::vector<int>> t,std::vector<std::vector<int>> popOfTask,std::vector<std::vector<int>> &wynik);
void greedy(std::vector<std::vector<int>> t,std::vector<std::vector<int>> &wynik);

void geneticAlgorithmN(std::vector<std::vector<int>> t,std::vector<std::vector<int>> popOfTask,int n,std::vector<int> &cel);
char interfejs();
void dane(std::vector<std::vector<int>> t,std::vector<std::vector<int>> &perm);
void generatorN(std::vector< std::vector<int>> &t);
void krzyzowanie(std::vector<std::vector<int>> &tasks);
void mutacja(std::vector<std::vector<int>> t, std::vector<std::vector<int>> &tasks);