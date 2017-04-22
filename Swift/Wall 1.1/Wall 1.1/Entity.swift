//
//  Entity.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/17/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class Entity: SKNode {
    var currentSprite: SKSpriteNode
    var health: Double
    
    var isDead: Bool {
        return health <= 0
    }
    
    init(name: String, health: Double) {
        self.currentSprite = SKSpriteNode()
        self.health = health
        
        super.init()
        
        self.name = name
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented in Entity")
    }
    /*
    func getWidthOfSprite(sprite: SKSpriteNode, withHeight newHeight: CGFloat) -> CGFloat {
        return sprite.size.width / sprite.size.height * newHeight
    }
    
    func getHeightOfSprite(sprite: SKSpriteNode, withWidth newWidth: CGFloat) -> CGFloat {
        return sprite.size.height / sprite.size.width * newWidth
    }*/
}