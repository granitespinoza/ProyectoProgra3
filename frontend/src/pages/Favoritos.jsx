import { useState, useEffect, useRef } from "react";
import { get_favorites, remove_liked_movie, undo, update_history } from "../api/api.js";

const Favoritos = () => {
    const [favoritos, setfavoritos] = useState([]);
    const [showFullSynopsis, setShowFullSynopsis] = useState({});
    const [showUndo, setShowUndo] = useState(false);
    const undoTimeoutRef = useRef(null);

    useEffect(() => {
        const fetchFavorite_movies = async () => {
            try {
                const movies = await get_favorites();
                setfavoritos(movies);
            } catch (error) {
                console.error(error);
            }
        };

        fetchFavorite_movies();
    }, []);

    const toggleSynopsis = (index) => {
        setShowFullSynopsis(prevState => ({...prevState, [index]: !prevState[index]}));
    };

    const handleRemove = async (movieId) => {
        try {
            await remove_liked_movie(movieId);
            setfavoritos(favoritos.filter(m => m.id !== movieId));
            setShowUndo(true);

            undoTimeoutRef.current = setTimeout(async () => {
                setShowUndo(false);
                await update_history();
                undoTimeoutRef.current = null;
            }, 5000);
        } catch (error) {
            console.error(error);
        }
    };

    const handleUndo = async () => {
        try {
            if (undoTimeoutRef.current) {
                clearTimeout(undoTimeoutRef.current);
                undoTimeoutRef.current = null;
            }
            await undo();
            const movies = await get_favorites();
            setfavoritos(movies);
            setShowUndo(false);
        } catch (error) {
            console.error(error);
        }
    };

    return (
        <div className="flex flex-col items-start mt-16 ml-2">
            <h1 className="text-3xl mb-4">Favoritos</h1>
            {favoritos.map((movie, index) => (
                <div key={index} className="border-2 border-gray-200 rounded-lg p-4 mb-4 w-11/12">
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
                        <button onClick={() => handleRemove(movie.id)} className="border-2 border-blue-500 text-blue-500 rounded px-4 py-2">
                            Eliminar de Ver Despues
                        </button>
                    </div>
                </div>
            ))}
            {showUndo && (
                <div className="fixed bottom-0 left-0 right-0 bg-gray-100 p-4 text-center shadow-lg">
                    <button onClick={handleUndo} className="text-blue-500">Deshacer</button>
                </div>
            )}
        </div>
    );
}

export default Favoritos;



