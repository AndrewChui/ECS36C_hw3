#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_
#include <string>
#include <vector>
class TeamData {
public:
TeamData(std::string filename);
int numPlayers() const;
double winPercentages(int i, int j) const { return winPercentages_[i][j]; }//
private:
// TODO: decide the type of this variable.
//we are returning winPercentage_[i][j], this is a 2D matrix so we need a type that depends on two indices 
// winPercentages_;
std::vector<std::vector<double>> winPercentages_;
int numPlayers_;
}; // class TeamData
#endif // _T