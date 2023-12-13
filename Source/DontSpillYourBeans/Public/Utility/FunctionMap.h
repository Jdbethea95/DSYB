// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include <functional>

/**
 * 
 */
class DONTSPILLYOURBEANS_API FunctionMap
{
public:

    FunctionMap();

    ~FunctionMap();

    // Add a function to the map by name
    void AddVoidFunction(const FName& name, std::function<void()> function);

    // Execute a function by name
    void ExecuteVoidFunction(const FName& name);

    // Add a function to the map by name
    void AddBoolIntFunction(const FName& name, std::function<bool(int)> function);

    // Execute a function by name
    bool ExecuteBoolIntFunction(const FName& name, int number);

private:

    std::map<FName, std::function<void()>> VoidFunctions;
  
    std::map<FName, std::function<bool(int)>> BoolIntFunctions;
	
};
