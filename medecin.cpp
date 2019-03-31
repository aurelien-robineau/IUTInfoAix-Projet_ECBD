#include "medecin.h"

#include <iterator>
#include <iostream>
#include <map>

using namespace std;

void Medecin::predire(CMatString learnTable, CVString criteres, CVString valeurs) const {

    // Association des maladies à leur nombre d'occurence
    map<string, unsigned> maladies;

    // On compte de nombre d'occurence de chaque maladie
    for(unsigned i = 0; i < learnTable.size() ; i++) {
        string newMaladie = learnTable[i][learnTable[0].size()-1];

        // Si la maladie n'est pas listée
        if(maladies.find(newMaladie) == maladies.end()) {
            maladies[newMaladie] = 1;
        } else {
            maladies[newMaladie]++;
        }
    }

    // Nombre d'associations string1->string2 pour chaque critere
    vector<  map< pair<string,string >, unsigned> > symptomes (criteres.size()-1);
    for(unsigned i = 0; i < symptomes.size(); i++) {
        for(unsigned j = 0; j < learnTable.size(); j++) {
            string attr = learnTable[j][i];
            string maladie = learnTable[j][learnTable[0].size()-1];
            pair<string,string> assos = make_pair(attr, maladie);

            // Si l'association n'est pas listée
            if(symptomes[i].find(assos) == symptomes[i].end()) {
                symptomes[i][assos] = 1;
            } else {
                symptomes[i][assos]++;
            }
        }
    }

    // Ajout des associations inexistantes avec pour valeur 0
    for(unsigned i = 0; i < criteres.size()-1; i++) {
        for(unsigned attr = 0; attr < learnTable.size(); attr++) {
            map< string, unsigned>::iterator it = maladies.begin();
            while (it != maladies.end()) {
                string label = it->first;
                pair<string, string> assos = make_pair(learnTable[attr][i], label);
                if(symptomes[i].find(assos) == symptomes[i].end()) {
                    symptomes[i][assos] = 0;
                }
                it++;
            }
        }
    }

    for(unsigned i = 0; i < symptomes.size(); i++) {
        // Create a map iterator and point to beginning of map
        map< pair<string,string >, unsigned>::iterator it1 = symptomes[i].begin();

        // Iterate over the map using Iterator till end.
        while (it1 != symptomes[i].end())
        {
            // Accessing KEY from element pointed by it.
            pair<string,string > word = it1->first;

            // Accessing VALUE from element pointed by it.
            double count = it1->second;

            cout << word.first << "->" << word.second << " :: " << count << endl;

            // Increment the Iterator to point to next entry
            it1++;
        }
    }


    map< string, double > scores;

    map< string, unsigned>::iterator it = maladies.begin();
    while (it != maladies.end()) {
        string label = it->first;
        unsigned nbOccu = it->second;

        scores[label] += double(nbOccu) / double(learnTable.size());
        for(unsigned i = 0; i < symptomes.size(); i++) {
            pair<string, string> assos = make_pair(valeurs[i], label);
            cout << (symptomes[i][assos] / nbOccu) << endl;
            scores[label] *= (double(symptomes[i][assos]) / double(nbOccu));
        }

        it++;
    }

    // Create a map iterator and point to beginning of map
    map< string, double >::iterator it2 = scores.begin();

    // Iterate over the map using Iterator till end.
    while (it2 != scores.end())
    {
        // Accessing KEY from element pointed by it.
        string word = it2->first;

        // Accessing VALUE from element pointed by it.
        double count = it2->second;

        cout << word << " :: " << count << endl;

        // Increment the Iterator to point to next entry
        it2++;
    }
}
