//
//  Buster.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/21/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class Buster: Entity {
    static let busterSpeed: CGFloat = 500
    
    init(angle: CGFloat, fromPlayer player: Player) {
        super.init(name: "Buster", health: 1)
        
        self.currentSprite = SKSpriteNode(imageNamed: "buster")
        self.currentSprite.texture?.filteringMode = .nearest
        self.currentSprite.position = player.position
        self.currentSprite.zPosition = player.zPosition
        self.currentSprite.size = CGSize(width: 20, height: 20)
        
        let physicsBody = SKPhysicsBody(circleOfRadius: self.currentSprite.size.width / 2)
        physicsBody.categoryBitMask = CollisionTypes.Buster | CollisionTypes.Entity
        physicsBody.collisionBitMask = CollisionTypes.Block | CollisionTypes.Boundary
        physicsBody.contactTestBitMask = CollisionTypes.Enemy | CollisionTypes.Block | CollisionTypes.Boundary
        physicsBody.linearDamping = 0
        physicsBody.angularDamping = 0
        physicsBody.velocity = CGVector(angle: angle) * Buster.busterSpeed
        
        self.currentSprite.physicsBody = physicsBody
        
        self.addChild(self.currentSprite)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
