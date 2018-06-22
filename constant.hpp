#pragma once
#include "types.hpp"
#include <unordered_map>
#include <string>

/**
 * Constant interface for any constants implementation
 */
class Constant {
public:
    typedef std::unordered_map<std::string, NumberRef> Registry;
    
    /**
     * Global functions registry
     */
    static Registry registry;
    
};
