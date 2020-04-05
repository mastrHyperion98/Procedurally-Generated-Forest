//
// Created by Steven Smith on 2020-03-07.
//

#ifndef ASSIGNMENT2_ENTITY_H
#define ASSIGNMENT2_ENTITY_H

#include <vector>
#include "Component.h"
#include "Transform.h"
#include "Shader.h"
class Entity {
public:
    Entity();
    Entity(const Entity& entity);
    Entity& operator=(const Entity& entity);
    ~Entity();
    void SetPosition(vec3 pos);
    void Translate(glm::vec3 translate);
    void Rotate(float angle, glm::vec3 rotate);
    void Scale(glm::vec3 scale);
    void Translate(int component, glm::vec3 translate);
    void Rotate(int component, float angle, glm::vec3 rotate);
    void Scale(int component, glm::vec3 scale);
    void ResetPosition();
    void ResetRotation();
    void ResetScaling();
    void Draw();
    void Update();
    void addComponent(Component);
    Transform getTransform();
protected:
    std::vector<Component*> components;
    Transform transform;
};


#endif //ASSIGNMENT2_ENTITY_H
