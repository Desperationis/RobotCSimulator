#pragma once
#include <bitset>

// An ID representing an Entity
using Entity = size_t;

// The maximum number of entities
const Entity MAX_ENTITIES = 10000;

// An integer representing the amount of bits a Signature shifts by
using ComponentType = std::uint8_t;

// The maximum number of components
const ComponentType MAX_COMPONENTS = 15;

// A bitset used to identify the components associated with something
using Signature = std::bitset<MAX_COMPONENTS>;