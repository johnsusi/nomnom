#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <sqlite3.h>

const GLchar *const vertexShaderSource = R"(#version 140

    in vec2 LVertexPos2D;

    void main()
    {
        gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
    }

)";

const GLchar *const fragmentShaderSource = R"(#version 140

    out vec4 LFragment;

    void main()
    {
        LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );
    }

)";

int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    auto window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    auto gl = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

    SDL_GL_SetSwapInterval(1);

    GLuint gVBO = 0;
    GLuint gIBO = 0;

    auto program = glCreateProgram();
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    glCompileShader(vertexShader);

    glAttachShader(program, vertexShader);

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);

    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    auto gVertexPos2DLocation = glGetAttribLocation(program, "LVertexPos2D");
    glClearColor(0.f, 0.f, 0.f, 1.f);
    GLfloat vertexData[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};

    // IBO data
    GLuint indexData[] = {0, 1, 2, 3};

    // Create VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    // Create IBO
    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

    for (bool gameover = false; !gameover;)
    {
        if (SDL_Event event; SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameover = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    gameover = true;
                    break;
                }
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glEnableVertexAttribArray(gVertexPos2DLocation);

        glBindBuffer(GL_ARRAY_BUFFER, gVBO);
        glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

        glDisableVertexAttribArray(gVertexPos2DLocation);

        glUseProgram(0);

        SDL_GL_SwapWindow(window);
    }

    glDeleteProgram(program);

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
