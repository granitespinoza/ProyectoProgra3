//
// Created by Usuario on 20/06/2024.
//

#ifndef MYCPPRESTPROJECT_MOVIEDATABASE_H
#define MYCPPRESTPROJECT_MOVIEDATABASE_H
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator> // Necesario para std::iterator_traits
#include <stack>



struct Movie {
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::string tags;
    std::string split;
    std::string synopsis_source;
};

//implementar Patron Memento

class Memento {
private:
    std::vector<Movie> watchLater;
    std::vector<Movie> likedMovies;
public:
    Memento(std::vector<Movie> watchLater, std::vector<Movie> likedMovies) : watchLater(std::move(watchLater)), likedMovies(std::move(likedMovies)) {}
    std::vector<Movie> getWatchLater() {
        return watchLater;
    }
    std::vector<Movie> getLikedMovies() {
        return likedMovies;
    }
};

// Definición de la clase MovieBuilder
class MovieBuilder {
private:
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::string tags;
    std::string split;
    std::string synopsis_source;

public:
    MovieBuilder& setImdbId(const std::string& id) {
        imdb_id = id;
        return *this;
    }

    MovieBuilder& setTitle(const std::string& t) {
        title = t;
        return *this;
    }

    MovieBuilder& setPlotSynopsis(const std::string& plot) {
        plot_synopsis = plot;
        return *this;
    }

    MovieBuilder& setTags(const std::string& t) {
        tags = t;
        return *this;
    }

    MovieBuilder& setSplit(const std::string& s) {
        split = s;
        return *this;
    }

    MovieBuilder& setSynopsisSource(const std::string& source) {
        synopsis_source = source;
        return *this;
    }

    Movie build() {
        return {imdb_id, title, plot_synopsis, tags, split, synopsis_source};
    }
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

private:
    std::unordered_map<std::string, Movie> movies;
    std::vector<Movie> watchLater;
    std::vector<Movie> likedMovies;

    // Memento
    std::stack<Memento> history;

    // Constructor privado
    MovieDatabase() {}

    // Constructor de copia y operador de asignación privados
    MovieDatabase(const MovieDatabase&) = delete;
    MovieDatabase& operator=(const MovieDatabase&) = delete;

public:
    // Método estático para acceder a la instancia
    static MovieDatabase& getInstance() {
        static MovieDatabase instance;
        return instance;
    }


    bool historyIsEmpty();
    void saveStateToMemento();
    void updateState();
    void restoreStateFromMemento();
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
    static std::string getRandomTag(const std::string& tags);
    std::vector<Movie> getLikedMovies();
    Movie getMovieById(const std::string& imdb_id);
    void removeWatchLater(const std::string& id);
    void removeLikedMovie(const std::string& id);
};


#endif //MYCPPRESTPROJECT_MOVIEDATABASE_H
