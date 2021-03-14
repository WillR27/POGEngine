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

#define PG_FILE __FILE__
#define PG_LINE __LINE__
#define PG_FUNC __FUNCTION__
#define PG_FILENAME FileName(PG_FILE)