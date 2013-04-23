//
//  LinkGameConfig.h
//  LinkGame
//
//  Created by CpyShine on 13-4-20.
//
//

#ifndef LinkGame_LinkGameConfig_h
#define LinkGame_LinkGameConfig_h

struct LinkGameCellProperty {
    int c_column;
    int c_row;
};

class LinkSpriteCell;
class LinkGameCell_TouchEvent {
public:
    virtual void LinkGameCell_TouchBegan(LinkSpriteCell *_cell)=0;
};

#endif
