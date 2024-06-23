#include "../include/MovieDatabase.h"
#include "../include/utils.h"
#include <iostream>
#include <vector>

void MovieDatabase::loadFromCSV(const std::string& filename) {
    std::string csvData = readCSVToString(filename);

    std::string delimiter = "¬";
    std::vector<std::string> fields = splitString(csvData, delimiter);

    std::vector<std::vector<std::string>> groupedData = groupData(fields, 6);

    removeQuotes(groupedData);

    for (const auto& group : groupedData) {
        if (group.size() == 6) {
            Movie movie;
            movie.imdb_id = group[0];
            movie.title = group[1];
            movie.plot_synopsis = group[2];
            movie.tags = group[3];
            movie.split = group[4];
            movie.synopsis_source = group[5];
            movies[movie.imdb_id] = movie;
        } else {
            std::cerr << "Línea con formato incorrecto." << std::endl;
        }
    }

    std::cout << "Se cargaron " << movies.size() << " películas desde el archivo CSV." << std::endl;
}

std::vector<Movie> MovieDatabase::getMoviesByPage(int page, int pageSize) {
    std::vector<Movie> pageMovies;
    if (page < 1 || pageSize < 1 || (page - 1) * pageSize >= movies.size()) {
        return pageMovies; // Retorna un vector vacío si los parámetros de la página son inválidos
    }

    // Calcular el inicio y el final de la página
    size_t start = (page - 1) * pageSize;
    size_t end = std::min(movies.size(), start + pageSize);

    // Copiar las películas de la página al vector pageMovies
    auto it = movies.begin();
    std::advance(it, start);
    for (size_t i = start; i < end; ++i, ++it) {
        pageMovies.push_back(it->second);
    }

    return pageMovies;
}

std::vector<Movie> MovieDatabase::searchByTitle(const std::string& query) {
    std::vector<Movie> results;
    for (const auto& pair : movies) {
        if (pair.second.title.find(query) != std::string::npos) {
            results.push_back(pair.second);
        }
    }
    return results;
}

std::vector<Movie> MovieDatabase::searchByTag(const std::string& tag) {
    std::vector<Movie> results;
    for (const auto& pair : movies) {
        if (pair.second.tags.find(tag) != std::string::npos) {
            results.push_back(pair.second);
        }
    }
    return results;
}

std::vector<Movie> MovieDatabase::getMoviesToWatchLater() {
    return watchLater;
}

std::vector<Movie> MovieDatabase::getRecommendedMovies() {
    return likedMovies;
}

void MovieDatabase::addToWatchLater(const Movie& movie) {
    watchLater.push_back(movie);
}

void MovieDatabase::likeMovie(const Movie& movie) {
    likedMovies.push_back(movie);
}
