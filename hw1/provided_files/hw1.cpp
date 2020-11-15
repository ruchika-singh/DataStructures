#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//function dilates pixels at the border of a cluster
void dilation(std::vector<std::string> &grid, char value)
{
  std::vector<std::string>grid_copy = grid;//creates copy of original grid
  for(int i = 0; i< grid_copy.size(); i++)
  {
    for(int j = 0; j < grid_copy[i].size(); j++)
    {
      //checks to make sure pixel is within bounds
      if (i-1 >= 0 && j-1 >= 0 && i+1 <= grid_copy.size() && j+1 <= grid_copy[i].size())
        if (grid_copy[i+1][j] == value || grid_copy[i-1][j] == value || 
        grid_copy[i][j+1] == value || grid_copy[i][j-1] == value)
          grid[i][j] = value;
    }
  }
}
//function shrinks boundry of a cluster of pixels
void erosion(std::vector<std::string> &grid, char back_round)
{
  std::vector<std::string>grid_copy = grid;
  for(int i = 0; i< grid_copy.size(); i++)
  {
    for(int j = 0; j < grid_copy[i].size(); j++)
    {
      if (i-1 >= 0 && j-1 >= 0 && i+1 <= grid_copy.size() && j+1 <= grid_copy[i].size())//checks bounds
        if (grid_copy[i+1][j] == back_round || grid_copy[i-1][j] == back_round ||
        grid_copy[i][j+1] == back_round ||grid_copy[i][j-1] == back_round)
          grid[i][j] = back_round;
    }
  }
}
//function replaces the pixels with different characters
void replace(std::vector<std::string>&grid, char orig, char new_char)
{
  for(int i = 0; i< grid.size(); i++)
  {
    for(int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == orig)
        grid[i][j] = new_char;
    }
  }
}

int main (int argc, char* argv[]){
  std::string line;
  std::ifstream myfile (argv[1]);//input file
  std::ofstream outfile (argv[2]);//output file
  std::vector<std::string> grid;
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
        getline (myfile,line);
        grid.push_back(line);
    }
    myfile.close();
  }
  else 
    std::cout << "Unable to open file";
  if (outfile.is_open())
  {
    if ( !outfile.good() )
    {
      std::cerr << "Can't open " << argv[4] << " to write.\n";
      exit(1);
    }
  }

  if (std::string(argv[3]) == std::string("replace"))
  {
    if (argc > 6 || argc < 6)
    {
      std::cerr << "Not the correct amount of input needed"<<std::endl;
      exit(1);
    }
    else
      replace(grid,*argv[4],*argv[5]); 
  }
  else if (std::string(argv[3]) == std::string("dilation"))
  {
    if (argc > 5 || argc < 5)
    {
      std::cerr << "Not the correct amount of input needed"<<std::endl;
      exit(1);
    }
    else
      dilation(grid,*argv[4]);
  }
  else if (std::string(argv[3]) == std::string("erosion"))
  {
    if (argc > 6 || argc < 6)
    {
      std::cerr << "Not the correct amount of input needed"<<std::endl;
      exit(1);
    }
    else
      erosion(grid,*argv[5] );
  }
  for (int i = 0; i< grid.size()-1; i++)
  {
      outfile<<grid[i]<<std::endl;//rewrites grid to outfile
  }
  outfile.close();
  return 0;
}