//
//  types.h
//  kixeye
//
//  Created by Iskandar Safarov on 21/6/18.
//  Copyright © 2018 Iskandar Safarov. All rights reserved.
//
#pragma once
#include <memory>

#define DECLREF(cls) class cls; typedef std::shared_ptr<cls> cls ## Ref

DECLREF(Value);
DECLREF(Number);
DECLREF(Operator);
DECLREF(Function);
