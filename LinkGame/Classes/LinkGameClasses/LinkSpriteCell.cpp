//
//  LinkSpriteCell.cpp
//  LinkGame
//
//  Created by CpyShine on 13-4-19.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "LinkSpriteCell.h"

bool LinkSpriteCell::init(void){
    if (!CCSprite::init()) {
        return false;
    }
    touch_delegate = NULL;
    return true;
}


void LinkSpriteCell::onEnter(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void LinkSpriteCell::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    touch_delegate = NULL;
}

bool LinkSpriteCell::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCPoint locationAR = this->convertTouchToNodeSpaceAR(pTouch);
//    CCLOG("%f,%f",locationAR.x,locationAR.y);
    CCPoint convertToWorldAR = this->convertToWorldSpaceAR(locationAR);
//    CCLOG("%f,%f",convertToWorldAR.x,convertToWorldAR.y);
//    CCPoint convertToNodeAR = this->convertToNodeSpaceAR(locationAR);
//    CCLOG("%f,%f",convertToNodeAR.x,convertToNodeAR.y);
//
//    CCPoint location = this->convertTouchToNodeSpace(pTouch);
//    CCLOG("%f,%f",location.x,location.y);
//    CCPoint convertToWorld = this->convertToWorldSpace(locationAR);
//    CCLOG("%f,%f",convertToWorld.x,convertToWorld.y);
//    CCPoint convertToNode = this->convertToNodeSpace(locationAR);
//    CCLOG("%f,%f",convertToNode.x,convertToNode.y);
//    
//    CCLOG("%f,%f,%f,%f",this->boundingBox().origin.x,this->boundingBox().origin.y,this->boundingBox().origin.x+this->boundingBox().size.width,this->boundingBox().origin.y+this->boundingBox().size.height);
    if (touch_delegate) {
        if (this->boundingBox().containsPoint(convertToWorldAR)) {
            touch_delegate->LinkGameCell_TouchBegan(this);
        }else
            return false;
    }
    
    return false;
}

void LinkSpriteCell::Cell_Select(){
//    this->stopAllActions();
    LSC_isSelect = true;
    CCScaleTo * scaleTo = CCScaleTo::create(0.5, 1.2);
    CCScaleTo * scaleBack = CCScaleTo::create(0.5, 1);
    CCSequence * sequence = CCSequence::create(scaleTo,scaleBack,NULL);
    CCRepeatForever * repeateF = CCRepeatForever::create(sequence);
    this->getActionManager()->addAction(repeateF, this, false);
//    this->runAction(repeateF);
//    this->setScale(1.3);
//    CCLog("run Action   !");
}

void LinkSpriteCell::Cell_DisSellect(){
    this->stopAllActions();
    LSC_isSelect = false;
    this->setScale(1);
}

void LinkSpriteCell::Cell_Disappear(){
    this->removeFromParentAndCleanup(true);
}