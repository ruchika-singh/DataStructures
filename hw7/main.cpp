#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath> 
#include <vector>
#include <algorithm>
#define earthRadiusKm 6371.0
#ifndef M_PI
#define M_PI 3.14
#endif

//TODO: You must fill in all ?????? with the correct types.
typedef long int ID_TYPE; //Type for user IDs
typedef std::pair<long int, long int>COORD_TYPE; //Type for a coordinate (latitude and longitude)
typedef std::map<long int,std::vector<long int> > ADJ_TYPE; //Adjacency Lists type
typedef std::map<long int,std::pair<double, double> > GEO_TYPE; //Positional "dictionary"

//Function forward declarations. DO NOT CHANGE these. 
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile);
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile);
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance);
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset);


// DO NOT CHANGE THIS FUNCTION
int main(int argc, char** argv){
    ADJ_TYPE adj_lists;
    GEO_TYPE locations;

    if(argc != 3){
        std::cout << "Correct usage is " << argv[0] 
                  << " [commands file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream commands(argv[1]);
    if(!commands){
        std::cerr << "Problem opening " << argv[1] << " for reading!" 
                  << std::endl;
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Problem opening " << argv[2] << " for writing!" 
                  << std::endl;
        return -1;
    }

    std::string token; //Read the next command
    while(commands >> token){
        if(token == "load-connections"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading locations." << std::endl;
                return -1;
            }

            loadLocations(locations, loadfile);
        }
        else if(token == "print-degrees"){
            printDegreesOfAll(adj_lists, outfile);
        }
        else if(token == "print-degree-histogram"){
            printDegreesHistogram(adj_lists, outfile);
        }
        else if(token == "all-users-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printAllUsersWithinDistance(locations, outfile, start_id, 
                                        max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile, 
                                       start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                                    adj_lists.find(start_id), offset);
        }
        else{
            std::cerr << "Unknown token \"" << token << "\"" << std::endl;
            return -1;
        }
    }

    return 0;
}




// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS POINT////////////////////

