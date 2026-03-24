//
// Created by iceoc0 on 2025/4/20.
//

#ifndef POLYGONDISPLAY_CONE_1_H
#define POLYGONDISPLAY_CONE_1_H

#include "sphere_1.h"
#include "../polygonClass/ConeDemo.h"

// 心 900 250 150 方 50 高 100
#define radiusExpand (30.f)
/*
 * 倒反包围盒
 * lb-----rb
 *        |
 *        |
 *        |
 * lt --- rt
 *
 */
ConeXYZ* ConePos001 = new ConeXYZ({1150.f-radiusExpand,250.f+300.f,200.f-radiusExpand},{1250.f+radiusExpand,250.f+300.f,200.f-radiusExpand},
                                  {1250.f+radiusExpand,250.f+300.f,300.f+radiusExpand},{1150.f-radiusExpand,250.f+300.f,300.f+radiusExpand},
                                  {1200.f,150.f+300.f,250.f});
ConeXYZ* ConePos002 = new ConeXYZ({1150.f,250.f,100.f},{1250.f,250.f,100.f},{1250.f,250.f,200.f},{1150.f,250.f,200.f},
                                  {1200.f,150.f,150.f});

void coneInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr,ConeXYZ* _tblrd,int frontColor1,int frontColor2, int backColor,  unsigned char _debug);
void coneInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr,ConeXYZ* _tblrd,int frontColor1,int frontColor2, int backColor,  unsigned char _debug){
    unique_ptr<ConeDemo> cone01 = make_unique<ConeDemo>(_tblrd->ltSet,_tblrd->rtSet,_tblrd->rbSet,_tblrd->lbSet,
                                    _tblrd->downCuspSet, _debug);
    cone01->setFrontColor(frontColor1,frontColor2); // 1 ? 2 葵扇黄
    cone01->setBackColor(backColor);

    polygonAllPtr->push_back(std::move(cone01));
}
#endif //POLYGONDISPLAY_CONE_1_H
