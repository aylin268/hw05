#include "CountyMap.h"
#include <stdexcept>
#include <algorithm>



using namespace std;


		CountyMap::CountyMap(vector<County> counties,vector<vector<bool>> adjacencyMatrix){
			countiesID = std::move(counties);
    		neighbors = std::vector<std::vector<int>>(countiesID.size());
    
    		size_t n = countiesID.size();
    		if (adjacencyMatrix.size() != n)
        		throw std::invalid_argument("bad adjacency size");

    		for (size_t i = 0; i < n; ++i) {
        		if (adjacencyMatrix[i].size() != n)
            		throw std::invalid_argument("bad adjacency size");
    		}

    		
    		for (size_t i = 0; i < n; ++i) {
        		neighbors[i].reserve(6); 
    		}

    		for (size_t i = 0; i < n; ++i) {
        		for (size_t j = i + 1; j < n; ++j) {
            		if (adjacencyMatrix[i][j]) {
                		neighbors[i].push_back((int)j);
                		neighbors[j].push_back((int)i);
            		}
        		}
    		}
		}

		CountyMap::CountyMap(const CountyMap& other){
			countiesID = other.countiesID;
    		neighbors = other.neighbors;
			
		}

		CountyMap::~CountyMap(){};;

		//performance: O(1)
		County CountyMap::getCounty(int countyID){
			return countiesID.at(countyID);
		}

		//performance: O(1)
		bool CountyMap::countyAdjacency(int countyID1, int countyID2){
			if (countyID1 < 0 || countyID2 < 0 ||countyID1 >= (int)countiesID.size() || countyID2 >= (int)countiesID.size())
        		return false;

    		const auto &a = neighbors[countyID1];
    		const auto &b = neighbors[countyID2];
    		const auto &smaller = (a.size() < b.size()) ? a : b;
    		int target = (smaller.data() == a.data()) ? countyID2 : countyID1;

    		for (int nb : smaller) if (nb == target) return true;
    			return false;
		}

		//performance: O(1)
		int CountyMap::getNumCounties(){
			return (int) countiesID.size();
		}
		
		//performance: O(n), n = number of counties
		vector<int> CountyMap::getAdjacentCounties(int countyID){
			if(countyID<0 || countyID>= (int)neighbors.size()) return{};
			return neighbors[countyID];
		}

		//performance: O(n), n = number of counties in the itinerary
		bool CountyMap::checkValidItinerary(vector<int> itinerary){
			if(itinerary.empty()){
				return true;
			}
			for (size_t i = 1; i < itinerary.size(); ++i) {
        		if (!countyAdjacency(itinerary[i-1], itinerary[i])){
					return false;
				}
    		}
    		return true;
		}
