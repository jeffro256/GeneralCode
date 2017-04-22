//
//  Animations.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/25/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

enum Animations {
    static let boom = generateAnimation("boom", frames: 27, timePerFrame: 0.05)
    static let boss = SKAction.repeatForever(generateAnimation("boss", frames: 10, timePerFrame: 0.15))
    static let trail = SKAction.repeatForever(generateAnimation("trail", frames: 10, timePerFrame: 0.1))
}

func generateAnimation(_ name: String, frames: Int, timePerFrame: TimeInterval) -> SKAction {
    var textures = [SKTexture]()
    
    var i = 0
    var path = "\(name)\(0)"
    while i < frames {
        let texture = SKTexture(imageNamed: path)
        texture.filteringMode = .nearest
        
        textures.append(texture)
        
        i += 1
        path = "\(name)\(i)"
    }
    
    return SKAction.animate(with: textures, timePerFrame: timePerFrame)
}
