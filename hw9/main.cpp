#include <iostream>
#include <string>
#include <utility>
#include <cassert>
#include <vector>
#include <map>
#include "ds_hashset.h"
#include <fstream>
#include "Movie.h"
#include <list>

class hash_string_obj {
public:
  unsigned int operator() ( const std::string& key ) const {
    //  This implementation comes from 
    //  http://www.partow.net/programming/hashfunctions/
    //
    //  This is a general-purpose, very good hash function for strings.
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
  }   
};

typedef ds_hashset<Movie, hash_string_obj> hashtable;

int main() {
  //variables for the input
  std::string title;
  std::string year;
  std::string min;
  std::vector<std::string> genres;
  std::map<std::string, std::string> actors;
  std::vector<std::string> ids;
  std::vector<std::string> roles;
  std::string id;
  std::string actor;
  std::vector<Movie> og_movies;//vector of parent(full) movies
  int table_size = 100;
  float occupancy = .5;
  std::string prompt;
  std::cin >> prompt;

  while(prompt != "movies"){//checks if the table size and the occupancy are given 
    if(prompt == "table_size"){
      std::cin >> table_size;
    }
    std::cin >> prompt;
    if(prompt == "occupancy"){
      std::cin >> occupancy;
    }
  }
  hashtable movie_table(table_size);//creates the table
  movie_table.setOccupancy(occupancy);//sets the occupancy
  //file of full movies
  if(prompt == "movies"){
    std::string movie_file;
    std::cin >> movie_file;
    std::ifstream in_str(movie_file);
    if(!in_str.good()){
      std::cerr <<"Can't open.\n";
      exit(1);
    }
    int parent = 0;//holds index
    //gets each movies information
    while(in_str >> title >> year >> min){
      std::vector<std::string> genres;
      std::vector<std::string> ids;
      std::vector<std::string> roles;
      int genre_num;
      int id_num;
      int role_num;
      in_str >> genre_num;
      std::string genre;
      for(int i = 0; i < genre_num; i++){
        in_str >> genre;
        genres.push_back(genre);//stores each genre
      }
      in_str >> id_num;
      for(int i = 0; i < id_num; i++){
        in_str >> id;
        ids.push_back(id);//stores all ids
      }
      in_str >> role_num;
      for(int i = 0; i < role_num; i++){
        std::string role;
        in_str >> role;
        roles.push_back(role);//stores all roles;
      }
      //creates a movie object
      Movie current(title, year, min, genres,ids, roles, 0);
      og_movies.push_back(current);//stores all movies in vector
      //index of which parent movie in vector 
      parent++;
      //start of making partials for each parent(full) movie
      std::string p_title;
      std::string p_year;
      std::string p_min;
      std::vector<std::string> p_genres;
      std::vector<std::string> p_ids;
      std::vector<std::string> p_roles;
      //creates 64 different possible combinations by either adding 
      //variable or not adding it to movie
      for(int a = 0; a < 2; a++){
        for(int b = 0; b < 2; b++){
          for(int c = 0; c < 2; c++){
            for(int d = 0; d < 2; d++){
              for(int e = 0; e < 2 ; e++){
                for(int f = 0; f < 2; f++){
                  if(a == 0){
                    p_title = "?";//no title
                  }
                  if(a == 1){
                    p_title = title;//add title
                  }
                  if(b == 0){
                    p_year = "?";//no year
                  }
                  if(b == 1){
                    p_year = year;//add year
                  }
                  if(c == 0){
                    p_min = "?";//no minutes
                  }
                  if(c == 1){
                    p_min = min;//add minutes
                  }
                  if(d == 0){
                    p_genres.clear();//no genres
                  }
                  if(d == 1){
                    p_genres.clear();//reset genres for each partial
                    for(int i = 0; i < genres.size(); i++){
                      p_genres.push_back(genres[i]);//add genres
                    }
                  }
                  if(e == 0){
                    p_ids.clear();//no ids
                  }
                  if(e == 1){
                    p_ids.clear();//reset ids for each partial
                    for(int i = 0; i < ids.size(); i++){
                      p_ids.push_back(ids[i]);//add partials
                    }
                  }
                  if(f == 0){
                    p_roles.clear();//no roles
                  }
                  if(f == 1){
                    p_roles.clear();//reset roles for each partial
                    for(int i = 0; i < roles.size(); i++){
                      p_roles.push_back(roles[i]);//add roles
                    }
                  }
                  //create movie object of each partial movie
                  Movie partials(p_title, p_year, p_min, p_genres,
                   p_ids, p_roles, parent);//last parameter holds index of parent movie
                  //insert each partial into table(includes full movie)
                  movie_table.insert(partials);
                }
              }
            }
          }
        }
      }
    }
  }
  std::cin >> prompt; 
  if( prompt == "actors"){
      std::string actors_file;
      std::cin >> actors_file;//get actor file
      std::ifstream in_str1(actors_file);
  if(!in_str1.good()){
      std::cerr <<"Can't open.\n";//if file can't be opened
      exit(1);
  }
  while(in_str1 >> id >> actor){
      actors[id] = actor;//read file input into a map of ids and actors
    }
  }
  //read in queries
  while(true){
    //query input variables
    std::string q_title;
    std::string q_year;
    std::string q_min;
    std::vector<std::string> q_genres;
    std::vector<std::string> q_ids;
    std::vector<std::string> q_roles;
    int num;
    std::string in;
    std::cin >>prompt;
    //ends the loop at the end of input file queries
    if(prompt == "quit"){
      break;
    }
    //gets all input for queries
    if(prompt == "query"){
      std::cin >> q_title;
      std::cin >> q_year;
      std::cin >> q_min;
      std::cin >> num;
      for(int i = 0; i < num; i++){
        std::cin >> in;
        q_genres.push_back(in);//store genres
      }
      std::cin >> num;
      for(int i = 0; i < num; i++){
        std::cin >> in;
        q_ids.push_back(in);//store ids
      }
      std::cin >> num;
      for(int i = 0; i < num; i++){
        std::cin >> in;
        q_roles.push_back(in);//store roles
      }
      //create a movie object for queries
      Movie query(q_title, q_year, q_min, q_genres, q_ids, q_roles, 0);
      std::list<Movie> answer;
      answer = movie_table.find(query); //find all movies that match query
      //checks if there were any matches
      if(answer.size() == 0){
        std::cout << "No results for query." << std::endl;
      }
      else{
        std::list<Movie>::const_iterator it;
        std::vector<std::string> parent_genres;
        std::vector<std::string> parent_ids;
        std::vector<std::string> parent_roles;
        //print how many movies matched the query
        std::cout << "Printing " << answer.size() << " result(s):" << std::endl;
        //goes through list of movies and prints information from original movie vector
        for(it = answer.begin(); it != answer.end(); it++){
          std::cout << og_movies[(it->getParent())-1].getTitle()<<std::endl;
          std::cout << og_movies[(it->getParent())-1].getYear() << std::endl;
          std::cout << og_movies[(it->getParent())-1].getMin() << std::endl;
          parent_genres = og_movies[(it->getParent())-1].getGenres();
          std::cout << parent_genres.size();
          for(int i = 0; i < parent_genres.size(); i++){
            std::cout << " " << parent_genres[i];//prints each genre
          }
          std::cout << std::endl;
          parent_ids = og_movies[it->getParent()-1].getActors();
          parent_roles = og_movies[it->getParent()-1].getRoles();
          std::cout << parent_ids.size();
          //goes through ids and prints out its counterpart from map
          for(int i = 0; i < parent_ids.size(); i++){
            std::cout << " " << actors[parent_ids[i]];//gets info from map
            std::cout << " (" << parent_roles[i] << ")";//prints role
          }
          std::cout << std::endl;
        }
      }
    }
  }
  return 0;
}