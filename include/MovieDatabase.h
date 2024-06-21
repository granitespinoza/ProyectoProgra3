//
// Created by Usuario on 20/06/2024.
//

#ifndef MYCPPRESTPROJECT_MOVIEDATABASE_H
#define MYCPPRESTPROJECT_MOVIEDATABASE_H

#include <string>
#include <unordered_map>
#include <vector>

struct Movie {
    std::string title;
    std::string synopsis;
    std::string tag;
};

class MovieDatabase {
public:
    void loadFromCSV(const std::string& filename);
    std::vector<Movie> searchByTitle(const std::string& query);
    std::vector<Movie> searchByTag(const std::string& tag);
    std::vector<Movie> getMoviesToWatchLater();
    std::vector<Movie> getRecommendedMovies();
    void addToWatchLater(const Movie& movie);
    void likeMovie(const Movie& movie);

private:
    std::unordered_map<std::string, Movie> movies;
    std::vector<Movie> watchLater;
    std::vector<Movie> likedMovies;
};


#endif //MYCPPRESTPROJECT_MOVIEDATABASE_H
