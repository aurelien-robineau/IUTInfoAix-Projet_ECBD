#ifndef MEDECIN_H
#define MEDECIN_H

#include <vector>
#include <string>

using namespace std;

typedef vector<string> CVString;
typedef vector <vector<string>> CMatString;

class Medecin
{
    public:
        void predire(CMatString learnTable, CVString criteres, CVString valeurs) const;
};

#endif // MEDECIN_H
