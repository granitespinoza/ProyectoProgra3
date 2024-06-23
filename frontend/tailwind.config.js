/** @type {import('tailwindcss').Config} */
export default {
  content: ["./indes.html",
    "./src/**/*.{js,jsx,ts,tsx}"],
  theme: {
    extend: {
      transitionProperty: {
        'height': 'height',
        'spacing': 'margin, padding',
        'scale': 'transform',
      }
    },
    plugins: [],
  }
}

