//
//  GLObject.cpp
//  OpenGL_Transformations
//
//  Created by Rafael Radkowski on 9/12/15.
//
//

#include <glm/glm.hpp>


glm::mat4 g_projectionMatrix; // Store the projection matrix
glm::mat4 g_viewMatrix; // Store the view matrix


glm::mat4 g_trackball; // the trackball
glm::mat4 g_rotated_view;

#include "GLObject.h"



void SetTrackballLocation(glm::mat4 trackball)
{
    g_trackball = trackball;
    g_rotated_view = g_viewMatrix * g_trackball;
}

void SetViewAsLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    g_viewMatrix = glm::lookAt(eye, center, up);
    
    g_rotated_view = g_viewMatrix * g_trackball;
}



GLObject::GLObject()
{

    g_projectionMatrix = glm::perspective(1.57f, (float)800 / (float)600, 0.1f, 100.f);
    g_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    g_trackball =  glm::mat4();
    g_rotated_view = glm::mat4();
    
}


GLObject::~GLObject()
{

}


/*!
 Add the model view matrix, especially the three shader program objects to
 the shader program "program"
 */
bool GLObject::addModelViewMatrixToProgram(GLuint program)
{
    
    _projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrixBox"); // Get the location of our projection matrix in the shader
    _viewMatrixLocation = glGetUniformLocation(program, "viewMatrixBox"); // Get the location of our view matrix in the shader
    _modelMatrixLocation = glGetUniformLocation(program, "modelMatrixBox"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix()[0][0] ); // Send our projection matrix to the shader
    glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &viewMatrix()[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]); // Send our model matrix to the shader

    return true;
}

/*!
 Set the appearance of this object
 */
void GLObject::setApperance(GLAppearance& apperance)
{
    if(_apperance.exists())
    {
        cerr << "[GLObject] - Did not set apperrance. The appearance for this object has already been set and cannot be changed without re-initialization" << endl;
        return;
    }
    
    _apperance = apperance;
}


/*!
 Set the appearance of this object
 */
void setApperance(GLAppearance& apperance);





glm::mat4 GLObject::projectionMatrix(void)
{
    return g_projectionMatrix;
}


glm::mat4 GLObject::viewMatrix(void)
{
    return g_viewMatrix;
}



// returns the rotated view matrix, mulitplied with the trackball.
glm::mat4 GLObject::rotatedViewMatrix(void)
{
    return g_rotated_view;
}








