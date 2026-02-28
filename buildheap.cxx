#include <iostream>
#include <fstream>
#include <cmath>
#include "json.hpp"
#include "priorityqueue.h"

//input json file
//read operations
//execute operations on priorityqueue
//convert heap -> json format
//print json

int main(int argc, char** argv) {
    //1. Read the JSON file 
    std::ifstream in(argv[1]);
    if(!in){
        std::cerr << "Error opening file.\n";
        return 1;
    }

    nlohmann::json jsonObject;
    in >> jsonObject;

    //json file -> instructions
    //priorityqueue -> machine that executes instructions
    //final heap -> result after executing instructions 
    
    //2 Create a priority queue with the max size and get the number of operations from metadata
    //attaining max heap size 
    int maxHeapSize = jsonObject["metadata"]["maxHeapSize"];
    //attaining the number of operations 
    int numOfOperations = jsonObject["metadata"]["numOperations"];

    //PriorityQueue(std::size_t max_nodes);
    PriorityQueue queue(maxHeapSize);

    //3. loop through operations 
    //find correct OpXX
    //get its operation type
    //if insert -> read key
    //apply to queue
    for(int i = 1; i<= numOfOperations; i++){
        //from createheapoperationdata.cxx
        int totalZeros = (int) floor(log10((double) numOfOperations)) + 1;
        int opZeros = (int) floor(log10((double) i)) + 1;
        std::string opNum = std::string(totalZeros - opZeros, '0') + std::to_string(i);
        std::string opKey = "Op" + opNum;


        //attain opkey and operations
        nlohmann::json op = jsonObject[opKey];
        std::string operation = op["operation"];

        if(operation == "insert"){
            double key = op["key"];
            queue.insert(key);
        }
        else if(operation == "removeMin"){
            queue.removeMin();
        }
    }
    //4. print the final heap using priorityQueue::JSON() method
    nlohmann::json result = queue.JSON();
    result["metadata"]["numOperations"] = numOfOperations;
    result["metadata"]["maxHeapSize"] = maxHeapSize;
    
    std::cout << result.dump(2) << std:: endl;

    return 0;
}
