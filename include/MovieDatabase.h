#ifndef MYCPPRESTPROJECT_MOVIEDATABASE_H
#define MYCPPRESTPROJECT_MOVIEDATABASE_H
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator> // Necesario para std::iterator_traits

struct Movie {
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::string tags;
    std::string split;
    std::string synopsis_source;
};

class MovieDatabase {
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Movie;
        using pointer = Movie*;
        using reference = Movie&;

        Iterator(std::unordered_map<std::string, Movie>::iterator it) : it_(it) {}

        Iterator& operator++() {
            ++it_;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return it_ != other.it_;
        }

        reference operator*() {
            return it_->second;
        }

    private:
        std::unordered_map<std::string, Movie>::iterator it_;
    };

    Iterator begin() {
        return Iterator(movies.begin());
    }

    Iterator end() {
        return Iterator(movies.end());
    }

    void loadFromCSV(const std::string& filename);
    std::vector<Movie> getMoviesByPage(int page, int pageSize);
    std::vector<Movie> searchByTitle(const std::string& query);
    std::vector<Movie> searchByTag(const std::string& tag);
    std::vector<Movie> getMoviesToWatchLater();
    std::vector<Movie> getRecommendedMovies_by_tag();
    std::vector<Movie> getRecommendedMovies_by_title();
    void addToWatchLater(const std::string& id);
    void likeMovie(const std::string& id);
    std::vector<Movie> getRandomMovies();
    std::string getRandomTag(std::string tags);
    std::vector<Movie> getLikedMovies();
    Movie getMovieById(const std::string& imdb_id);
    void removeWatchLater(const std::string& id);
    void removeLikedMovie(const std::string& id);

private:
    std::unordered_map<std::string, Movie> movies;
    std::vector<Movie> watchLater;
    std::vector<Movie> likedMovies;
};

#endif //MYCPPRESTPROJECT_MOVIEDATABASE_H
