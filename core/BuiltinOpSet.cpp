/*
 * Copyright 2011-2012 INSA Rennes
 * 
 * This file is part of ImageINSA.
 * 
 * ImageINSA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ImageINSA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ImageINSA.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "BuiltinOpSet.h"

BuiltinOpSet::BuiltinOpSet(std::string name) : OpSet(name) {
}

std::vector<GenericOperation*> BuiltinOpSet::getOperations() {
    return _operations;
}

void BuiltinOpSet::addOperation(GenericOperation* operation) {
    _operations.push_back(operation);
}
