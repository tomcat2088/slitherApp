//
//  Logger.cpp
//  slitherApp
//
//  Created by wangyang on 16/5/12.
//
//

#include "Logger.hpp"
void logInfo(std::string info)
{
    printf("%s",info.data());
}

void logWarning(std::string warning)
{
    printf("%s",warning.data());
}

void logError(std::string error)
{
    printf("%s",error.data());
}