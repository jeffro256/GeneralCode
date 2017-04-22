//
//  Enemy.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 3/25/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class Enemy: SKNode {
    var playerAtlas: SKTextureAtlas
    var currentSprite: SKSpriteNode
    var playerSpeed: CGFloat = 150
    var playerHeight: CGFloat = 32
    var isDead = false
    
    init(spriteName: String) {
        playerAtlas = SKTextureAtlas(named: "alpha_characters")
        
        for textureName in playerAtlas.textureNames {
            let texture = playerAtlas.textureNamed(textureName )
            
            texture.filteringMode = .nearest
        }
        
        currentSprite = SKSpriteNode(texture: playerAtlas.textureNamed("\(spriteName)1"))
        currentSprite.zPosition = 20
        
        currentSprite.run(SKAction.repeatForever(SKAction.animate(with: [playerAtlas.textureNamed("\(spriteName)1"), playerAtlas.textureNamed("\(spriteName)2")], timePerFrame: 0.4)))
        
        super.init()
        self.name = "Enemy"
        
        adjustSize()
        
        addChild(currentSprite)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func adjustSize() {
        let newWidth = playerHeight * currentSprite.size.width / currentSprite.size.height
        
        currentSprite.size = CGSize(width: newWidth, height: playerHeight)
        
        self.physicsBody = SKPhysicsBody(rectangleOf: currentSprite.size)
        self.physicsBody?.categoryBitMask = CollisionTypes.Entity | CollisionTypes.Enemy
        self.physicsBody?.collisionBitMask = CollisionTypes.Block | CollisionTypes.Boundary | CollisionTypes.Enemy
        self.physicsBody?.contactTestBitMask = CollisionTypes.All
        self.physicsBody?.friction = 0
        self.physicsBody?.linearDamping = 0
        self.physicsBody?.angularDamping = 0
        self.physicsBody?.isDynamic = true
        self.physicsBody?.allowsRotation = false
        self.physicsBody?.restitution = 1
    }
    
    func moveToward(_ point: CGPoint) {
        let velocity = (point - self.position).normalized() * 300
        
        self.physicsBody?.velocity = CGVector(point: velocity)
    }
}
