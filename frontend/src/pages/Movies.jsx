import {useState, useEffect} from "react";
import {get_movies_by_page} from "../api/api.js";

const Movies = () => {
    const [movies, setMovies] = useState([])
    const [page, setPage] = useState(1)
    const [pageSize, setPageSize] = useState(10)
    const [showFullSynopsis, setShowFullSynopsis] = useState({})

    useEffect(() => {
        const fetchMovies = async () => {
            try {
                const response = await get_movies_by_page(page, pageSize);
                setMovies(response);
            } catch (error) {
                console.error(error);
            }
        }

        fetchMovies();
    }, [page, pageSize]);

    const handleNextPage = () => {
        setPage(prevPage => prevPage + 1);
    }

    const handlePrevPage = () => {
        setPage(prevPage => prevPage > 1 ? prevPage - 1 : 1);
    }

    const handlePageSizeChange = (e) => {
        setPageSize(Number(e.target.value));
    }

    const toggleSynopsis = (index) => {
        setShowFullSynopsis(prevState => ({...prevState, [index]: !prevState[index]}));
    }

    return (
        <div className="flex flex-col items-start mt-16 ml-2">
            <h1 className="text-3xl mb-4">Movies</h1>
            {movies.map((movie, index) => (
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
                </div>
            ))}
            <div className="flex flex-row">
            <div className="mb-4 flex ml-96">
                <button onClick={handlePrevPage} className="border-2 border-blue-500 text-blue-500 rounded px-4 py-2 mr-2">Anterior</button>
                <span className="mr-2">Página {page}</span>
                <button onClick={handleNextPage} className="border-2 border-blue-500 text-blue-500 rounded px-4 py-2">Siguiente</button>
            </div>
            <div className="flex ml-2">
                <label className="mr-2">Tamaño de página: </label>
                <select value={pageSize} onChange={handlePageSizeChange} className="border-2 border-gray-200 rounded h-10 ">
                    <option value={10}>10</option>
                    <option value={20}>20</option>
                </select>
            </div>
            </div>
        </div>
    )
}

export default Movies;