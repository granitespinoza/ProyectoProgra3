import {useState} from "react";
import {get_movies} from "../api/api.js";

const Movies = () => {
    const [movies, setMovies] = useState([])
    const [search, setSearch] = useState("")

    const searchMovies = async (e) => {
        e.preventDefault();
        try {
            const response = await get_movies(search);
            setMovies(response);
        } catch (error) {
            console.error(error);
        }
    }

    return (
        <div>
            <h1>Movies</h1>
            <form onSubmit={searchMovies}>
                <input type="text" value={search} onChange={e => setSearch(e.target.value)} />
                <button type="submit">Buscar</button>
            </form>
            {movies.map((movie, index) => (
                <div key={index}>
                    <h2>{movie.title}</h2>
                    <p>{movie.synopsis}</p>
                </div>
            ))}
        </div>
    )
}

export default Movies;