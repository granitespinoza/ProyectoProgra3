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
    crow::App<CORS> app; // Usa el middleware CORS

    MovieDatabase db;
    db.loadFromCSV("../data/movies.csv");

    CROW_ROUTE(app, "/")([&db](){
        auto movies = db.getMoviesToWatchLater();
        crow::json::wvalue x;
        for (size_t i = 0; i < movies.size(); ++i) {
            const auto& movie = movies[i];
            crow::json::wvalue movie_json;
            movie_json["title"] = movie.title;
            movie_json["synopsis"] = movie.synopsis;
            x["movies"][i] = std::move(movie_json);
        }
        return x;
    });

    CROW_ROUTE(app, "/search")
            .methods("POST"_method)([&db](const crow::request& req){
                auto body = crow::json::load(req.body);
                std::string query = body["query"].s();
                auto results = db.searchByTitle(query);
                crow::json::wvalue x;
                for (size_t i = 0; i < results.size(); ++i) {
                    const auto& movie = results[i];
                    crow::json::wvalue movie_json;
                    movie_json["title"] = movie.title;
                    movie_json["synopsis"] = movie.synopsis;
                    x["results"][i] = std::move(movie_json);
                }
                crow::response res(x);
                return res;
            });
    CROW_ROUTE(app, "/tag/<string>")([&db](const std::string& tag){
        auto results = db.searchByTag(tag);
        crow::json::wvalue x;
        for (size_t i = 0; i < results.size(); ++i) {
            const auto& movie = results[i];
            crow::json::wvalue movie_json;
            movie_json["title"] = movie.title;
            movie_json["synopsis"] = movie.synopsis;
            x["results"][i] = std::move(movie_json);
        }
        crow::response res(x);
        return res;
    });

    CROW_ROUTE(app, "/like")
            .methods("POST"_method)([&db](const crow::request& req){
                auto body = crow::json::load(req.body);
                std::string title = body["title"].s();
                db.likeMovie(db.searchByTitle(title)[0]); // Assuming exact match
                crow::response res(200);
                return res;
            });

    CROW_ROUTE(app, "/watchlater")
            .methods("POST"_method)([&db](const crow::request& req){
                auto body = crow::json::load(req.body);
                std::string title = body["title"].s();
                db.addToWatchLater(db.searchByTitle(title)[0]); // Assuming exact match
                crow::response res(200);
                return res;
            });

    app.port(18080).multithreaded().run(); // Ejecutar la aplicación en el puerto 18080
}