/**
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile){
  long int a;
  long int b;
  //loads the ID and IDS of all their friends in a vector in a map
  while(loadfile >> a >> b){
    adj_lists[a].push_back(b); 
  }
}

/**
 * Loads a list of locations in the format "id latitude longitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile){
  long int id;
  double lat, lon;
  while(loadfile >> id >> lat >> lon){
    //holds the latitude and longitude in a pair
    std::pair<double, double > loc;
    loc = std::make_pair(lat, lon);
    //the key is the ID and the value is the pair of the location
    locations[id] = loc;
  }
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to longest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance){
  GEO_TYPE::const_iterator it = locations.begin();
  //temporary map that makes the key the distance and the value a vector of IDs
  //this is so the distances can be sorted 
  std::map <double, std::vector<long int> > temp;
  double distance;
  GEO_TYPE::const_iterator og;
  //get the iterator for the start location
  og = locations.find(start_id);
  //if the ID doesn't have a location
  if(og == locations.end()){
    outfile << "User ID " << start_id << " does not have a recorded location." << std::endl;
  }
  else{
    //goes through all the locations and calculates the distance between the user and the other user
    for(; it != locations.end(); it++){
        distance = distanceEarth((og->second).first, (og->second).second,(it->second).first,(it->second).second);
        //if its less than the max distance its added to the map
        if(int(distance) < max_distance && it != og){
          temp[int(distance)].push_back(it->first);
        }
      }
    //if there are no users within maz_distance of the user
    if(temp.size() == 0){
      outfile << "There are no users within " << max_distance << " km of user " << start_id << std::endl;
    }
    else{
      outfile << "User IDs within " << max_distance << " km of user " <<start_id << ":" << std::endl;
      std::map <double, std::vector<long int> >::const_iterator  it1 = temp.begin();
      //prints each user and the distance
      for(; it1 != temp.end(); it1++){
        outfile << " " << int(it1->first) << " km:";
        for(int i = 0; i < (it1->second).size(); i ++){
          outfile << " " << (it1->second)[i];
        } 
        outfile << std::endl;
      }

    }
  }
}

/**
 * Prints a sorted list of degrees (smallest to largest) along with how many users
 * have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
  //map of sorted degrees and the users with that degree
  std::map <long int, int> degree;
  ADJ_TYPE::const_iterator it = adj_lists.begin();
  for(; it != adj_lists.end(); it++){
    //increases the counter for the degree if it is greater than 1
    if(it->second.size() >= 1){
      ++degree[it->second.size()];
    }
  }
  outfile << "Histogram for " << adj_lists.size() << " users:"<< std::endl;
  //goes through degree map and prints it
  std::map <long int, int>::const_iterator it1 = degree.begin();
  for(; it1 != degree.end(); it1++){
    outfile << " " << "Degree " << it1->first << ": " << it1->second << std::endl; 
  }
}

/**
 * Prints a sorted list of user IDs (smallest to largest) along with the degree for
 * each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
  ADJ_TYPE::const_iterator it = adj_lists.begin();
  //map of IDs and their degrees per user
  std::map <long int,long int> degree;
  for(; it != adj_lists.end(); it++){
    //only adds to map if it is greater than 1
    if(it->second.size() >= 1){
      degree[it->first] = it->second.size();
    }
  }
  std::map <long int,long int>::const_iterator it1 = degree.begin();
  //goes through degree map and prints output
  outfile << "Degrees for " << adj_lists.size() << " users:"<< std::endl;
  for(; it1 != degree.end(); it1++){
    outfile << " " << it1->first << ": Degree " << it1->second <<std::endl;
  }
}

/**
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree){
  ADJ_TYPE::const_iterator og;
  //finds the iterator for start id
  og = adj_lists.find(start_id);
  //if the start ID doesn't exist
  if(og == adj_lists.end()){
    outfile << "There is no user with friends and ID " << start_id<<std::endl;
  }
  else{
    //vector to store friends of user with a particular degree
    std::vector <long int> friends;
    ADJ_TYPE::const_iterator it = adj_lists.begin();
    for(; it != adj_lists.end(); it++){
      if(it->second.size() == degree){
        for(int i = 0; i < og->second.size(); i++){
          if(it->first == (og->second)[i]){
            friends.push_back(it->first);
          }
        }
      }
    }
    //if the user doesn't have any friends with the degree
    if(friends.size() == 0){
      outfile << "User " << start_id << " has " << friends.size() << " friend(s) with degree " << degree << std::endl;
    }
    else{
      outfile << "User " << start_id << " has " << friends.size() << " friend(s) with degree " << degree << ":";
      for(int i = 0; i < friends.size(); i++){
        outfile << " " << friends[i];
      }
      outfile << std::endl;
    }
  }
}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to longest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance){
  GEO_TYPE::const_iterator it = locations.begin();
  //map that contains the distance as key and value of ID
  std::map <double,long int > temp;
  double distance;
  GEO_TYPE::const_iterator og_loc;
  ADJ_TYPE::const_iterator og;
  //holds iterator for start_id location
  og_loc = locations.find(start_id);
  //holds iterator for start_id
  og = adj_lists.find(start_id);
  //if there is no id found in map
  if(og == adj_lists.end()){
    outfile << "There is no user with friends and ID " << start_id << std::endl;
  }
  //if the id doesn't have a location 
  else if(og_loc == locations.end()){
    outfile << "User ID " << start_id << " does not have a recorded location." << std::endl;
  }
  else{
    //friends of user
    std::vector<long int> friends = og->second;
    for(; it != locations.end(); it++){
      for(int i = 0; i < friends.size(); i++){
        if(it->first == friends[i]){
          distance = distanceEarth((og_loc->second).first, (og_loc->second).second,(it->second).first,(it->second).second);
          if(distance < max_distance){
            //ads distance and id to the map
            temp[distance] = it->first;
          }
        }
      }
    }
    std::map <double, long int >::const_iterator it1 = temp.begin();
    if(temp.size() > 0){
      outfile << "Friends within " << max_distance << " km of user " << start_id << ":" << std::endl;
      for(; it1 != temp.end(); it1++){
        outfile << " " << it1->first << " km: " << it1->second <<std::endl;
      }
    }
    else
      outfile << "There are no friends within " << max_distance << " km of user " << start_id << std::endl;
  }
}

/**
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator-- O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0 diifference)
 *        It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed user's
 *               ID can have
 */
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset){
  //vector of ids close to the user
  std::vector<long int> ids;
  ADJ_TYPE::const_iterator forward = start_it;
  ADJ_TYPE::const_iterator backward = start_it;
  const long int first_val = start_it->first;
  //the user id is not valid
  if(start_it == end){
    outfile << "There is no user with the requested ID" << std::endl;
  }
  else{
    //ads the beigninng and end to the vector if its within offset
    if(start_it->first - offset == begin->first){
      ids.push_back(begin->first);
    }
    //iterates through offset to check if id is within range
    //from start to start-offset
    for(;backward != begin;backward--){
      if(backward->first >= (start_it->first - offset)){
        if(backward->first == first_val){
          continue;
        }
        else
          ids.push_back(backward->first);
      }
      else{
        break;
      }
    }
    //forward from start-it to offset
    for(;forward != end ;forward++){
        if(forward->first <= (start_it->first + offset)){
          if(forward->first == first_val){
            continue;
        }
        else
        ids.push_back(forward->first);
      }
      else{
        break;
      }
    }
    //sort the ids
    sort(ids.begin(), ids.end());
    if(ids.size() == 0){
      outfile << "There are no users with an ID within +/-" << offset << " of " << start_it->first<<std::endl;
    }
    else{
      outfile << "Users with an ID within +/-" << offset << " of " << start_it->first << ":";
      sort(ids.begin(), ids.end());
      for(int i = 0; i< ids.size(); i++){
        outfile << " " << ids[i];
      }
      outfile << std::endl;
    }
  }
}