//
// Created by iceoc0 on 2025/12/13.
//

#ifndef POLYGONDISPLAY_BEZIER3IMG_HPP
#define POLYGONDISPLAY_BEZIER3IMG_HPP
#include "Bezier33Edge4.h"


class Bezier3Img : public Bezier33Edge4  {
public:
    Bezier3Img(glm::vec3 _P[4][4]);
};


#endif //POLYGONDISPLAY_BEZIER3IMG_HPP