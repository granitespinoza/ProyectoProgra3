import { useState, useEffect } from "react";
import { get_favorites } from "../api/api.js";
import {remove_liked_movie} from "../api/api.js";

const Favoritos = () => {
    const [favorites, setFavorites] = useState([]);
    const [showFullSynopsis, setShowFullSynopsis] = useState({})

    useEffect(() => {
        const fetchFavorites = async () => {
            try {
                const movies = await get_favorites();
                setFavorites(movies);
                console.log(movies);
            } catch (error) {
                console.error(error);
            }
        }

        fetchFavorites();
    }, []);

    const toggleSynopsis = (index) => {
        setShowFullSynopsis(prevState => ({...prevState, [index]: !prevState[index]}));
    }

    const handleRemove = async (movie) => {
    try {
        const response = await remove_liked_movie(movie.id);
        console.log(response); // Log the response for debugging
        // Remove the movie from the state
        setFavorites(favorites.filter(m => m.id !== movie.id));
    } catch (error) {
        console.error(error);
    }

}

    return (
        <div className="flex flex-col items-start mt-16 ml-2">
            <h1 className="text-3xl mb-4">Favoritos</h1>
            {favorites.map((movie, index) => (
                <div key={index} className="border-2 border-gray-200 rounded-lg p-4 mb-4  w-11/12 ">
                    <h2 className="text-2xl mb-2">{movie.title}</h2>
                    <div className="flex flex-wrap mb-2">
                        {movie.tags.split(',').map((tag, i) => (
                            <span key={i} className="tag bg-blue-200 text-blue-700 rounded px-2 py-1 mr-2 mb-2">{tag.trim()}</span>
                        ))}
                    </div>
                    <p className="text-sm">
                        {showFullSynopsis[index] ? movie.synopsis : `${movie.synopsis.substring(0, 300)}...`}
                        <button onClick={() => toggleSynopsis(index)} className="text-blue-500 ml-2">
                            {showFullSynopsis[index] ? 'Ver menos' : 'Ver más'}
                        </button>
                    </p>
                    <div className="flex mt-2">
                        <button onClick={() => handleRemove(movie)} className="border-2 border-blue-500 text-blue-500 rounded px-4 py-2">
                            Eliminar de favoritos
                        </button>
                    </div>
                </div>
            ))}
        </div>
    )
}

export default Favoritos;