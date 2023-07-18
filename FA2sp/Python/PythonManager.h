#pragma once

class PythonManager
{
public:
    static bool Init();
    static void Release();
    static bool Is_Initialized();
    static bool Execute(const char* filepath);

private:
    static bool IsInitialized;
};