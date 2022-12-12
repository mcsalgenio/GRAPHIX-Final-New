#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <string> 
#include <iostream>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

#include "Model.h"
#include "Shader.h"
#include "PerspectiveCamera.h"
#include "OrthoCamera.h"
#include "Light.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float window_height = 1000.0f;
    float window_width = 1000.0f;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, "Final Project", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    Model mainShip = Model("3D/Ship.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 173.0f); //Initialize main obj
    Model enemyShipOne = Model("3D/Ship.obj", glm::vec3(3.0f, 3.0f, 5.0f), glm::vec3(0.5f, 0.5f, 0.5f), 95.0f); //Initialize enemy ships
    Model enemyShipTwo = Model("3D/Ship.obj", glm::vec3(-15.0f, -10.0f, -20.0f), glm::vec3(0.5f, 0.5f, 0.5f), 20.0f);
    Model enemyShipThree = Model("3D/Ship.obj", glm::vec3(-5.0f, 7.0f, 35.0f), glm::vec3(0.5f, 0.5f, 0.5f), 273.0f); 
    Model enemyShipFour = Model("3D/Ship.obj", glm::vec3(10.0f, -9.0f, 13.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f); 
    Model enemyShipFive = Model("3D/Ship.obj", glm::vec3(7.0f, 10.0f, -27.0f), glm::vec3(0.5f, 0.5f, 0.5f), 45.0f); 
    Model enemyShipSix = Model("3D/Ship.obj", glm::vec3(-7.5f, -3.0f, -2.0f), glm::vec3(0.5f, 0.5f, 0.5f), 182.0f); 

    stbi_set_flip_vertically_on_load(true); 

    //Load main ship texture
    int img_width, img_height, color_channels;
    unsigned char* texture_bytes = stbi_load("3D/Blue_Ship.png", &img_width, &img_height, &color_channels, 0); 
    GLuint texture; 
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGB,
        img_width,
        img_height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        texture_bytes
    );

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture_bytes);
    glEnable(GL_DEPTH_TEST);

    //Load main ship normal map
    unsigned char* norm_bytes = stbi_load("3D/Blue_Normal.png", &img_width, &img_height, &color_channels, 0);
    GLuint norm_tex;
    glGenTextures(1, &norm_tex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, norm_tex);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        img_width,
        img_height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        norm_bytes
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(norm_bytes);

    //Red ship textures
    texture_bytes = stbi_load("3D/Red_Ship.png", &img_width, &img_height, &color_channels, 0);
    GLuint enemy_one_texture;
    glGenTextures(1, &enemy_one_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, enemy_one_texture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        img_width,
        img_height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        texture_bytes
    );

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture_bytes);

    norm_bytes = stbi_load("3D/Red_Normal.png", &img_width, &img_height, &color_channels, 0);
    GLuint enemy_one_norm_tex;
    glGenTextures(1, &enemy_one_norm_tex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, enemy_one_norm_tex);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        img_width,
        img_height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        norm_bytes
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(norm_bytes);

    //Green ship textures
    texture_bytes = stbi_load("3D/Green_Ship.png", &img_width, &img_height, &color_channels, 0);
    GLuint enemy_two_texture;
    glGenTextures(1, &enemy_two_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, enemy_two_texture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        img_width,
        img_height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        texture_bytes
    );

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture_bytes);

    norm_bytes = stbi_load("3D/Green_Normal.png", &img_width, &img_height, &color_channels, 0);
    GLuint enemy_two_norm_tex;
    glGenTextures(1, &enemy_two_norm_tex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, enemy_two_norm_tex);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        img_width,
        img_height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        norm_bytes
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(norm_bytes);

    /*Modifies screen space*/
    glViewport(0, 0, window_width, window_height); 

    //Create shaders
    Shader mainShader = Shader("Shaders/vshade.vert", "Shaders/fshade.frag"); //for objects
    Shader skyboxShader = Shader("Shaders/skybox.vert", "Shaders/skybox.frag"); //for skybox

    //Prepare skybox
    float skyboxVertices[]{
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };

    unsigned int skyboxIndices[]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    std::string facesSkybox[]{
        "Skybox/uw_rt.jpg",
        "Skybox/uw_lf.jpg", 
        "Skybox/uw_up.jpg", 
        "Skybox/uw_dn.jpg", 
        "Skybox/uw_bk.jpg", 
        "Skybox/uw_ft.jpg"  
    };
    
    unsigned int skyboxTex;
    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyCChannel;
        stbi_set_flip_vertically_on_load(false);
        unsigned char* data = stbi_load(facesSkybox[i].c_str(), &w, &h, &skyCChannel, 0);
        
        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                w, 
                h, 
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
    }

    //Reenable flip
    stbi_set_flip_vertically_on_load(true);

    //Cameras
    PerspectiveCamera perspective = PerspectiveCamera(90.f, window_height, window_width, 0.1f, 50.f);
    OrthoCamera orthographic = OrthoCamera(-35.0f, 35.0f, -35.0f, 35.0f, -50.0f, 50.0f, glm::vec3(0.0f, 15.0f, 10.0f));

    //for camera movement
    float pers_x, pers_y, pers_z, ortho_x, ortho_y, ortho_z;
    pers_x = pers_y = pers_z = ortho_x = ortho_y = ortho_z = 0.0f;
    
    bool camType = true; //for camera changing

    //for ship movement
    float x_pos, y_pos, z_pos;
    x_pos = y_pos = z_pos = 0.0f;

    Light dLight = Light(glm::vec3(0.f, -1.0f, 0.f));
    glm::vec3 ptLightColor = glm::vec3(3.f, 3.f, 3.f);

    std::cout << y_pos << "\n";

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        //Set blending function
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Source Factor, Destination Factor
        glBlendEquation(GL_ADD);

        /*-----------SKYBOX-----------*/
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShader.getShader());

        glm::mat4 sky_view = glm::mat4(1.f);
        
        //adjust skybox view depending on camera type
        if (camType)
            sky_view = glm::mat4(glm::mat3(perspective.getViewMatrix()));
        else
            sky_view = glm::mat4(glm::mat3(orthographic.getViewMatrix()));

        unsigned int skyboxViewLoc = glGetUniformLocation(skyboxShader.getShader(), "view");
        glUniformMatrix4fv(skyboxViewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));

        unsigned int skyboxProjLoc = glGetUniformLocation(skyboxShader.getShader(), "projection");
        glUniformMatrix4fv(skyboxProjLoc, 1, GL_FALSE, glm::value_ptr(perspective.getProjPerspective()));

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        /*-----------SKYBOX-----------*/

        /*-----------DRAW-----------*/
        glUseProgram(mainShader.getShader());

        //Apply lighting
        unsigned int lightPosLoc = glGetUniformLocation(mainShader.getShader(), "lightPos"); //Directional
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(dLight.getLightPos()));
        unsigned int ptLightPosLoc = glGetUniformLocation(mainShader.getShader(), "ptLightPos"); //Point
        glUniform3fv(ptLightPosLoc, 1, glm::value_ptr(glm::vec3(x_pos, y_pos, z_pos - 1.0f))); //move depending on main ship placement
        unsigned int lightColorLoc = glGetUniformLocation(mainShader.getShader(), "lightColor");
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(dLight.getLightColor()));
        unsigned int ptLightColorLoc = glGetUniformLocation(mainShader.getShader(), "ptLightColor");
        glUniform3fv(ptLightColorLoc, 1, glm::value_ptr(ptLightColor));

        unsigned int ambientStrLoc = glGetUniformLocation(mainShader.getShader(), "ambientStr");
        glUniform1f(ambientStrLoc, dLight.getAmbientStr());
        unsigned int ambientColorLoc = glGetUniformLocation(mainShader.getShader(), "ambientColor");
        glUniform3fv(ambientColorLoc, 1, glm::value_ptr(dLight.getAmbientColor()));

        unsigned int cameraPosLoc = glGetUniformLocation(mainShader.getShader(), "cameraPos");
        glUniform3fv(cameraPosLoc, 1, glm::value_ptr(perspective.getCamPos()));
        unsigned int specStrLoc = glGetUniformLocation(mainShader.getShader(), "specStr");
        glUniform1f(specStrLoc, dLight.getSpecStr());
        unsigned int specPhongLoc = glGetUniformLocation(mainShader.getShader(), "specPhong");
        glUniform1f(specPhongLoc, dLight.getSpecPhong());

        //Switch camera types; 1 / true = perspective, 2 / false = orthographic
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            camType = true;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            camType = false;
        }
        if (camType) {
            //Main Ship Movement + Perspective Cam Movement
            //W/S Forward/Back == translation on Z-Axis
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                z_pos -= 0.01f;
                pers_z -= 0.01f;
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                z_pos += 0.01f;
                pers_z += 0.01f;
            }
                
            //A/D Move Left/Right == translation on X-Axis || TODO: Change to rotation
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                x_pos -= 0.01f;
                pers_x -= 0.01f;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                x_pos += 0.01f;
                pers_x += 0.01f;
            }

            //Q/E Ascend/Descend == translation on Y-Axis
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                y_pos += 0.01f;
                pers_y += 0.01f;
                std::cout << y_pos << "\n";
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                y_pos -= 0.01f;
                pers_y -= 0.01f;
                std::cout << y_pos << "\n";
            }

            perspective.updateViewMatrix(pers_x, pers_y, pers_z);

            //Reset values to prevent cont. translation in one direction bc of loop design
            pers_x = 0;
            pers_y = 0;
            pers_z = 0;

            unsigned int projLoc = glGetUniformLocation(mainShader.getShader(), "projection");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(perspective.getProjPerspective()));
            unsigned int viewLoc = glGetUniformLocation(mainShader.getShader(), "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(perspective.getViewMatrix()));
        }
        else {
            //Orthographic Camera Movement
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                ortho_x -= 0.01f;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                ortho_x += 0.01f;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                ortho_z -= 0.01f;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                ortho_z += 0.01f;

            orthographic.updateViewMatrix(ortho_x, ortho_y, ortho_z);

            //Reset values to prevent cont. translation in one direction bc of loop design
            ortho_z = 0;
            ortho_x = 0;

            unsigned int projLoc = glGetUniformLocation(mainShader.getShader(), "projection");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(orthographic.getProjOrtho()));
            unsigned int viewLoc = glGetUniformLocation(mainShader.getShader(), "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(orthographic.getViewMatrix()));
        }

        mainShip.draw(glm::vec3(x_pos, y_pos, z_pos), mainShader.getShader(), texture, norm_tex); //controlled ship, can change pos
        enemyShipOne.draw(mainShader.getShader(), enemy_one_texture, enemy_one_norm_tex); //enemy ships, stationary
        enemyShipTwo.draw(mainShader.getShader(), enemy_one_texture, enemy_one_norm_tex);
        enemyShipThree.draw(mainShader.getShader(), enemy_one_texture, enemy_one_norm_tex);
        enemyShipFour.draw(mainShader.getShader(), enemy_two_texture, enemy_two_norm_tex); //enemy ships, stationary
        enemyShipFive.draw(mainShader.getShader(), enemy_two_texture, enemy_two_norm_tex);
        enemyShipSix.draw(mainShader.getShader(), enemy_two_texture, enemy_two_norm_tex);

        /*-----------DRAW-----------*/

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    mainShip.deleteBuffers();
    enemyShipOne.deleteBuffers();
    enemyShipTwo.deleteBuffers();
    enemyShipThree.deleteBuffers();
    enemyShipFour.deleteBuffers();
    enemyShipFive.deleteBuffers();
    enemyShipSix.deleteBuffers();

    glfwTerminate();
    return 0;
}