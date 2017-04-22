//
//  Player.swift
//  Wall 1.0
//
//  Created by Jeffrey Ryan on 2/27/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class Player: SKNode {
    var currentPlayerSprite: SKSpriteNode
    var playerSpeed: CGFloat = 300
    
    override init() {
        let atlas = SKTextureAtlas(named: "characters")
        let texture = atlas!.textureNamed("player_ft1")
        currentPlayerSprite = SKSpriteNode(texture: texture)
        
        super.init()
        
        addChild(currentPlayerSprite)
        
        name = "Player"
        
        var minDiam = min(currentPlayerSprite.size.width, currentPlayerSprite.size.height)
        minDiam = max(minDiam - 16.0, 4.0)
        self.physicsBody = SKPhysicsBody(circleOfRadius: minDiam / 2)
        self.physicsBody?.usesPreciseCollisionDetection = true
        self.physicsBody?.allowsRotation = false
        self.physicsBody?.friction = 0
        self.physicsBody?.linearDamping = 0
        self.physicsBody?.restitution = 1
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func moveToward(target: CGPoint) {
        let velocity = (target - position).normalized() * playerSpeed
        physicsBody?.velocity = CGVector(point: velocity)
    }
}
