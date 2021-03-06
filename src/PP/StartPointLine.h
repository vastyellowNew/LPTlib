/*
 * LPTlib
 * Lagrangian Particle Tracking library
 *
 * Copyright (c) 2012-2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

#ifndef PPLIB_LINE_H
#define PPLIB_LINE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <typeinfo>
#include "StartPoint.h"

namespace PPlib
{
//forward declaration
class Line;
Line* LineFactory(REAL_TYPE Coord1[3], REAL_TYPE Coord2[3], int SumStartPoints, double StartTime, double ReleaseTime, double TimeSpan, double ParticleLifeTime);
//! @brief 線分型で定義された開始点の情報を保持するクラス
class Line: public StartPoint
{
    Line() : StartPoint(){}

public:
    //! テキスト出力を行う
    std::string TextPrint(const REAL_TYPE& RefLength, const double& RefTime) const;

    //! TextPrintの出力を読み込む
    void ReadText(std::istream& stream, const REAL_TYPE& RefLength, const double& RefTime);

    //! @brief 開始点オブジェクトをMaxNumStartPointsで指定した開始点数以下のオブジェクトに分割する。
    //! 余りが生じた場合は1つ余計にオブジェクトを生成し、そのオブジェクトに余り領域を入れて返す
    //! @attention 分割前のオブジェクトは残っているので、このメソッド実行後に破棄すること
    //! @param MaxNumStartPoints [in]  分割後のオブジェクトが持つ最大の開始点数
    //! @ret   分割後の開始点オブジェクトを格納したコンテナ
    void Divider(std::vector<StartPoint*>* StartPoints, const int& MaxNumStartPoints);

    //! 格子点(粒子の発生位置)の座標を引数で指定したvectorに格納する
    //! @param Coords [out] 格子点座標
    void GetGridPointCoord(std::vector<REAL_TYPE>& Coords);

private:
    REAL_TYPE    Coord1[3]; //!< 開始点が存在する線分の端点の座標
    REAL_TYPE    Coord2[3]; //!< Coord1とは異なる端点の座標

    friend Line* LineFactory(REAL_TYPE Coord1[3], REAL_TYPE Coord2[3], int SumStartPoints, double StartTime, double ReleaseTime, double TimeSpan, double ParticleLifeTime);
};
static Line* LineFactory(REAL_TYPE Coord1[3], REAL_TYPE Coord2[3], int SumStartPoints, double StartTime, double ReleaseTime, double TimeSpan, double ParticleLifeTime)
{
    Line* tmpStartPoint = new Line;
    if(Coord1 == NULL && Coord2 == NULL && SumStartPoints == NULL && StartTime == NULL && ReleaseTime == NULL && TimeSpan == NULL && ParticleLifeTime == NULL)return tmpStartPoint;

    for(int i = 0; i < 3; i++)
    {
        tmpStartPoint->Coord1[i] = Coord1[i];
        tmpStartPoint->Coord2[i] = Coord2[i];
    }
    tmpStartPoint->SumStartPoints   = SumStartPoints;
    tmpStartPoint->StartTime        = StartTime;
    tmpStartPoint->ReleaseTime      = ReleaseTime;
    tmpStartPoint->TimeSpan         = TimeSpan;
    tmpStartPoint->ParticleLifeTime = ParticleLifeTime;

    return tmpStartPoint;
}
} // namespace PPlib
#endif