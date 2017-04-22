//
//  Slimeball.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 5/13/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class Slimeball: Entity {
    var moveSpeed: CGFloat = 400
    
    init(angle: CGFloat, fromEntity entity: SKNode) {
        super.init(name: "Buster", health: 1)
        
        self.currentSprite = SKSpriteNode(imageNamed: "slime")
        self.currentSprite.texture?.filteringMode = .nearest
        self.currentSprite.zPosition = entity.zPosition
        self.currentSprite.size = CGSize(width: 20, height: 20)
        
        let physicsBody = SKPhysicsBody(circleOfRadius: self.currentSprite.size.width / 2)
        physicsBody.categoryBitMask = CollisionTypes.Slime | CollisionTypes.Entity
        physicsBody.collisionBitMask = CollisionTypes.None
        physicsBody.linearDamping = 0
        physicsBody.angularDamping = 0
        physicsBody.velocity = CGVector(angle: angle) * moveSpeed
        
        let trail = SKSpriteNode(imageNamed: "trail0")
        trail.texture?.filteringMode = .nearest
        trail.resizeWithWidth(currentSprite.size.width * 5)
        trail.position = CGPoint(angle: angle + π) * (trail.size.width / 2 - currentSprite.size.width / 2)
        trail.zRotation = angle + π
        trail.run(Animations.trail)
        
        self.position = entity.position
        self.physicsBody = physicsBody
        self.addChild(self.currentSprite)
        self.addChild(trail)
        self.run(SKAction.sequence([SKAction.wait(forDuration: 10), SKAction.removeFromParent()]))
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
