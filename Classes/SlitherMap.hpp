//
//  SlitherMap.hpp
//  slitherApp
//
//  Created by wangyang on 16/4/21.
//
//

#ifndef SlitherMap_hpp
#define SlitherMap_hpp

#include <stdio.h>

typedef enum : NSUInteger {
    SlitherMapPropTypeFood
} SlitherMapPropType;

typedef struct {
    double x;
    double y;
    double size;
    int color;
    double value;
    SlitherMapPropType
}SlitherMapProp;

#endif /* SlitherMap_hpp */
