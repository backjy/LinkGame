//
//  LinkGameDateHandle.cpp
//  LinkGame
//
//  Created by CpyShine on 13-4-19.
//
//
#include "LinkGameLayer.h"
#include "LinkGameDateHandle.h"


void LinkGameDateHandle::LGDH_initWithCloumAndRow(int _column,int _row,float _t_width,float _t_height){
    
    
    float _halfWi = _t_width * 0.5f;
    float _halfHe = _t_height * 0.5f;
    
    LGDH_T_Column = _column;
    LGDH_T_Row = _row;
    LGDH_T_Count = _row*_column;
    
    LGDH_stateArray = new int[LGDH_T_Count]();
    memset(LGDH_stateArray, 0, sizeof(int)*LGDH_T_Count);//初始化 状态数组
    LGDH_positionArray = new CCPoint[LGDH_T_Count]();
    
    for (int r=0;r<LGDH_T_Row; r++) {
        for (int c=0; c<LGDH_T_Column; c++) {
            
            int _index = (r *LGDH_T_Column) + c;
            
            if (_index<0 || _index>=LGDH_T_Count) {continue;}
            CCPoint pos = CCPoint(_t_width*c + _halfWi, _t_height*r + _halfHe);
            LGDH_positionArray[_index] = pos;
            
            if ((r==0 || r==(LGDH_T_Row-1)) || (c==0|| c==(LGDH_T_Column-1))) {
                continue;
            }
            int _type = arc4random()%8 + 1;
            LGDH_stateArray[_index] = _type;            LinkGameLayer::LGL_getSharedGameLayer()->LGL_addLinkSpriteCellAt(c, r, _type,pos);
        }
    }
    LGDH_ShowDebug();
}



/*基本思路是
 1.如果两个点相近的话 直接就返回true
 2.如果两个点在同行或同列的时候就直线 match 是否成功 如果成功直接返回true
 3.如果有一个折点
 4.如果有两个折点
 
 */
bool LinkGameDateHandle::LGDH_MatchAtoB(const LinkGameCellProperty &_ap, const LinkGameCellProperty &_bp){
    
#pragma mark - 1
    int _distance = abs(_ap.c_column-_bp.c_column)+abs(_ap.c_row-_bp.c_row);//当两个点相邻时 return true
    if (_distance==1) {
        CCLog("两个相邻!");
        return true;
    }
    
#pragma mark - 2
    if(_ap.c_column==_bp.c_column || _ap.c_row==_bp.c_row){//如果
        if(LGDH_MatchSameColumnOrRow_direct(_ap, _bp)) {
            CCLog("在一条直线上!");
           return true; 
        }
    }
#pragma mark - 3
    bool _correctAB = (_ap.c_column>_bp.c_column)?false:true;//纠正 a b的列谁大
    
    if (_correctAB) {
        CCLog("开始1次折点 尝试!");
        if (LGDH_MatchWithOneCorner(_ap, _bp)) {//先检查一个折点
            CCLog("1次 折点成功 ，未换位置!");
            return true;
        }
        CCLog("开始1次折点 尝试失败!");
        CCLog("开始2次折点 尝试!");
        if( LGDH_MatchWithTwoCorner(_ap, _bp)){//检查两个折点
            CCLog("2次 折点成功 ，未换位置!");
            return true;
        }
        CCLog("开始2次折点 尝试失败!");
    }else{
        CCLog("开始1次折点 尝试!");
        if (LGDH_MatchWithOneCorner(_bp, _ap)) {
            CCLog("1次 折点成功 ，换位置!");
            return true;
        }
        CCLog("开始1次折点 尝试失败!");
        CCLog("开始2次折点 尝试!");
        if (LGDH_MatchWithTwoCorner(_bp, _ap)){
            CCLog("2次 折点成功 ，换位置!");
            return true;
        }
        CCLog("开始2次折点 尝试失败!");
    }
    
    return false;
}

