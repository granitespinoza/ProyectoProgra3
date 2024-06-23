import axios from "axios";

const BAKEND_URL = 'http://localhost:18080';

export const get_movies_tittle = async (movie)=>{
    const res = await axios.post(`${BAKEND_URL}/search`, {
        query: movie
    });
    return res.data.results;
}

export const get_movies_tag = async (tag)=>{
    const res = await axios.post(`${BAKEND_URL}/tag/${tag}`);
    return res.data.results;
}

export const get_movies_by_page = async (page,sizepage)=> {
    const res = await axios.get(`${BAKEND_URL}/movies/${page}/${sizepage}`);
    return res.data.movies;
}

export const liked_movie = async (id) => {
    const res = await axios.post(`${BAKEND_URL}/like`, {
        id_movie: id
    });
    return res.data;
}

export const get_favorites = async () => {
    const res = await axios.get(`${BAKEND_URL}/get_movies_liked`);
    return res.data.movies;
}

export const watch_later = async (id) => {
    const res = await axios.post(`${BAKEND_URL}/watchlater`, {
        id_movie: id
    });
    return res.data;
}

export const get_watch_later = async () => {
    const res = await axios.get(`${BAKEND_URL}/get_WatchLater`);
    return res.data.movies;
}

export const get_movies_recommendations_tag = async () => {
    const res = await axios.get(`${BAKEND_URL}/recommended_by_tag`);
    return res.data.movies;
}
