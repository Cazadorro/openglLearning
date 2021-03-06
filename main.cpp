#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "glutil.h"
#include "glfwutil.h"

#include <iostream>

void framebuffer_size_callback(glfwutil::Window &window, int width, int height);

void mouse_callback(glfwutil::Window &window, double xpos, double ypos, Camera &camera);

void scroll_callback(glfwutil::Window &window, double xoffset, double yoffset, Camera &camera);

void processInput(glfwutil::Window &window, Camera &camera, float deltaTime);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main() {
    // glfw: initialize and configure
    // ------------------------------

    glfwutil::initWindowManager(3, 3, true);

    glfwutil::Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");

    // timing

    Camera camera(2.5f, 0.1f, 45.0f, glm::vec3(0.0f, 0.0f, 3.0f));

    auto f_mouse_callback = [&](glfwutil::Window &window, double xoffset, double yoffset) {
        return mouse_callback(window, xoffset, yoffset, camera);
    };

    auto f_scroll_callback = [&](glfwutil::Window &window, double xoffset, double yoffset) {
        return scroll_callback(window, xoffset, yoffset, camera);
    };

    window.makeCurrentContext();
    window.setFrameBufferCallback(framebuffer_size_callback);
    window.setMouseCallback(f_mouse_callback);
    window.setScrollCallback(f_scroll_callback);


    // tell GLFW to capture our mouse
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader vertex_shader(readAllText(filesys::getPathFromRoot("shader.vert")), GL_VERTEX_SHADER);
    Shader fragment_shader(readAllText(filesys::getPathFromRoot("shader.frag")), GL_FRAGMENT_SHADER);
    ShaderProgram shader_program;
    shader_program.attachShader(vertex_shader);
    shader_program.attachShader(fragment_shader);
    shader_program.link();

    UniformVariable u_texture0(shader_program, "texture0");
    UniformVariable u_texture1(shader_program, "texture1");
    UniformVariable u_projection(shader_program, "projection");
    UniformVariable u_view(shader_program, "view");
    UniformVariable u_model(shader_program, "model");

    VertexAttributeLocation a_inPos(shader_program, "inPos");
    VertexAttributeLocation a_inTexCoord(shader_program, "inTexCoord");

    Image container_image(filesys::getPathFromRoot("resources/textures/container.png"));
    Image awesomeface_image(filesys::getPathFromRoot("resources/textures/awesomeface.png"));

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    VertexBufferObject VBO(sizeof(cube_verticies), cube_verticies, GL_STATIC_DRAW);
    VertexAttributeObject VAO;
    VAO.setVertexBufferObject(VBO);
    VAO.setAttributeData(a_inPos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    VAO.setAttributeData(a_inTexCoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float));

    Texture2D texture0;
    texture0.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture0.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture0.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture0.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture0.setImage(container_image, GL_RGB);
    texture0.generateMipmap();

    Texture2D texture1;
    texture1.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture1.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture1.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture1.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture1.setImage(awesomeface_image, GL_RGBA);
    texture1.generateMipmap();

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shader_program.use();
    shader_program.setUniform(u_texture0, 0);
    shader_program.setUniform(u_texture1, 1);

    // render loop
    // -----------
    float lastFrame = 0.0f;
    while (!window.shouldClose()) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window, camera, deltaTime);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        texture0.use(GL_TEXTURE0);
        texture1.use(GL_TEXTURE1);

        // activate shader
        shader_program.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()),
                                                (float) SCR_WIDTH /
                                                (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        shader_program.setUniform(u_projection, projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shader_program.setUniform(u_view, view);

        // render boxes
        VAO.bind();
        for (unsigned int i = 0; i < 10; i++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;

            model = glm::rotate(model, glm::radians(angle),
                                glm::vec3(1.0f, 0.3f, 0.5f));
            shader_program.setUniform(u_model, model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(glfwutil::Window &window, Camera &camera, float deltaTime) {
    if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window.setShouldClose(true);
    }

    if (window.getKey(GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (window.getKey(GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (window.getKey(GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (window.getKey(GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(glfwutil::Window &window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(glfwutil::Window &window, double xpos, double ypos, Camera &camera) {
    static double lastX = SCR_WIDTH / 2.0f;
    static double lastY = SCR_HEIGHT / 2.0f;
    static bool firstMouse = true;
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    // reversed since y-coordinates go from bottom to top
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(glfwutil::Window &window, double xoffset, double yoffset, Camera &camera) {
    camera.ProcessMouseScroll(yoffset);
}