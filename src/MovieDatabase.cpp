#include "../include/MovieDatabase.h"
#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

void MovieDatabase::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    // Saltar la primera línea si contiene encabezados
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string title, synopsis, tag;

        std::getline(ss, title, ',');
        std::getline(ss, synopsis, ',');
        std::getline(ss, tag, ',');

        Movie movie = {title, synopsis, tag};
        movies[title] = movie;
    }

    std::cout << "Loaded " << movies.size() << " movies from CSV file." << std::endl;
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
        if (pair.second.tag == tag) {
            results.push_back(pair.second);
        }
    }
    return results;
}

std::vector<Movie> MovieDatabase::getMoviesToWatchLater() {
    return watchLater;
}

std::vector<Movie> MovieDatabase::getRecommendedMovies() {
    // Implement your own recommendation algorithm
    return likedMovies; // Simple example: return liked movies
}

void MovieDatabase::addToWatchLater(const Movie& movie) {
    watchLater.push_back(movie);
}

void MovieDatabase::likeMovie(const Movie& movie) {
    likedMovies.push_back(movie);
}