import { useState, useEffect } from "react";
import { get_movies_recommendations_tag, get_movies_recommendations_tittle } from "../api/api.js";
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faArrowRight, faArrowLeft } from '@fortawesome/free-solid-svg-icons'



const Home = () => {
    const [recommendedMoviesTag, setRecommendedMoviesTag] = useState([]);
    const [recommendedMoviesTitle, setRecommendedMoviesTitle] = useState([]);
    const [startIndexTag, setStartIndexTag] = useState(0);
    const [startIndexTitle, setStartIndexTitle] = useState(0);
    const [showFullSynopsis, setShowFullSynopsis] = useState({});
    const [isTransitioning, setIsTransitioning] = useState(false);
    const [isTransitioningTitle, setIsTransitioningTitle] = useState(false);

    useEffect(() => {
        const fetchRecommendedMovies = async () => {
            try {
                const moviesTag = await get_movies_recommendations_tag();
                setRecommendedMoviesTag(moviesTag);
                const moviesTitle = await get_movies_recommendations_tittle();
                setRecommendedMoviesTitle(moviesTitle);
            } catch (error) {
                console.error(error);
            }
        }

        fetchRecommendedMovies();
    }, []);

    const nextMoviesTag = () => {
        setIsTransitioning(true);
        setTimeout(() => {
            if (startIndexTag >= recommendedMoviesTag.length - 2) {
                setStartIndexTag(0); // Vuelve al principio si se llega al final
            } else {
                setStartIndexTag(prevIndex => prevIndex + 2);
            }
            setIsTransitioning(false);
        }, 500);
    }

    const beforeMoviesTag = () => {
        setIsTransitioning(true);
        setTimeout(() => {
            if (startIndexTag === 0) {
                setStartIndexTag(recommendedMoviesTag.length - 2); // Vuelve al final si se llega al principio
            } else {
                setStartIndexTag(prevIndex => prevIndex - 2);
            }
            setIsTransitioning(false);
        }, 500);
    }

    const nextMoviesTitle = () => {
        setIsTransitioningTitle(true);
        setTimeout(() => {
            if (startIndexTitle >= recommendedMoviesTitle.length - 2) {
                setStartIndexTitle(0); // Vuelve al principio si se llega al final
            } else {
                setStartIndexTitle(prevIndex => prevIndex + 2);
            }
            setIsTransitioningTitle(false);
        }, 500);
    }

    const beforeMoviesTitle = () => {
        setIsTransitioningTitle(true);
        setTimeout(() => {
            if (startIndexTitle === 0) {
                setStartIndexTitle(recommendedMoviesTitle.length - 2); // Vuelve al final si se llega al principio
            } else {
                setStartIndexTitle(prevIndex => prevIndex - 2);
            }
            setIsTransitioningTitle(false);
        }, 500);
    }

    const toggleSynopsis = (index) => {
        setShowFullSynopsis(prevState => ({...prevState, [index]: !prevState[index]}));
    }

    return (
    <div className="flex flex-col items-start mt-16 ml-2">
        <h1 className="text-3xl mb-4">Recomendacion por tags</h1>
        <div className="flex flex-row">
            <button onClick={beforeMoviesTag} className="h-20 mt-16">
                <FontAwesomeIcon icon={faArrowLeft} />
            </button>
            {recommendedMoviesTag.slice(startIndexTag, startIndexTag + 2).map((movie, index) => (
                <div key={index}
                     className={`movie-card border-2 border-gray-200 rounded-lg p-4 mb-4 mr-2 ml-2 w-11/12 justify-between transition-opacity duration-500 ${isTransitioning ? 'opacity-0' : 'opacity-100'}`}>
                    <h2>{movie.title}</h2>
                    <div className="flex flex-wrap mb-2">
                        {movie.tags.split(',').map((tag, i) => (
                            <span key={i}
                                  className="tag bg-blue-200 text-blue-700 rounded px-2 py-1 mr-2 mb-2">{tag.trim()}</span>
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
            <button onClick={nextMoviesTag} className="h-20 mt-16">
                <FontAwesomeIcon icon={faArrowRight}/>
            </button>
        </div>
        <hr className="w-full my-4"/>
        <h1 className="text-3xl mb-4">Recomendacion por titulo</h1>
        <div className="flex flex-row">
            <button onClick={beforeMoviesTitle} className="h-20 mt-16">
                <FontAwesomeIcon icon={faArrowLeft} />
            </button>
            {recommendedMoviesTitle.slice(startIndexTitle, startIndexTitle + 2).map((movie, index) => (
                <div key={index}
                     className={`movie-card border-2 border-gray-200 rounded-lg p-4 mb-4 mr-2 ml-2 w-11/12 justify-between transition-opacity duration-500 ${isTransitioningTitle ? 'opacity-0' : 'opacity-100'}`}>
                    <h2>{movie.title}</h2>
                    <div className="flex flex-wrap mb-2">
                        {movie.tags.split(',').map((tag, i) => (
                            <span key={i}
                                  className="tag bg-blue-200 text-blue-700 rounded px-2 py-1 mr-2 mb-2">{tag.trim()}</span>
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
            <button onClick={nextMoviesTitle} className="h-20 mt-16">
                <FontAwesomeIcon icon={faArrowRight}/>
            </button>
        </div>

    </div>
    )
}

export default Home;