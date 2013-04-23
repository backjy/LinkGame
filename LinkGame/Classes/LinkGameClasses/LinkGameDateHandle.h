//
//  LinkGameDateHandle.h
//  LinkGame
//
//  Created by CpyShine on 13-4-19.
//
//

#ifndef __LinkGame__LinkGameDateHandle__
#define __LinkGame__LinkGameDateHandle__

#include <iostream>
#include "cocos2d.h"
#include "LinkGameConfig.h"
using namespace cocos2d;

class LinkGameDateHandle {
    
    int LGDH_T_Row;
    int LGDH_T_Column;
    int LGDH_T_Count;
    
    int * LGDH_stateArray;
    CCPoint * LGDH_positionArray;
    
public:
    
    void LGDH_initWithCloumAndRow(int _column,int _row,float _t_width,float _t_height);
    
    inline int LGDH_getTotalCounts(){
        return LGDH_T_Count;
    }
    
    void LGDH_ShowDebug(){
        printf("abcdefghijklmnopqrstuvwxyz\n");
        for (int r=LGDH_T_Row-1; r>=0; r--) {
            for (int i=0; i<LGDH_T_Column; i++) {
                int index = r*LGDH_T_Column +i;
                printf("%d",LGDH_stateArray[index]);
            }
            printf("-----%02d\n",r);
        }
        printf("abcdefghijklmnopqrstuvwxyz\n");
    }
    
    bool LGDH_MatchAWithB(const LinkGameCellProperty &_ap,const LinkGameCellProperty &_bp){
        if (LGDH_MatchAtoB(_ap, _bp)) {
            LGDH_resetStateAtIndex(_ap);
            LGDH_resetStateAtIndex(_bp);
            printf("\n");
            return true;
        }
        return false;
    }
  
private:
    
    inline void LGDH_resetStateAtIndex(const LinkGameCellProperty &_p){
        int _index = LGDH_getColumnAndRowAtIndex(_p);//(_p.c_row *LGDH_T_Column) + _p.c_column;
        if (_index>=0) {
            LGDH_stateArray[_index]=0;
        }
    }
    
    inline int LGDH_getColumnAndRowAtIndex(const LinkGameCellProperty & _pro){//通过 行列得到 ——index
        int _index = (_pro.c_row *LGDH_T_Column) + _pro.c_column;
        if (_index >= LGDH_T_Count || _index <0){
            return -1;
        }
        return _index;
    }
    
    inline int LGDH_getLGDStateArrayStateAtIndex(int _index){//得到状态在 ——index位置
        return LGDH_stateArray[_index];
    }
    
    inline int LGDH_getStateAtCellProperty(const LinkGameCellProperty &_pro){//直接通过 行列的到当前位置的状态
        int _index = LGDH_getColumnAndRowAtIndex(_pro);
        if (_index>=0) {
            printf("%d,%d ",_index,LGDH_getLGDStateArrayStateAtIndex(_index));
            return LGDH_getLGDStateArrayStateAtIndex(_index);
        }
        printf("1 ");
        return 1;//当返回为真的时候失败，所以超界时也要返回失败
    }
    
    
    bool LGDH_MatchAtoB(const LinkGameCellProperty &_ap,const LinkGameCellProperty &_bp);//开始匹配
    
    bool LGDH_MatchSameColumnOrRow_direct(const LinkGameCellProperty &_a,const LinkGameCellProperty &_b);//同行或同列的匹配
    
    bool LGDH_MatchWithTwoCorner(const LinkGameCellProperty &_a,const LinkGameCellProperty &_b);
    bool LGDH_MatchWithOneCorner(const LinkGameCellProperty &_a,const LinkGameCellProperty &_b);
    
#pragma mark - 
public:
    LinkGameDateHandle(){}
    ~LinkGameDateHandle(){
        if (LGDH_stateArray ){
            delete [] LGDH_stateArray;
        }
        if (LGDH_positionArray) {
            delete [] LGDH_positionArray;
        }
    }
    
};

#endif /* defined(__LinkGame__LinkGameDateHandle__) */
