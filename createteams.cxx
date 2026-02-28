 //1. read a JSON file that contains
//- numPlayers
//- every possible 2-person team
// each team's win percentage //

//2. fairness 
// A team is fair if its win % is close to 50 %
//key = abs(winPercentage - 50.0)
//prioirt queue key : smaller key, closer to 50% = more fair

//3. insert all teams into your min heap 
//key = abs(win% - 50)
//Value = std::pair<int, int>(playerOne, playerTwo)

//priority queue stores (key, (player1, player2))

//4. greedy algorithm
//1) remove (pop) the minimum from the heap
//.   --gives 50%
//2) if neither player is already assigned:
    // accept the team
    //mark both players as assigned
//3) if one of them is already assigned
    //skip this team
    //continue removing from heap

#include "teamdata.h"
#include "priorityqueue.h"
#include "json.hpp"
#include <cmath>



int main(int argc, char* argv[]){

    //1. read a json file
    //TeamData(std::string filename);
    //creating a data object for json reading
    std::string filename = argv[1];

    //A teamdata object that reads the JSON file//from TeamData.cpp
    TeamData data(filename);
    //call member function to get the number of players from the JSON metadata//frin TeamData.h and cpp
    int numPlayers = data.numPlayers();
   

    //2 determine the number of teams from teamStats(count only valid teams)
    int numTeams = 0;
    //remember it is a matrix//loop throught the matrix, because from teamdata.h we've defined std::vector<std::vector<double>> winPercentages_;
    for(int player1 = 0; player1 < numPlayers; ++player1){
        for(int player2 = player1 + 1; player2 < numPlayers; ++player2){
            //get tge win % of the team
            //we only count terms that actually exist in the input when determining the heap size
            if(data.winPercentages(player1, player2) > 0.0){ //skip missing teams//we assume that 
                //increase heap size
                numTeams++;;
            } 
        }
    }



    //3. insert all teams into your min heap(prioirty queue)
    //the heap stores (key, (player1, player2))
    //we need to find the key = percenetage difference from 50

    //PriorityQueue(std::size_t max_nodes);
    //creating a minheap
    PriorityQueue minheap(numTeams);

    //each heap element has a key and corresponding player one and two

    //p1 = player 1, p2 = player 2, defined in teamdata.cpp
    //using the insert function from priorityqueue.cpp

    //loops over all player pairs(player1, player2)
    for(int player1 = 0; player1 < numPlayers; player1++){
        for(int player2 = player1 + 1; player2 < numPlayers; ++player2){

            //skip missing team
            // we don't insert nonexisting term
            if(data.winPercentages(player1, player2) == 0.0) continue;

            //insert the data into heap by key since we only care about their fairness 
            double key = abs(data.winPercentages() - 50.0);
            minheap.insert({key, {player1, player2}});
        }
    }

    //4. greedy algorithm
    //keeping track of assignments
    std::vector<bool> assigned(numPlayers, false);

    //storing result
    std::vector<std::vector<int>> finalTeams;

    //popping!!!
    while(!minHeap.isEmpty()){
        //from priorityqueue.h
        KeyValuePair team = minHeap.removeMin();//remove the most fair team, which is just the top
        //(key, player1, player2)
        int player1 = team.second.first; //accesing player 1's index, team.second get us (player1, player2), and item.second.first get us player1
        int player2 = team.second.second;  //accesgin player 2's index

        //check if both players have not been assigned yet
        //only assign team if both players have not been assigned
        if(!assigned[player1] && !assigned[player2]){
            assigned[player1] = true;
            assigned[player2] = true;

            //add them to the result vector
            finalTeams.push_back({player1, player2});
        }

        //stop if all players are assigned
        if(finalTeams.size() == numPlayers/2){
            break;
        }
    }

    //output result in JSON format
    nlohmann::json result;
    result["teams"] = finalTeams;
    std::cout << result.dump(2) << std::endl;

    return 0;

    }


