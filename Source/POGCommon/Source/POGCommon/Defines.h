#pragma once

constexpr const char* FileName(const char* path) 
{
    const char* file = path;
    while (*path) 
    {
        if (*path++ == '\\') 
        {
            file = path;
        }
    }
    return file++;
}

#define POG_FILE __FILE__
#define POG_LINE_NUMBER __LINE__
#define POG_FUNCTION_SIGNATURE __FUNCTION__
#define POG_FILENAME FileName(POG_FILE)