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
    Shader cube_vertex_shader(readAllText(filesys::getPathFromRoot("shaders/light1.vert")), GL_VERTEX_SHADER);
    Shader lamp_vertex_shader(readAllText(filesys::getPathFromRoot("shaders/light1lamp.vert")), GL_VERTEX_SHADER);
    Shader cube_fragment_shader(readAllText(filesys::getPathFromRoot("shaders/light1.frag")), GL_FRAGMENT_SHADER);
    Shader lamp_fragment_shader(readAllText(filesys::getPathFromRoot("shaders/light1lamp.frag")), GL_FRAGMENT_SHADER);
    ShaderProgram cube_shader_program;
    cube_shader_program.attachShader(cube_vertex_shader);
    cube_shader_program.attachShader(cube_fragment_shader);
    cube_shader_program.link();

    ShaderProgram lamp_shader_program;
    lamp_shader_program.attachShader(lamp_vertex_shader);
    lamp_shader_program.attachShader(lamp_fragment_shader);
    lamp_shader_program.link();

    UniformVariable u_objectColor(cube_shader_program, "objectColor");
    UniformVariable u_lightColor(cube_shader_program, "lightColor");
    UniformVariable u_ambient_strength(cube_shader_program, "ambient_strength");
    UniformVariable u_specular_strength(cube_shader_program, "specular_strength");
    UniformVariable u_specular_shine(cube_shader_program, "specular_shine");
    UniformVariable u_light_position(cube_shader_program, "light_position");
    UniformVariable u_projection(cube_shader_program, "projection");
    UniformVariable u_view(cube_shader_program, "view");
    UniformVariable u_model(cube_shader_program, "model");
    UniformVariable u_normal_matrix(cube_shader_program, "normal_matrix");
    UniformVariable u_view_position(cube_shader_program, "view_position");

    UniformVariable u_lightColor_lamp(lamp_shader_program, "lightColor");
    UniformVariable u_projection_lamp(lamp_shader_program, "projection");
    UniformVariable u_view_lamp(lamp_shader_program, "view");
    UniformVariable u_model_lamp(lamp_shader_program, "model");


    // need two versions?
    VertexAttributeLocation a_inPos(cube_shader_program, "inPos");
    VertexAttributeLocation a_inNormal(cube_shader_program, "inNormal");
    VertexAttributeLocation a_inPos_lamp(lamp_shader_program, "inPos");



    VertexBufferObject VBO(sizeof(cube_verticies_normals), cube_verticies_normals, GL_STATIC_DRAW);
    VertexAttributeObject cube_VAO;
    cube_VAO.setVertexBufferObject(VBO);
    cube_VAO.setAttributeData(a_inPos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    cube_VAO.setAttributeData(a_inNormal, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3* sizeof(float));

    VertexAttributeObject lamp_VAO;
    lamp_VAO.setVertexBufferObject(VBO);
    lamp_VAO.setAttributeData(a_inPos_lamp, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    auto lamp_color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lamp_base_position(0.0f, 1.0f, 2.0f);
    glm::vec3 lamp_position(lamp_base_position);

    cube_shader_program.use();
    cube_shader_program.setUniform(u_objectColor, glm::vec3(1.0f, 0.5f, 0.31f));
    cube_shader_program.setUniform(u_lightColor, lamp_color);
    cube_shader_program.setUniform(u_ambient_strength, 0.1f);
    cube_shader_program.setUniform(u_specular_strength, 0.5f);
    cube_shader_program.setUniform(u_specular_shine, 32);
    cube_shader_program.setUniform(u_light_position, lamp_position);

    lamp_shader_program.use();
    lamp_shader_program.setUniform(u_lightColor_lamp, lamp_color);

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
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        cube_shader_program.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(camera.getZoomRad(),
                                                (float) SCR_WIDTH /
                                                (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glm::mat4 cube_model = glm::mat4(1.0f);

        glm::mat3 normal_matrix = glm::mat3(glm::transpose(glm::inverse(view * cube_model)));
        float time_move_val = currentFrame/4;
        lamp_position = lamp_base_position + glm::vec3(cosf(time_move_val), sinf(time_move_val), 0);
        cube_shader_program.use();
        cube_shader_program.setUniform(u_projection, projection);
        cube_shader_program.setUniform(u_view, view);
        cube_shader_program.setUniform(u_model, cube_model);
        cube_shader_program.setUniform(u_light_position, lamp_position);
        cube_shader_program.setUniform(u_view_position, camera.getPosition());
        cube_shader_program.setUniform(u_normal_matrix, normal_matrix);
        cube_VAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 lamp_model = glm::mat4(1.0f);
        lamp_model = glm::translate(lamp_model, lamp_position);
        lamp_model = glm::scale(lamp_model, glm::vec3(0.2f));
        lamp_shader_program.use();
        lamp_shader_program.setUniform(u_projection_lamp, projection);
        lamp_shader_program.setUniform(u_view_lamp, view);
        lamp_shader_program.setUniform(u_model_lamp, lamp_model);
        lamp_VAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

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