//
//  LinkGameLayer.cpp
//  LinkGame
//
//  Created by CpyShine on 13-4-19.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "LinkGameLayer.h"
#include "LinkSpriteCell.h"
#include "LinkGameDateHandle.h"

static LinkGameLayer * _sharedLinkGameLayer=NULL;

LinkGameLayer * LinkGameLayer::LGL_getSharedGameLayer(){
    if (!_sharedLinkGameLayer) {
        _sharedLinkGameLayer = LinkGameLayer::create();
    }
    return _sharedLinkGameLayer;
}

bool LinkGameLayer::init(void){
    if (!CCLayer::init()) {
        return false;
    }
    //set touch enable = yes,and delegate is oneByone
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    this->setPosition(CCPointZero);
    this->setAnchorPoint(CCPointZero);
    _sharedLinkGameLayer = this;
    
    _currentSelectCell = NULL;
    
    return true;
}

void LinkGameLayer::startGame(){
    
    CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("diamond_8.png");
    dateHandle = new LinkGameDateHandle();
    dateHandle->LGDH_initWithCloumAndRow(17,15, texture->getPixelsWide(), texture->getPixelsHigh());
}


void LinkGameLayer::LGL_addLinkSpriteCellAt(int _column, int _row, int _type,CCPoint &pos){
//    static bool a = false;
//    if (a) {
//        return;
//    }
//    a=true;
    LinkSpriteCell * _Cell = LinkSpriteCell::create();
    _Cell->initWith(_column, _row, _type);
    _Cell->setPosition(pos);
    _Cell->touch_delegate = this;
    
    this->addChild(_Cell);
}

void LinkGameLayer::onEnter(void){
    CCLayer::onEnter();
    
}

void LinkGameLayer::onEnterTransitionDidFinish(void){
    CCLayer::onEnterTransitionDidFinish();
}

void LinkGameLayer::onExit(void){
    CCLayer::onExit();
}

bool LinkGameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return false;
}

void LinkGameLayer::LinkGameCell_TouchBegan(LinkSpriteCell *_cell){
    _isDraw = false;
    if (!_currentSelectCell) {
        CCLog("first block selected!");
        _currentSelectCell = _cell;
        _currentSelectCell->Cell_Select();
        return;
    }
    
    if (_currentSelectCell == _cell) {
        CCLog("is same of cell!");
        _currentSelectCell->Cell_DisSellect();
        _currentSelectCell = NULL;
        return;
    }
    
    _cell->Cell_Select();
    
    if (_currentSelectCell->type!=_cell->type) {
        CCLog("is not same tyoe!");
        _currentSelectCell->Cell_DisSellect();
        _currentSelectCell = NULL;
        _cell->Cell_DisSellect();
        return;
    }
    CCLog("start A(%d,%d) matchWith B(%d,%d)",_currentSelectCell->property.c_row,_currentSelectCell->property.c_column, _cell->property.c_row, _cell->property.c_column);
    if (dateHandle->LGDH_MatchAWithB(_currentSelectCell->property, _cell->property)) {
        CCLog("match successed!");
        _currentSelectCell->Cell_Disappear();
        _cell->Cell_Disappear();
        _currentSelectCell = NULL;
//        _cell = NULL;
        dateHandle->LGDH_ShowDebug();
        _isDraw = true;
    }else{
        CCLog("match failed!");
        _cell->Cell_DisSellect();
        _currentSelectCell->Cell_DisSellect();
        _currentSelectCell = NULL;
    }
}



void LinkGameLayer::draw(void){
    if (_isDraw) {
        
    }
}

LinkGameLayer::~LinkGameLayer(){
    _sharedLinkGameLayer = NULL;
    if (dateHandle) {
        delete dateHandle;
        dateHandle = NULL;
    }
    _currentSelectCell = NULL;
    
}

