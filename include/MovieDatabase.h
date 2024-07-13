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
private:
    std::unordered_map<std::string, Movie> movies;
    std::vector<Movie> watchLater;
    std::vector<Movie> likedMovies;

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
};


#endif //MYCPPRESTPROJECT_MOVIEDATABASE_H