bool LinkGameDateHandle::LGDH_MatchWithTwoCorner(const LinkGameCellProperty &_a, const LinkGameCellProperty &_b){
    
    LinkGameCellProperty _tp = _a;
    for (int _row = _a.c_row+1; _row<LGDH_T_Row; _row++) {//向上走
        CCLog("向上开始match......");
        _tp.c_row = _row;
        if (LGDH_getStateAtCellProperty(_tp)) {
            CCLog("向上match失败");
            break;
        }else{
            if(LGDH_MatchWithOneCorner(_tp, _b))
                return true;
        }
    }
    
    for (int _row = _a.c_row-1; _row>=0; _row--) {//向下走
        CCLog("向下开始match......");
        _tp.c_row = _row;
        if (LGDH_getStateAtCellProperty(_tp)) {
            CCLog("向下match失败");
            break;
        }else{
            if(LGDH_MatchWithOneCorner(_tp, _b))
                return true;
        }
    }
    
    _tp = _a;
    
    for (int _column=_a.c_column+1;_column<LGDH_T_Column ; _column++) {//向右
        
        CCLog("向右开始match......");
        _tp.c_column = _column;
        if (LGDH_getStateAtCellProperty(_tp)) {
            CCLog("向右match失败");
            break;
        }else{
            if(LGDH_MatchWithOneCorner(_tp, _b))
                return true;
        }
    }
    
    for (int _column=_a.c_column-1; _column>=0; _column--) {//想左
        
        CCLog("向左开始match......");
        _tp.c_column = _column;
        if (LGDH_getStateAtCellProperty(_tp)) {
            CCLog("向左match失败");
            break;
        }else{
            if(LGDH_MatchWithOneCorner(_tp, _b))
                return true;
        }
    }
    
    return false;
}

bool LinkGameDateHandle::LGDH_MatchWithOneCorner(const LinkGameCellProperty &_a, const LinkGameCellProperty &_b){
    
    LinkGameCellProperty _pr;
    _pr.c_column = _b.c_column;     _pr.c_row= _a.c_row;
    CCLog("开始以点(行列)(%d，%d)......!",_pr.c_row,_pr.c_column);
    if (!LGDH_getStateAtCellProperty(_pr) && LGDH_MatchSameColumnOrRow_direct(_a, _pr) && LGDH_MatchSameColumnOrRow_direct(_pr, _b)) {
        return true;
    }
    CCLog("失败(行列)(%d，%d)......",_pr.c_row,_pr.c_column);
    _pr.c_column = _a.c_column;    _pr.c_row = _b.c_row;
    CCLog("开始以点(行列)(%d，%d)......!",_pr.c_row,_pr.c_column);
    if (!LGDH_getStateAtCellProperty(_pr) && LGDH_MatchSameColumnOrRow_direct(_a, _pr) && LGDH_MatchSameColumnOrRow_direct(_pr, _b)) {
        return true;
    }
    CCLog("失败(行列)(%d，%d)......",_pr.c_row,_pr.c_column);
    return false;
}

bool LinkGameDateHandle::LGDH_MatchSameColumnOrRow_direct(const LinkGameCellProperty &_a,const LinkGameCellProperty &_b)//同行 或 同列是时调用此方法匹配
{
    bool isMatch = false;
    if (_a.c_column==_b.c_column) {
        
        printf("开始同列:%d......",_a.c_column);
        
        int _startRow = _a.c_row>_b.c_row?_b.c_row:_a.c_row;
        int _endRow = _a.c_row>_b.c_row?_a.c_row:_b.c_row;
        
        int _column = _a.c_column;
        
        for (int r=_startRow+1; r<_endRow; r++) {//不包括两个点在内都检查
            LinkGameCellProperty _tp;
            _tp.c_column = _column;
            _tp.c_row = r;
            printf("p(%d,%d)",_tp.c_row,_tp.c_column);
            if (LGDH_getStateAtCellProperty(_tp)) {//当返回为真的时候 失败
                printf("失败\n");
                return false;
            }
        }
        isMatch = true;
    }
    
    if (_a.c_row==_b.c_row) {
        printf("开始同行:%d......",_a.c_row);
        int _row = _a.c_row;

        for (int c=_a.c_column+1; c<_b.c_column; c++) {//不包括两个点在内都检查
            LinkGameCellProperty _tp;
            _tp.c_row = _row;
            _tp.c_column = c;
            printf("p(%d,%d)",_tp.c_row,_tp.c_column);
            if (LGDH_getStateAtCellProperty(_tp)) {//当返回为真的时候 失败
                printf("失败\n");
                return false;
            }
        }
        isMatch = true;
    }
    printf("\n");
    return isMatch;
}