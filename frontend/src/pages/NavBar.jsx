
import {Link} from "react-router-dom";

const NavBar = () => {

    return (
        <nav>
            <ul>
                <li>
                    <Link to="/">Home</Link>
                </li>
                <li>
                    <Link to="/movies">Movies</Link>
                </li>
                <li>
                    <Link to="/favoritos">Favoritos</Link>
                </li>
                <li>
                    <Link to="/ver_despues">Ver mas tarde</Link>
                </li>
            </ul>
        </nav>
    )
}

export default NavBar;