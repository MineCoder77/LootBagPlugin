// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "JsonUtil.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LookAtDefinition {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LOOKATDEFINITION
public:
    class LookAtDefinition& operator=(class LookAtDefinition const&) = delete;
    LookAtDefinition(class LookAtDefinition const&) = delete;
#endif

public:
    MCAPI LookAtDefinition();
    MCAPI void deserializeData(class Json::Value&, class SemVersion const&);
    MCAPI void initialize(class EntityContext&, class LookAtComponent&) const;
    MCAPI void serializeData(class Json::Value&) const;
    MCAPI ~LookAtDefinition();
    MCAPI static void buildSchema(class std::shared_ptr<class JsonUtil::JsonSchemaObjectNode<class JsonUtil::EmptyClass, class LookAtDefinition> >&);

protected:

private:

};