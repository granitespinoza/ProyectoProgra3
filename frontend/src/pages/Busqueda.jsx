import React, { useState, useEffect } from 'react';
import { get_movies_tag, get_movies_tittle, liked_movie, watch_later } from '../api/api.js';

const BusquedaTag = () => {
    const [searchTag, setSearchTag] = useState('');
    const [searchTitle, setSearchTitle] = useState('');
    const [movies, setMovies] = useState([]);
    const [page, setPage] = useState(1);
    const [showFullSynopsis, setShowFullSynopsis] = useState({});
    const [isLoading, setIsLoading] = useState(false);
    const [searchType, setSearchType] = useState(null); // null, 'tag' or 'title'
    const [resultsCount, setResultsCount] = useState(0); // Número de resultados encontrados

    const fetchMoviesByTag = async (tag) => {
        setIsLoading(true);
        try {
            const movies = await get_movies_tag(tag);
            setMovies(movies);
            setResultsCount(movies.length); // Actualiza el número de resultados
            setPage(1); // Reset to the first page whenever a new search is made
        } catch (error) {
            console.error(error);
        } finally {
            setIsLoading(false);
        }
    };

    const fetchMoviesByTitle = async (title) => {
        setIsLoading(true);
        try {
            const movies = await get_movies_tittle(title);
            setMovies(movies);
            setResultsCount(movies.length); // Actualiza el número de resultados
            setPage(1); // Reset to the first page whenever a new search is made
        } catch (error) {
            console.error(error);
        } finally {
            setIsLoading(false);
        }
    };

    useEffect(() => {
        if (searchType === 'tag' && searchTag) {
            fetchMoviesByTag(searchTag);
        } else if (searchType === 'title' && searchTitle) {
            fetchMoviesByTitle(searchTitle);
        }
    }, [searchTag, searchTitle, searchType]);

    const handleSearchChange = (e) => {
        if (searchType === 'tag') {
            setSearchTag(e.target.value);
        } else if (searchType === 'title') {
            setSearchTitle(e.target.value);
        }
    };

    const handleSearchSubmit = (e) => {
        e.preventDefault();
        if (searchType === 'tag') {
            fetchMoviesByTag(searchTag);
        } else if (searchType === 'title') {
            fetchMoviesByTitle(searchTitle);
        }
    };

    const toggleSynopsis = (index) => {
        setShowFullSynopsis(prevState => ({ ...prevState, [index]: !prevState[index] }));
    };

    const handleLike = async (movie) => {
        try {
            const response = await liked_movie(movie.id);
            console.log(response); // Log the response for debugging
        } catch (error) {
            console.error(error);
        }
    };

    const handleWatchLater = async (movie) => {
        try {
            const response = await watch_later(movie.id);
            console.log(response); // Log the response for debugging
        } catch (error) {
            console.error(error);
        }
    };

    const moviesPerPage = 20;
    const startIndex = (page - 1) * moviesPerPage;
    const endIndex = startIndex + moviesPerPage;
    const paginatedMovies = movies.slice(startIndex, endIndex);

    const nextPage = () => {
        if (endIndex < movies.length) {
            setPage(page + 1);
        }
    };

    const prevPage = () => {
        if (startIndex > 0) {
            setPage(page - 1);
        }
    };

    return (
        <div className="flex mt-16">
            <div className="w-1/4 p-4">
                <div className="flex flex-col space-y-4">
                    <button
                        onClick={() => setSearchType('tag')}
                        className={`p-2 border rounded ${searchType === 'tag' ? 'bg-blue-500 text-white' : ''}`}
                    >
                        Búsqueda por Tag
                    </button>
                    <button
                        onClick={() => setSearchType('title')}
                        className={`p-2 border rounded ${searchType === 'title' ? 'bg-blue-500 text-white' : ''}`}
                    >
                        Búsqueda por Nombre
                    </button>
                    {searchType && (
                        <form onSubmit={handleSearchSubmit} className="flex flex-col space-y-4">
                            <input
                                type="text"
                                value={searchType === 'tag' ? searchTag : searchTitle}
                                onChange={handleSearchChange}
                                placeholder={`Buscar por ${searchType === 'tag' ? 'tag' : 'nombre'}`}
                                className="w-full p-2 border rounded"
                            />
                            <button type="submit" className="p-2 bg-blue-500 text-white rounded">Buscar</button>
                        </form>
                    )}
                    {searchType && (
                        <p>Se encontraron {resultsCount} películas</p>
                    )}
                </div>
            </div>
            <div className="w-3/4 p-4">
                {isLoading ? (
                    <p>Loading...</p>
                ) : (
                    <div>
                        <div className="grid grid-cols-2 gap-4">
                            {paginatedMovies.map((movie, index) => (
                                <div key={index} className="movie-card border-2 border-gray-200 rounded-lg p-4 mb-4">
                                    <h2 className="text-2xl mb-2">{movie.title}</h2>
                                    <div className="flex flex-wrap mb-2">
                                        {movie.tags.split(',').map((tag, i) => (
                                            <span key={i} className="tag bg-blue-200 text-blue-700 rounded px-2 py-1 mr-2 mb-2">
                                                {tag.trim()}
                                            </span>
                                        ))}
                                    </div>
                                    <p className="text-sm">
                                        {showFullSynopsis[index] ? movie.synopsis : `${movie.synopsis.substring(0, 100)}...`}
                                        <button onClick={() => toggleSynopsis(index)} className="text-blue-500 ml-2">
                                            {showFullSynopsis[index] ? 'Ver menos' : 'Ver más'}
                                        </button>
                                    </p>
                                    <div className="flex mt-2">
                                        <button onClick={() => handleLike(movie)} className="border-2 border-blue-500 text-blue-500 rounded px-4 py-2 mr-2">
                                            Me gusta
                                        </button>
                                        <button onClick={() => handleWatchLater(movie)} className="border-2 border-blue-500 text-blue-500 rounded px-4 py-2">
                                            Ver más tarde
                                        </button>
                                    </div>
                                </div>
                            ))}
                        </div>
                        <div className="flex justify-between mt-4">
                            <button onClick={prevPage} disabled={startIndex === 0} className="px-4 py-2 bg-gray-300 rounded">
                                Anterior
                            </button>
                            <button onClick={nextPage} disabled={endIndex >= movies.length} className="px-4 py-2 bg-gray-300 rounded">
                                Siguiente
                            </button>
                        </div>
                    </div>
                )}
            </div>
        </div>
    );
};

export default BusquedaTag;
