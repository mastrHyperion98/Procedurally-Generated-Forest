//
// Created by hyperion on 2020-04-05.
//

#include <World.h>
#include "Tree.h"

void Tree::Draw() {
    /*
     * Instance drawing no need to setup anything TreeGenerator should do that for us. Using one VAO
     * and using instancing
     */

    glm::mat4 modelWorldMatrix = mat4(1.0f);
  /*  glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, trunk_mat.diffuseMapId);
    Renderer::getCurrentShader()->setInt("material.diffuseMap[0]", 0);*/
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, leaves.diffuseMapId);
    Renderer::getCurrentShader()->setInt("material.diffuseMap[0]",0 );
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, trunk.diffuseMapId);
    Renderer::getCurrentShader()->setInt("material.diffuseMap[1]",2 );
    Renderer::getCurrentShader()->setBool("material.isTextured", true);

        // Set our Texture sampler to user Texture Unit 0

    // load the proper vao
    glBindVertexArray(vao);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // set the color
   // Renderer::getCurrentShader()->setVec3("material.color", cube->getMaterial().vertexColor.x, cube->getMaterial().vertexColor.y, cube->getMaterial().vertexColor.z);
    // setup transform
    transform->transformation = mat4(1.0);
    transform->transformation = translate(transform->transformation, transform->position);
    transform->transformation = transform->transformation * glm::mat4_cast(transform->rotation);
    transform->transformation = glm::scale(transform->transformation, transform->scaling);
    // matrix on the right applies first so we want to do the following
    modelWorldMatrix = World::getCurrent().getTransform().transformation* transform->transformation ;
    Renderer::getCurrentShader()->setMat4("worldMatrix", modelWorldMatrix);
    // draw a cube
    glDisable(GL_CULL_FACE);
    glDrawArraysInstanced(Renderer::getRenderMode(), 0, 36, data_offset.size());
    Renderer::getCurrentShader()->setBool("material.isTextured", false);
  //  glDeleteTextures(1,&leaves.diffuseMapId);
   // glDeleteTextures(1,&trunk_mat.diffuseMapId);
    glEnable(GL_CULL_FACE);
}

void Tree::Update() {

}



void Tree::addLeavesOffset(TreeOffsetData l_offset) {
   data_offset.push_back(l_offset);
}


void Tree::removeLeavesOffset(int index) {
    data_offset.erase(data_offset.begin()+index);
}

void Tree::createVAO(){
    leaves.addTexture("../Assets/Textures/leaves_c4.png");
    trunk.addTexture("../Assets/Textures/tree.jpg");

    // Cube model
    // Cube model stolen from lab 3
    const TexturedColoredVertex texturedCubeVertexArray[] = {  // position,
            TexturedColoredVertex(transform->size * vec3(-0.5f,-0.5f,-0.5f),vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)), //left - red
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f, 0.5f),vec3(-1.0f, 0.0f, 0.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)),

            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f,-0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 1.0f)), // far - blue
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 1.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(1.0f, 1.0f)), // bottom - turquoise
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f),vec3( 0.0f,-1.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f, 0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f),vec3( 0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)), // near - green
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f, 0.5f),vec3( 0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)), // right - purple
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f),vec3( 1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f),vec3( 1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)), // top - yellow
            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(1.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f,-0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f,-0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f))
    };
    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
                          3,                   // size
                          GL_FLOAT,            // type
                          GL_FALSE,            // normalized?
                          sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
                          (void*)0             // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,                            // attribute 2 matches aUV in Vertex Shader
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TexturedColoredVertex),
                          (void*)(1*sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TexturedColoredVertex),
                          (void*)(2*sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    );

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, data_offset.size() * sizeof(data_offset), &data_offset[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
     glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(1*sizeof(vec3)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glVertexAttribDivisor(3, 1); // tell OpenGL this is an instanced vertex attribute.
    glVertexAttribDivisor(4, 1); // tell OpenGL this is an instanced vertex attribute.


    vao = vertexArrayObject;
}

void Tree::setTrunkHeight(int height) {
    trunk_height = height;
}