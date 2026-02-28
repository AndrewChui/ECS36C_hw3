#include "teamdata.h"
#include <iostream>
#include "json.hpp"
TeamData::TeamData(std::string datafile){
    std::ifstream in(datafile);
    if(!in){
        std::cerr << "Error opening file.\n";
        std::exit(1);
    }

    //A json object called dataMatrix
    nlohmann::json dataMatrix;
    in >> dataMatrix;

    numPlayers_ = dataMatrix["metadata"]["numPlayers"];

    //create a matrix to store the information
    winPercentages_.resize(numPlayers_, std::vector<double>(numPlayers_,0.0));

    int teamStatsLen = dataMatrix["teamStats"].size();

    for(int i = 0; i < teamStatsLen; i++){
        auto& information = dataMatrix["teamStats"][i];
        winPercentages_.emplace_back(
            int player1 = information["playerOne"];
            int player2 = information["playerTwo"];
            double win = information["winPercentage"];

            winPercentages_[p1][p2] = win;
            winPercentages_[p2][p1] = win;
        );
    }



}