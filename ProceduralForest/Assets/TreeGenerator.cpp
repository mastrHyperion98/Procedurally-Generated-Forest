//
// Created by hyperion(Steven Smith) on 2020-04-05.
//
//

#include "TreeGenerator.h"
#include <cmath>
#include "Cube.h"
#include "Material.h"
#include <iostream>
#include "random"
Entity TreeGenerator::generateTree(float bias) {
    // generate the tree here and return it.
    Entity tree;
    generateTrunk( &tree);
    generateLeaves(&tree, bias);
    return tree;
}
void TreeGenerator::generateTrunk( Entity *tree) {
    Material mat;
    mat.addTexture("../Assets/Textures/bark.bmp");
    mat.vertexColor= vec3(0.290196, 0.172549, 0.160784);
    for(int i = 0; i < 8; i++) {
        Cube *cube=new Cube{mat, vec3(1)};
        tree->addComponent(cube);
        if(i != 0)
            cube->Translate(vec3(0,(tree->getComponent(i-1)->getTransform().size.y*
            tree->getComponent(i-1)->getTransform().scaling.y) +tree->getComponent(i-1)->getTransform().position.y ,0));
    }
}

void TreeGenerator::generateLeaves( Entity *tree, float bias) {
    int square_count{0};
    Material mat;
    mat.addTexture("../Assets/Textures/leaves_c4.png");
    // equation of a sphere is
    //(x-a)^2 + (y-b)^2 +(2-c)^2 = r^2
    //(a,b,c) --> origin
    int radius =4;
    int buttom_cutoff = 0;//ceilf(radius/2);
    vec3 center = tree->getComponent(7)->getTransform().position;
    int increment = 1; // unit cube

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,100); // distribution in range [1, 6]
    // compute in two halves
    for(int i = 0; i <= radius; i++){
        int num_x = computeNumberInX(center, radius, i, increment);
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(j, i * increment, 0);
            if(j!=0) {
                Cube *cube = new Cube{mat, vec3(1)};
                square_count++;
                tree->addComponent(cube);
                cube->Translate(position);
            }
            int num_z = computeNumberInZ(position, center, radius,j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(j, i * increment, k);

                    Cube *cube = new Cube{mat, vec3(1)};
                    square_count++;
                    tree->addComponent(cube);
                    cube->Translate(position);

                position = center + vec3(j, i * increment, -k);
                    Cube *cube2 = new Cube{mat, vec3(1)};
                    square_count++;
                    tree->addComponent(cube2);
                    cube2->Translate(position);
            }
        }
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(-j, i * increment, 0);
            if(j!=0 ) {
                Cube *cube = new Cube{mat, vec3(1)};
                square_count++;
                tree->addComponent(cube);
                cube->Translate(position);
            }
            int num_z = computeNumberInZ(position, center, radius,j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(-j, i * increment, k);

                    Cube *cube = new Cube{mat, vec3(1)};
                    square_count++;
                    tree->addComponent(cube);
                    cube->Translate(position);

                position = center + vec3(-j, i * increment, -k);

                    Cube *cube2 = new Cube{mat, vec3(1)};
                    square_count++;
                    tree->addComponent(cube2);
                    cube2->Translate(position);

            }
        }
    }

    for(int i = 0; i < radius - buttom_cutoff; i++){
        int num_x = computeNumberInX(center, radius, i, increment);
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(j, -(i * increment), 0);
            if(j!=0) {
                Cube *cube = new Cube{mat, vec3(1)};
                square_count++;
                tree->addComponent(cube);
                cube->Translate(position);
            }
            int num_z = computeNumberInZ(position, center, radius,j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(j, -(i * increment), k);

                    Cube *cube = new Cube{mat, vec3(1)};
                    square_count++;
                    tree->addComponent(cube);
                    cube->Translate(position);


                position = center + vec3(j, -(i * increment), -k);
                    Cube *cube2 = new Cube{mat, vec3(1)};
                    square_count++;
                    tree->addComponent(cube2);
                    cube2->Translate(position);

            }
        }
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(-j, -(i * increment), 0);
            if(j!=0) {
                Cube *cube = new Cube{mat, vec3(1)};
                square_count++;
                tree->addComponent(cube);
                cube->Translate(position);
            }
            int num_z = computeNumberInZ(position, center, radius,j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(-j, -(i * increment), k);

                    Cube *cube = new Cube{mat, vec3(1)};
                    square_count++;
                    tree->addComponent(cube);
                    cube->Translate(position);

                position = center + vec3(-j, -(i * increment), -k);
                    Cube *cube2 = new Cube{mat, vec3(1)};
                    square_count++;
                    tree->addComponent(cube2);
                    cube2->Translate(position);
            }
        }
    }
    std::cout << square_count << std::endl;
    // we want to remove x_number of blocks based on the total number of blocks in the tree
    int to_remove = square_count *0.40;

    for(int i = 0; i < to_remove; i++){
        int tree_size = tree->getSize() - 1;
        std::uniform_int_distribution<std::mt19937::result_type> dist(square_count/3,tree_size); // distribution in range [1, 6]
        int remove = dist(rng);
        tree->removeComponent(remove);
    }


}
float TreeGenerator::euclidianNorm(vec3 point, vec3 center) {
    vec3 vect = point - center;
    float norm = sqrt(pow(vect.x,2)+pow(vect.y,2)+pow(vect.z, 2));
    return norm;
}

bool TreeGenerator::inSphere(vec3 point, vec3 center, float radius) {
    return euclidianNorm(point, center) <= radius;
}
int TreeGenerator::computeNumberInX(vec3 center, float radius, int index, int increment) {
    float y = pow((center.y + index*increment) - center.y, 2);
    float z = 0; // always
    float x = sqrt(pow(radius, 2) - y) + center.x;

    return x;
}

int TreeGenerator::computeNumberInZ(vec3 position, vec3 center, float radius, int index, int increment) {
    float y = pow((center.y + index*increment) - center.y, 2);
    float x = pow(position.x - center.x, 2);

    float z = sqrt(pow(radius, 2) - y - x) + center.z;

    return z;
}