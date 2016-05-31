//
//  ServerCommands.h
//  slitherApp
//
//  Created by ocean on 5/31/16.
//
//

#ifndef ServerCommands_h
#define ServerCommands_h

typedef enum {
    ServerCommandLogin = 10000,
    ServerCommandSyncSlither = 10001,
    ServerCommandMap = 10002,
    ServerCommandKill = 10003,
    ServerCommandEatFood = 10004,
    ServerCommandLogout = 10005,
} ServerCommand;

#endif /* ServerCommands_h */
