#version 100

uniform sampler2D state;  // Board state
uniform vec2 scale;       // Scale of the game


/*
 * @brief: Get neighbor cell at (x, y) from current one
 *
 * @param x: Coordinates on x-axis from current cell
 * @param x: Coordinates on y-axis from current cell
 *
 * @return: Pixel RED value
 */

float get(int x, int y)
{
    return texture2D(state, (gl_FragCoord.xy + vec2(x, y)) / scale).r;
}

void main()
{
    int neighbors = 0;

    // Count number of neighbor cells
    neighbors += int(get(-1, -1));
    neighbors += int(get(-1,  0));
    neighbors += int(get(-1,  1));
    neighbors += int(get( 0, -1));
    neighbors += int(get( 0,  1));
    neighbors += int(get( 1, -1));
    neighbors += int(get( 1,  0));
    neighbors += int(get( 1,  1));

    // Apply game-of-life rules
    if (neighbors == 3)
    {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    if (neighbors == 2)
    {
        gl_FragColor = vec4(get(0, 0), get(0, 0), get(0, 0), 1.0);
    }
    else
    {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}