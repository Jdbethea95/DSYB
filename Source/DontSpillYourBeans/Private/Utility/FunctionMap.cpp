// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/FunctionMap.h"

FunctionMap::FunctionMap()
{
}

FunctionMap::~FunctionMap()
{
}

void FunctionMap::AddVoidFunction(const FName& name, std::function<void()> function)
{
    VoidFunctions[name] = function;
}

void FunctionMap::ExecuteVoidFunction(const FName& name)
{
    if (VoidFunctions.find(name) != VoidFunctions.end())
    {
        auto action = VoidFunctions[name];
        action();
    }
    else 
    {
        //bad stuff
    }
}

void FunctionMap::AddBoolIntFunction(const FName& name, std::function<bool(int)> function)
{
    BoolIntFunctions[name] = function;
}

bool FunctionMap::ExecuteBoolIntFunction(const FName& name, int number)
{
    if (BoolIntFunctions.find(name) != BoolIntFunctions.end())
    {
        auto action = BoolIntFunctions[name];
        action(number);

        return true;
    }
    else
    {
        return false;
    }
}
