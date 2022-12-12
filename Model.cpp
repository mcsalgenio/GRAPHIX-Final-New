#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <string>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

Model::Model(std::string obj_path, glm::vec3 pos, glm::vec3 scl, float rot) {
    position = pos;
    scale = scl;
    theta = rot;
    rotation_x = glm::vec3(1.0f, 0, 0);
    rotation_y = glm::vec3(0, 1.0f, 0);
    rotation_z = glm::vec3(0, 0, 1.0f);

    //Get obj file
    std::string path = obj_path;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, error;
    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &materials,
        &warning,
        &error,
        path.c_str()
    );

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }

    //Get T and B
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    for (int i = 0; i < shapes[0].mesh.indices.size(); i += 3) {
        tinyobj::index_t vData1 = shapes[0].mesh.indices[i];
        tinyobj::index_t vData2 = shapes[0].mesh.indices[i + 1];
        tinyobj::index_t vData3 = shapes[0].mesh.indices[i + 2];

        glm::vec3 v1 = glm::vec3(attributes.vertices[vData1.vertex_index * 3],
            attributes.vertices[vData1.vertex_index * 3 + 1],
            attributes.vertices[vData1.vertex_index * 3 + 2]);
        glm::vec3 v2 = glm::vec3(attributes.vertices[vData2.vertex_index * 3],
            attributes.vertices[vData2.vertex_index * 3 + 1],
            attributes.vertices[vData2.vertex_index * 3 + 2]);
        glm::vec3 v3 = glm::vec3(attributes.vertices[vData3.vertex_index * 3],
            attributes.vertices[vData3.vertex_index * 3 + 1],
            attributes.vertices[vData3.vertex_index * 3 + 2]);

        glm::vec2 uv1 = glm::vec2(attributes.texcoords[vData1.texcoord_index * 2],
            attributes.texcoords[vData1.texcoord_index * 2 + 1]);
        glm::vec2 uv2 = glm::vec2(attributes.texcoords[vData2.texcoord_index * 2],
            attributes.texcoords[vData2.texcoord_index * 2 + 1]);
        glm::vec2 uv3 = glm::vec2(attributes.texcoords[vData3.texcoord_index * 2],
            attributes.texcoords[vData3.texcoord_index * 2 + 1]);

        glm::vec3 deltaPos1 = v2 - v1;
        glm::vec3 deltaPos2 = v3 - v1;
        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        float r = 1.f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));

        glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
    }

    //std::vector<GLfloat> fullVertexData;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3)]
        );

        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3) + 1]
        );

        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3) + 2]
        );

        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3)]
        );
        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3) + 1]
        );
        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3) + 2]
        );

        fullVertexData.push_back(
            attributes.texcoords[(vData.texcoord_index * 2)]
        );

        fullVertexData.push_back(
            attributes.texcoords[(vData.texcoord_index * 2) + 1]
        );

        fullVertexData.push_back(
            tangents[i].x
        );
        fullVertexData.push_back(
            tangents[i].y
        );
        fullVertexData.push_back(
            tangents[i].z
        );

        fullVertexData.push_back(
            bitangents[i].x
        );
        fullVertexData.push_back(
            bitangents[i].y
        );
        fullVertexData.push_back(
            bitangents[i].z
        );
    }

    //GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * fullVertexData.size(),
        fullVertexData.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(GL_FLOAT),
        (void*)0
    );

    GLintptr normPtr = 3 * sizeof(float);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)normPtr
    );

    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)uvPtr
    );

    GLintptr tangentPtr = 8 * sizeof(float);
    glVertexAttribPointer(
        3,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(GL_FLOAT),
        (void*)tangentPtr
    );

    GLintptr bitangentPtr = 11 * sizeof(float);
    glVertexAttribPointer(
        4,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(GL_FLOAT),
        (void*)bitangentPtr
    );

    glEnableVertexAttribArray(0); //Enable pos (XYZ)
    glEnableVertexAttribArray(1); //Enable normals
    glEnableVertexAttribArray(2); //Enable UV/tex coords
    glEnableVertexAttribArray(3); //Enable tangent
    glEnableVertexAttribArray(4); //Enable bitangent

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::draw(GLuint shaderProg, GLuint texture, GLuint norm_tex)
{
    glm::mat4 transformation_matrix = glm::mat4(1.0f);
    transformation_matrix = glm::translate(transformation_matrix, position);
    transformation_matrix = glm::scale(transformation_matrix, scale);
    transformation_matrix = glm::rotate(transformation_matrix, glm::radians(theta), rotation_y);

    unsigned int transformationLoc = glGetUniformLocation(shaderProg, "transform");
    glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));

    //Apply textures
    glActiveTexture(GL_TEXTURE0);
    GLuint tex0Address = glGetUniformLocation(shaderProg, "tex0");
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(tex0Address, 0);

    //Normal map
    glActiveTexture(GL_TEXTURE1);
    GLuint tex1Address = glGetUniformLocation(shaderProg, "norm_tex");
    glBindTexture(GL_TEXTURE_2D, norm_tex);
    glUniform1i(tex1Address, 1);

    glUseProgram(shaderProg);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 14);
}

void Model::draw(glm::vec3 new_pos, GLuint shaderProg, GLuint texture, GLuint norm_tex)
{
    glm::mat4 transformation_matrix = glm::mat4(1.0f);
    transformation_matrix = glm::translate(transformation_matrix, new_pos);
    transformation_matrix = glm::scale(transformation_matrix, scale);
    transformation_matrix = glm::rotate(transformation_matrix, glm::radians(theta), rotation_y);

    unsigned int transformationLoc = glGetUniformLocation(shaderProg, "transform");
    glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));

    //Apply textures
    glActiveTexture(GL_TEXTURE0);
    GLuint tex0Address = glGetUniformLocation(shaderProg, "tex0");
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(tex0Address, 0);

    //Normal map
    glActiveTexture(GL_TEXTURE1);
    GLuint tex1Address = glGetUniformLocation(shaderProg, "norm_tex");
    glBindTexture(GL_TEXTURE_2D, norm_tex);
    glUniform1i(tex1Address, 1);

    glUseProgram(shaderProg);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 14);
}

void Model::deleteBuffers()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}