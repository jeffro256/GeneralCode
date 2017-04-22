//
//  CollisionTypes.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 3/25/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

enum CollisionTypes {
    static let All      : UInt32 = UInt32.max
    static let None     : UInt32 = 0
    static let Boundary : UInt32 = 1 << 0
    static let Block    : UInt32 = 1 << 1
    static let Entity   : UInt32 = 1 << 2
    static let Player   : UInt32 = 1 << 3
    static let Enemy    : UInt32 = 1 << 4
    static let Buster   : UInt32 = 1 << 5
    static let Boss     : UInt32 = 1 << 6
    static let Slime    : UInt32 = 1 << 7
}