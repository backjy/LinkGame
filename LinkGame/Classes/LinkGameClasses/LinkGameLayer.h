//
//  LinkGameLayer.h
//  LinkGame
//
//  Created by CpyShine on 13-4-19.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _LinkGameLayer_H
#define _LinkGameLayer_H

#include "cocos2d.h"

#include "LinkGameConfig.h"

using namespace cocos2d;
class LinkGameDateHandle;
class LinkGameLayer :public CCLayer,public LinkGameCell_TouchEvent {
    
    
public:
    bool _isDraw;
    LinkGameDateHandle * dateHandle;
    LinkSpriteCell * _currentSelectCell;
    static LinkGameLayer *LGL_getSharedGameLayer();
    
    void LGL_addLinkSpriteCellAt(int _column,int _row,int _type,CCPoint &pos);
    
    virtual bool init(void);
    virtual void onEnter(void);
    virtual void onExit(void);
    virtual void onEnterTransitionDidFinish(void);
    virtual void draw(void);
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void LinkGameCell_TouchBegan(LinkSpriteCell *_cell);
    
    void startGame();
    
    CREATE_FUNC(LinkGameLayer);
    
    virtual ~LinkGameLayer();
    
};

#endif