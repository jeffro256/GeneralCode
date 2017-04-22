//
//  CollisionTypes.swift
//  Pogo 0.1
//
//  Created by Jeffrey Ryan on 5/21/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import Foundation

enum CollisionTypes {
    static let All:    UInt32 = UINT32_MAX
    static let None:   UInt32 = 0
    static let World:  UInt32 = 1 << 0
    static let Ground: UInt32 = 1 << 1
    static let Head:   UInt32 = 1 << 2
    static let Pogo:   UInt32 = 1 << 3
}