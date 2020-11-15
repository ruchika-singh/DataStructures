class Movie{
  public:
    Movie(std::string aTitle, std::string aYear, std::string aMinutes,
     std::vector<std::string> aGenres, std::vector<std::string> aActorID, 
     std::vector<std::string> aRoles, int aParent){
      title = aTitle;
      year = aYear;
      min = aMinutes;
      genres = aGenres;
      actorsID = aActorID;
      roles = aRoles;
      parent = aParent;
    }
    //accessor functions
    std::string getTitle() const{return title;}
    std::string getYear() const {return year;}
    std::string getMin() const {return min;}
    std::vector<std::string> getGenres() const {return genres;}
    std::vector<std::string> getActors() const {return actorsID;}
    std::vector<std::string> getRoles() const {return roles;}
    int getParent() const {return parent;}

    //compare operator to check if movies are not equal to each other
    bool operator!=(Movie& other){
      if (this->getTitle() != other.getTitle() || this->getYear() != other.getYear()
       || this->getMin() != other.getMin())
        return true;
      if(this->getGenres().size() != other.getGenres().size()) 
        return true;
      std::vector<std::string> g = this->getGenres();
      std::vector<std::string> g1 = other.getGenres();
      for(int i = 0; i < g.size(); i++){
        if(g[i] != g1[i]) 
          return true;
      }
      std::vector<std::string> a = this->getActors();
      std::vector<std::string> a1 = other.getActors();
      for(int i = 0; i < a.size(); i++){
        if(a[i] != a1[i]) 
          return true;
      }
      std::vector<std::string> r = this->getRoles();
      std::vector<std::string> r1 = other.getRoles();
      for(int i = 0; i < r.size(); i++){
        if(r[i] != r1[i]) 
          return true;
      }
      return false;
    }

    //compare if two movies are equal to each other 
    bool operator==(Movie& other){
      if (this->getTitle() != other.getTitle() || this->getYear() != other.getYear()
       || this->getMin() != other.getMin())
        return false;
      //compare size before comparing each individual string in vector
      if(this->getGenres().size() != other.getGenres().size()) 
        return false;
      std::vector<std::string> g = this->getGenres();
      std::vector<std::string> g1 = other.getGenres();
      for(int i = 0; i < g.size(); i++){
        if(g[i] != g1[i]) 
          return false;
      }
      if(this->getActors().size() != other.getActors().size()) 
        return false;
      std::vector<std::string> a = this->getActors();
      std::vector<std::string> a1 = other.getActors();
      for(int i = 0; i < a.size(); i++){
        if(a[i] != a1[i]) 
          return false;
      }
      if(this->getRoles().size() != other.getRoles().size()) 
        return false;
      std::vector<std::string> r = this->getRoles();
      std::vector<std::string> r1 = other.getRoles();
      for(int i = 0; i < r.size(); i++){
        if(r[i] != r1[i]) 
          return false;
      }
      return true;
    }
  private:
    std::string title;
    std::string year;
    std::string min;
    std::vector<std::string> genres;
    std::vector<std::string> actorsID;
    std::vector<std::string> roles;
    int parent;
};