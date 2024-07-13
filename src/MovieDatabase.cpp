#include "../include/MovieDatabase.h"
#include "../include/utils.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

void MovieDatabase::loadFromCSV(const std::string& filename) {
    std::string csvData = readCSVToString(filename);

    std::string delimiter = "¬";
    std::vector<std::string> fields = splitString(csvData, delimiter);

    std::vector<std::vector<std::string>> groupedData = groupData(fields, 6);

    removeQuotes(groupedData);

    for (int i = 0; i < groupedData.size(); ++i) {
        const auto& group = groupedData[i];
        if (group.size() == 6) {
            //uso del patron de diseño builder
            Movie movie = MovieBuilder().setImdbId(group[0])
                                        .setTitle(group[1])
                                        .setPlotSynopsis(group[2])
                                        .setTags(group[3])
                                        .setSplit(group[4])
                                        .setSynopsisSource(group[5])
                                        .build();
            movies[movie.imdb_id] = movie;
        } else {
            std::cerr << "Linea " << i+1 << " con formato incorrecto: ";
            for (const auto& element : group) {
                std::cerr << element << " ";
            }
            std::cerr << std::endl;
        }
    }

    std::cout << "Se cargaron " << movies.size() << " peliculas desde el archivo CSV." << std::endl;
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
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (const auto& pair : movies) {
        std::string lowerTitle = pair.second.title;
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

        if (lowerTitle.find(lowerQuery) != std::string::npos) {
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

std::vector<Movie> MovieDatabase::getRandomMovies() {
    std::vector<Movie> randomMovies;
    std::vector<std::string> keys;
    keys.reserve(movies.size());
    for (const auto& pair : movies) {
        keys.push_back(pair.first);
    }

    for (int i = 0; i < 10; ++i) {
        int randomIndex = rand() % keys.size();
        randomMovies.push_back(movies[keys[randomIndex]]);
        keys.erase(keys.begin() + randomIndex);
    }

    return randomMovies;
}

std::string MovieDatabase::getRandomTag(std::string tags) {
    std::vector<std::string> tagList = splitString(tags, ",");
    int randomIndex = rand() % tagList.size();
    return tagList[randomIndex];
}



std::vector<Movie> MovieDatabase::getRecommendedMovies_by_tag() {
    if (likedMovies.empty()) {
        // Si likedMovies está vacío, devuelve 10 películas aleatorias
        return getRandomMovies();
    }
    else if (likedMovies.size() == 1) {
        // Si likedMovies tiene solo una película, realiza una búsqueda por título con el título de la película
        std::string tag =getRandomTag(likedMovies[0].tags);
        std::vector<Movie> searchResults = searchByTag(tag);
        searchResults.resize(10);
        return searchResults;
    }
    else {
        // Crea un mapa para almacenar cada etiqueta y su recuento
        std::unordered_map<std::string, int> tagCount;

        // Recorre todas las películas en likedMovies
        for (const auto& movie : likedMovies) {
            // Divide las etiquetas y actualiza el recuento en el mapa
            std::vector<std::string> tags = splitString(movie.tags, ",");
            for (const auto& tag : tags) {
                ++tagCount[tag];
            }
        }

        // Encuentra la etiqueta con el recuento más alto en el mapa
        std::string mostFrequentTag;
        int maxCount = 0;
        for (const auto& pair : tagCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequentTag = pair.first;
            }
        }

        // Si todos los recuentos son iguales, toma la primera etiqueta del contenedor del mapa
        if (maxCount == 1) {
            mostFrequentTag = tagCount.begin()->first;
        }

        // Realiza una búsqueda por etiqueta con la etiqueta más frecuente
        std::vector<Movie> searchResults = searchByTag(mostFrequentTag);

        // Si hay más de 10 resultados, reduce el vector a los primeros 10
        if (searchResults.size() > 10) {
            searchResults.resize(10);
        }

        return searchResults;
    }
}

void MovieDatabase::addToWatchLater(const std::string& id) {
    // Verifica si la película ya está en watchLater
    auto it = std::find_if(watchLater.begin(), watchLater.end(), [&id](const Movie& movie) {
        return movie.imdb_id == id;
    });

    // Si la película no está en watchLater, la agrega
    if (it == watchLater.end()) {
        watchLater.push_back(movies[id]);
    }
}

void MovieDatabase::likeMovie(const std::string& id) {
    // Verifica si la película ya está en likedMovies
    auto it = std::find_if(likedMovies.begin(), likedMovies.end(), [&id](const Movie& movie) {
        return movie.imdb_id == id;
    });

    // Si la película no está en likedMovies, la agrega
    if (it == likedMovies.end()) {
        likedMovies.push_back(movies[id]);
    }
}

Movie MovieDatabase::getMovieById(const std::string& imdb_id) {
    return movies[imdb_id];
}

std::vector<Movie> MovieDatabase::getLikedMovies() {
    return likedMovies;
}

std::vector<Movie> MovieDatabase::getRecommendedMovies_by_title() {
    if (likedMovies.empty()) {
        // Si likedMovies está vacío, devuelve 10 películas aleatorias
        return getRandomMovies();
    } else {
        // Crea un mapa para almacenar cada palabra y su recuento
        std::unordered_map<std::string, int> wordCount;

        // Recorre todas las películas en likedMovies
        for (const auto& movie : likedMovies) {
            // Divide el título en palabras
            std::vector<std::string> words = splitString(movie.title, " ");

            // Filtra las palabras que tienen menos de 4 caracteres y actualiza el recuento en el mapa
            for (const auto& word : words) {
                if (word.length() >= 4) {
                    ++wordCount[word];
                }
            }
        }

        // Encuentra la palabra con el recuento más alto en el mapa
        std::string mostFrequentWord;
        int maxCount = 0;
        for (const auto& pair : wordCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequentWord = pair.first;
            }
        }

        // Si todos los recuentos son iguales, toma la primera palabra del contenedor del mapa
        if (maxCount == 1) {
            mostFrequentWord = wordCount.begin()->first;
        }

        // Realiza una búsqueda por título con la palabra más frecuente
        std::vector<Movie> searchResults = searchByTitle(mostFrequentWord);

        // Si hay más de 10 resultados, reduce el vector a los primeros 10
        if (searchResults.size() > 10) {
            searchResults.resize(10);
        }

        return searchResults;
    }
}

void MovieDatabase::removeWatchLater(const std::string &id) {
    watchLater.erase(std::remove_if(watchLater.begin(), watchLater.end(), [id](const Movie& movie) {
        return movie.imdb_id == id;
    }), watchLater.end());

}

void MovieDatabase::removeLikedMovie(const std::string &id) {
    likedMovies.erase(std::remove_if(likedMovies.begin(), likedMovies.end(), [id](const Movie& movie) {
        return movie.imdb_id == id;
    }), likedMovies.end());
}
