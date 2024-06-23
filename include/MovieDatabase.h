//
// Created by Usuario on 20/06/2024.
//

#ifndef MYCPPRESTPROJECT_MOVIEDATABASE_H
#define MYCPPRESTPROJECT_MOVIEDATABASE_H
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>


struct Movie {
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::string tags;
    std::string split;
    std::string synopsis_source;
};

class MovieDatabase {
private:
    std::unordered_map<std::string, Movie> movies;
    std::vector<Movie> watchLater;
    std::vector<Movie> likedMovies;

public:

    void loadFromCSV(const std::string& filename);
    std::vector<Movie> getMoviesByPage(int page, int pageSize);
    std::vector<Movie> searchByTitle(const std::string& query);
    std::vector<Movie> searchByTag(const std::string& tag);
    std::vector<Movie> getMoviesToWatchLater();
    std::vector<Movie> getRecommendedMovies_by_tag();
    void addToWatchLater(const std::string& id);
    void likeMovie(const std::string& id);
    std::vector<Movie> getRandomMovies();
    std::string getRandomTag(std::string tags);
    std::vector<Movie> getLikedMovies();
    Movie getMovieById(const std::string& imdb_id);
};


#endif //MYCPPRESTPROJECT_MOVIEDATABASE_H
