
import Home from './pages/Home'

import './App.css'
import NavBar from "./pages/NavBar.jsx";
import {BrowserRouter as Router, Route, Routes} from 'react-router-dom'
import Favoritos from "./pages/Favoritos.jsx";
import VerDespues from "./pages/VerDespues.jsx";
import Movies from "./pages/Movies.jsx";

function App() {



  return (
      <Router>
        <NavBar />
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/movies" element={<Movies />} />
          <Route path="/favoritos" element={<Favoritos />} />
          <Route path="/ver_despues" element={<VerDespues />} />
        </Routes>
      </Router>

  )
}

export default App
