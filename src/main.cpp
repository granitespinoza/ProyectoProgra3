#include "crow.h"
#include "../include/MovieDatabase.h"

struct CORS {
    struct context {};
    void before_handle(crow::request& req, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    }

    void after_handle(crow::request& /*req*/, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    }
};

int main() {
    crow::App<CORS> app; // Crear una aplicación Crow con CORS habilitado


    // Acceder a la instancia de MovieDatabase a través del método getInstance
    auto& db = MovieDatabase::getInstance();
    db.loadFromCSV("../data/movies.csv");

    CROW_ROUTE(app, "/get_WatchLater")
        .methods("GET"_method)([&db](){
        auto movies = db.getMoviesToWatchLater();
        crow::json::wvalue x;
        for (size_t i = 0; i < movies.size(); ++i) {
            const auto& movie = movies[i];
            crow::json::wvalue movie_json;
            movie_json["id"] = movie.imdb_id;
            movie_json["tags"]= movie.tags;
            movie_json["title"] = movie.title;
            movie_json["synopsis"] = movie.plot_synopsis;
            x["movies"][i] = std::move(movie_json);
        }
        return x;
    });

    CROW_ROUTE(app, "/search")
            .methods("POST"_method)([&db](const crow::request& req){
                auto body = crow::json::load(req.body);
                if (!body) {
                    return crow::response(400, "Invalid JSON");
                }
                std::string query = body["query"].s();
                auto results = db.searchByTitle(query);
                crow::json::wvalue x;
                for (size_t i = 0; i < results.size(); ++i) {
                    const auto& movie = results[i];
                    crow::json::wvalue movie_json;
                    movie_json["title"] = movie.title;
                    movie_json["synopsis"] = movie.plot_synopsis;
                    x["results"][i] = std::move(movie_json);
                }
                return crow::response(x);
            });

    CROW_ROUTE(app, "/tag/<string>")
            .methods("GET"_method)([&db](const std::string& tag){
                auto results = db.searchByTag(tag);
                crow::json::wvalue x;
                for (size_t i = 0; i < results.size(); ++i) {
                    const auto& movie = results[i];
                    crow::json::wvalue movie_json;

                    movie_json["id"] = movie.imdb_id;
                    movie_json["title"] = movie.title;
                    movie_json["tags"] = movie.tags;
                    movie_json["synopsis"] = movie.plot_synopsis;
                    x["results"][i] = std::move(movie_json);
                }
                return crow::response(x);
            });

    CROW_ROUTE(app, "/movies/<int>/<int>")
    .methods("GET"_method)([&db](const int& page, const int& pageSize){
        auto pageMovies = db.getMoviesByPage(page, pageSize);
        crow::json::wvalue x;
        for (size_t i = 0; i < pageMovies.size(); ++i) {
            const auto& movie = pageMovies[i];
            crow::json::wvalue movie_json;
            movie_json["id"] = movie.imdb_id;
            movie_json["title"] = movie.title;
            movie_json["tags"] = movie.tags;
            movie_json["synopsis"] = movie.plot_synopsis;
            x["movies"][i] = std::move(movie_json);
        }
        return crow::response(x);
    });

    CROW_ROUTE(app, "/like")
            .methods("POST"_method)([&db](const crow::request& req){
                auto body = crow::json::load(req.body);
                if (!body) {
                    return crow::response(400, "Invalid JSON");
                }
                std::string id = body["id_movie"].s();
                auto movie = db.getMovieById(id);
                if (movie.imdb_id.empty()) {
                    return crow::response(404, "Movie not found");
                }
                db.likeMovie(id); // Assuming exact match
                return crow::response(200);
            });

    CROW_ROUTE(app, "/watchlater")
            .methods("POST"_method)([&db](const crow::request& req){
                auto body = crow::json::load(req.body);
                if (!body) {
                    return crow::response(400, "Invalid JSON");
                }
                std::string id = body["id_movie"].s();
                auto movie = db.getMovieById(id);
                if (movie.imdb_id.empty()) {
                    return crow::response(404, "Movie not found");
                }
                db.addToWatchLater(id); // Assuming exact match
                return crow::response(200);
            });

    CROW_ROUTE(app, "/recommended_by_tag")
            .methods("GET"_method)([&db](){
                auto movies = db.getRecommendedMovies_by_tag();
                crow::json::wvalue x;
                for (size_t i = 0; i < movies.size(); ++i) {
                    const auto& movie = movies[i];
                    crow::json::wvalue movie_json;
                    movie_json["id"] = movie.imdb_id;
                    movie_json["title"] = movie.title;
                    movie_json["tags"] = movie.tags;
                    movie_json["synopsis"] = movie.plot_synopsis;
                    x["movies"][i] = std::move(movie_json);
                }
                return crow::response(x);
            });

    CROW_ROUTE(app, "/recommended_by_title")
            .methods("GET"_method)([&db](){
                auto movies = db.getRecommendedMovies_by_title();
                crow::json::wvalue x;
                for (size_t i = 0; i < movies.size(); ++i) {
                    const auto& movie = movies[i];
                    crow::json::wvalue movie_json;
                    movie_json["id"] = movie.imdb_id;
                    movie_json["title"] = movie.title;
                    movie_json["tags"] = movie.tags;
                    movie_json["synopsis"] = movie.plot_synopsis;
                    x["movies"][i] = std::move(movie_json);
                }
                return crow::response(x);
            });

    CROW_ROUTE(app,"/get_movies_liked")
            .methods("GET"_method)([&db](){
                auto movies = db.getLikedMovies();
                crow::json::wvalue x;
                for (size_t i = 0; i < movies.size(); ++i) {
                    const auto& movie = movies[i];
                    crow::json::wvalue movie_json;
                    movie_json["id"] = movie.imdb_id;
                    movie_json["title"] = movie.title;
                    movie_json["tags"] = movie.tags;
                    movie_json["synopsis"] = movie.plot_synopsis;
                    x["movies"][i] = std::move(movie_json);
                }
                return crow::response(x);
            });


    CROW_ROUTE(app,"/remove_watchlater")
            .methods("POST"_method)([&db](const crow::request& req){
                auto body = crow::json::load(req.body);
                if (!body) {
                    return crow::response(400, "Invalid JSON");
                }
                std::string id = body["id_movie"].s();
                auto movie = db.getMovieById(id);
                if (movie.imdb_id.empty()) {
                    return crow::response(404, "Movie not found");
                }
                db.removeWatchLater(id); // Assuming exact match
                return crow::response(200);
            });

    CROW_ROUTE(app,"/remove_liked")
            .methods("POST"_method)([&db](const crow::request& req){
                auto body = crow::json::load(req.body);
                if (!body) {
                    return crow::response(400, "Invalid JSON");
                }
                std::string id = body["id_movie"].s();
                auto movie = db.getMovieById(id);
                if (movie.imdb_id.empty()) {
                    return crow::response(404, "Movie not found");
                }
                db.removeLikedMovie(id); // Assuming exact match
                return crow::response(200);
            });

    app.port(18080).multithreaded().run(); // Ejecutar la aplicación en el puerto 18080
}
