import {Link} from "react-router-dom";
import Lottie from "react-lottie";
import animation_1 from "../animations/animation_1.json";
import animation_2 from "../animations/animation_2.json";
import animation_3 from "../animations/animation_3.json";
import animation_4 from "../animations/animation_4.json";
import animation_5 from "../animations/animation_5.json"; // Importa la nueva animación

const defaultOptions = {
    loop: true,
    autoplay: true,
    animationData: animation_1,
    rendererSettings: {
        preserveAspectRatio: "xMidYMid slice"
    }
}

const defaultOptions2 = {
    loop: true,
    autoplay: true,
    animationData: animation_2,
    rendererSettings: {
        preserveAspectRatio: "xMidYMid slice"
    }
}

const defaultOptions3 = {
    loop: true,
    autoplay: true,
    animationData: animation_3,
    rendererSettings: {
        preserveAspectRatio: "xMidYMid slice"
    }
}

const defaultOptions4 = {
    loop: true,
    autoplay: true,
    animationData: animation_4,
    rendererSettings: {
        preserveAspectRatio: "xMidYMid slice"
    }
}

const defaultOptions5 = { // Define las opciones de la nueva animación
    loop: true,
    autoplay: true,
    animationData: animation_5,
    rendererSettings: {
        preserveAspectRatio: "xMidYMid slice"
    }
}


const NavBar = () => {
    return (
        <nav className="fixed top-0 w-full bg-gray-950 h-14">
            <ul className="flex justify-around p-1 mt-1">
                <li className="flex flex-row">
                    <div className="flex mt-0">
                        <Lottie options={defaultOptions2} height={50} width={50} speed={0.5}/>
                    </div>
                        <Link to="/" className="text-neutral-50 text-lg flex mt-3">Inicio</Link>
                </li>
                <li className="flex flex-row">
                    <div className="flex mt-0">
                        <Lottie options={defaultOptions} height={50} width={50}/>
                    </div>
                        <Link to="/movies" className="text-neutral-50 text-lg flex mt-3">Peliculas</Link>
                </li>
                <li className="flex flex-row">
                    <div className="flex mt-0">
                    <Lottie options={defaultOptions4} height={45} width={45} speed={0.5} />
                    </div>
                    <Link to="/favoritos" className="text-neutral-50 text-lg flex mt-3">Favoritos</Link>
                </li>
                <li className="flex flex-row">
                    <div className="flex mt-0">
                        <Lottie options={defaultOptions3} height={46} width={46}/>
                    </div>
                        <Link to="/ver_despues" className="text-neutral-50 text-lg flex mt-3">Ver mas tarde</Link>
                </li>
                <li className="flex flex-row">
                    <div className="flex mt-0">
                        <Lottie options={defaultOptions5} height={46} width={46}/>
                    </div>
                    <Link to="/busqueda" className="text-neutral-50 text-lg flex mt-3">Busqueda</Link>
                </li>
            </ul>
        </nav>
    )
}

export default NavBar;