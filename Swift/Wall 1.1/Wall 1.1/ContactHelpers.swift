//
//  ContactHelpers.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/15/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

func masksAreTouching(_ mask1: UInt32, mask2: UInt32, contact: SKPhysicsContact) -> Bool {
    let bodyAMask = contact.bodyA.categoryBitMask
    let bodyBMask = contact.bodyB.categoryBitMask
    
    if maskContainsSubmask(bodyAMask, sub: mask1) {
        if maskContainsSubmask(bodyBMask, sub: mask2) {
            return true
        }
    }
    else if maskContainsSubmask(bodyAMask, sub: mask2) {
        if maskContainsSubmask(bodyBMask, sub: mask1) {
            return true
        }
    }
    return false
}

func maskContainsSubmask(_ mask: UInt32, sub: UInt32) -> Bool {
    return (mask & sub) == sub
}
