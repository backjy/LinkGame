//
//  LinkSpriteCell.h
//  LinkGame
//
//  Created by CpyShine on 13-4-19.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _LinkSpriteCell_H
#define _LinkSpriteCell_H

#include "cocos2d.h"
#include "LinkGameConfig.h"

using namespace cocos2d;


class LinkSpriteCell :public CCSprite ,public CCTouchDelegate{
    
    
public:
    int type;
    
    bool LSC_isSelect;
    
    LinkGameCellProperty property;
    
    LinkGameCell_TouchEvent * touch_delegate;
    
    void initWith(int _column, int _row, int _type){
        property.c_column = _column;
        property.c_row = _row;
        std::string s;
        switch (_type) {
            case 1:
                s="diamond_1.png";
                break;
            case 2:
                s="diamond_2.png";
                break;
            case 3:
                s="diamond_3.png";
                break;
            case 4:
                s="diamond_4.png";
                break;
            case 5:
                s="diamond_5.png";
                break;
            case 6:
                s="diamond_6.png";
                break;
            case 7:
                s="diamond_7.png";
                break;
            case 8:
                s="diamond_8.png";
                break;
            default:
                break;
        }
        
        this->initWithFile(s.c_str());
        LSC_isSelect = false;
        type = _type;
    }
    
    virtual bool init(void);
    virtual void onEnter(void);
    virtual void onExit(void);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    CREATE_FUNC(LinkSpriteCell);

#pragma mark -
    void Cell_Disappear();

    void Cell_Select();
    void Cell_DisSellect();
};

#endif