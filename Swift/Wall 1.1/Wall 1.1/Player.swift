//
//  Player.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 3/25/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class Player: Entity {
    let playerAtlas: SKTextureAtlas
    let playerSpeed: CGFloat = 250
    let playerHeight: CGFloat = 64
    let maxHealth: Double = 10
    
    init(spriteName: String) {
        playerAtlas = SKTextureAtlas(named: "alpha_characters")
        
        for textureName in playerAtlas.textureNames {
            let texture = playerAtlas.textureNamed(textureName )
            
            texture.filteringMode = .nearest
        }
        
        super.init(name: "Player", health: self.maxHealth)

        self.currentSprite = SKSpriteNode(texture: playerAtlas.textureNamed("\(spriteName)1"))
        self.currentSprite.zPosition = 20
        
        self.currentSprite.run(SKAction.repeatForever(SKAction.animate(with: [playerAtlas.textureNamed("\(spriteName)1"), playerAtlas.textureNamed("\(spriteName)2")], timePerFrame: 0.4)))
        
        
        adjustSize()
        
        addChild(currentSprite)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func adjustSize() {
        currentSprite.resizeWithHeight(self.playerHeight)
        
        self.physicsBody = SKPhysicsBody(rectangleOf: CGSize(width: currentSprite.size.width * 7 / 8, height: currentSprite.size.height * 7 / 8))
        self.physicsBody?.categoryBitMask = CollisionTypes.Entity | CollisionTypes.Player
        self.physicsBody?.collisionBitMask = CollisionTypes.Block | CollisionTypes.Boundary
        self.physicsBody?.contactTestBitMask = CollisionTypes.All
        self.physicsBody?.friction = 0
        self.physicsBody?.linearDamping = 0
        self.physicsBody?.angularDamping = 0
        self.physicsBody?.isDynamic = true
        self.physicsBody?.allowsRotation = false
        self.physicsBody?.restitution = 1
    }
}
