//
// Created by sriteja on 13/1/19.
//

#include "IrregularPolygon.h"
#include "main.h"


IrregularPolygon::IrregularPolygon(int num_of_sides, GLfloat *coordinates, glm::vec3 position, color_t color,
                                   float rotation_angle, glm::vec3 scale_values, glm::vec3 rotation_axis) {
    std::cout << "num_sides " << num_of_sides << std::endl;

    this->num_of_sides = num_of_sides;
    this->position = position;
    this->rotation = rotation_angle;
    this->scale = scale_values;
    this->rotation_axis = rotation_axis;
    convertCoordinatesToVertices(coordinates, num_of_sides, this->vertices);
    construct(this->vertices);
    this->color = color;
    this->object = create3DObject(GL_TRIANGLES, 3*num_of_sides, this->vertex_data, color, GL_FILL);
}

void IrregularPolygon::convertCoordinatesToVertices(GLfloat *coordinates, int n, glm::vec3 *vertices) {
    std::cout << "coor " << coordinates[3] << std::endl;
    for (int i=0,j=0; i<3*n; i+=3, j++) {
        vertices[j] = glm::vec3(coordinates[i], coordinates[i + 1], coordinates[i + 2]);
    }
    std::cout << vertices[1].x << std::endl;
//    for (auto i = vertices[1].begin(); i != path.end(); ++i)
//        std::cout << *i << ' ';
}

void IrregularPolygon::findCentroid() {
    float sum_x=0, sum_y=0, sum_z=0;
    std::cout << this->vertices[1].x << std::endl;
    for (int i=0; i<this->num_of_sides; i++)
    {
        sum_x += this->vertices[i].x;
        sum_y += this->vertices[i].y;
        sum_z += this->vertices[i].z;
    }
    centroid.x = sum_x/float(this->num_of_sides);
    centroid.y = sum_y/float(this->num_of_sides);
    centroid.z = sum_z/float(this->num_of_sides);
    std::cout << "sum " << sum_x << ' ' << sum_y << ' ' << sum_z;
}

void IrregularPolygon::copyVectorToArray(glm::vec3 vect, GLfloat *arr, int index) {
    arr[index++] = vect.x;
    arr[index++] = vect.y;
    arr[index] = vect.z;
}

void IrregularPolygon::print_array(GLfloat *arr) {
    int start=0;
    for (int i=0;i<this->num_of_sides;i++)
    {
        for (int j=0;j<3;j++) {
            for (int k=0;k<3;k++)
                printf("%f ",arr[start++] );
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
}

void IrregularPolygon::construct(glm::vec3 vertices[]) {
    findCentroid();

    int i=0, j=1;
    int k=0;
    for(;i<this->num_of_sides;i++,j++) {

        copyVectorToArray(this->centroid, this->vertex_data, k);
        k += 3;

        copyVectorToArray(vertices[i], this->vertex_data, k);
        k += 3;

        copyVectorToArray(vertices[j%this->num_of_sides], this->vertex_data, k);
        k += 3;
    }

    print_array(this->vertex_data);
//    std::cout << "Centroid " << centroid.x << ' ' << centroid.y << centroid.z << std::endl;
}

void IrregularPolygon::draw(glm::mat4 VP, bool reflect) {
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate(this->rotation, this->rotation_axis);
    glm::mat4 scale_mat = glm::scale(this->scale);
    glm::mat4 ref_mat = glm::mat4(1.0f);
    if (reflect) {
        ref_mat[0] = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);
        ref_mat[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
        ref_mat[2] = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
        ref_mat[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
//    glm::mat4 reflection = glm::reflect(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    // No need as coords centered at 0, 0, 0 of cube around which we want to rotate
//     rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate*scale_mat*ref_mat);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
//    print_array(this-)
    draw3DObject(this->object);

}

