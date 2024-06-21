import axios from "axios";

const BAKEND_URL = 'http://localhost:18080';

export const get_movies = async (movie)=>{
    const res = await axios.post(`${BAKEND_URL}/search`, {
        query: movie
    });
    return res.data.results;
}