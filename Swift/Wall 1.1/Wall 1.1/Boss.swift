//
//  Boss.swift
//  Wall 1.1
//
//  Created by Jeffrey Ryan on 4/28/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

import SpriteKit

class Boss: Entity {
    static let Name = "Boss"
    static let Health: Double = 25
    
    fileprivate var chargeSpeed: CGFloat = 400
    fileprivate var record = ProjectileRecord(minTimeBetweenShots: 5)
    fileprivate var shootDist: CGFloat = 500
    
    fileprivate var timeSinceCharged: TimeInterval = 0
    
    var targetPlayer: Player
    var state: BossState = .notSpawned
    
    var angleFromPlayer: CGFloat {
        return atan2(self.position.y - targetPlayer.position.y, self.position.x - targetPlayer.position.x)
    }
    
    var distFromPlayer: CGFloat {
        let dx = self.position.x - targetPlayer.position.x
        let dy = self.position.y - targetPlayer.position.y
        return sqrt(dx * dx + dy * dy)
    }
    
    enum BossState {
        case normal, charging, spawning, notSpawned
    }
    
    init(targetPlayer: Player) {
        self.targetPlayer = targetPlayer
        
        super.init(name: Boss.Name, health: Boss.Health)
        
        setup()
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func setup() {
        self.name = "Boss"
        self.zPosition = 40
        
        self.currentSprite = SKSpriteNode(imageNamed: "boss0")
        self.currentSprite.resizeWithHeight(175)
        self.currentSprite.run(Animations.boss, withKey: "animation")
        
        addChild(currentSprite)
        
        let bossBody = SKPhysicsBody(rectangleOf: CGSize(width: self.currentSprite.size.width * 3 / 4, height: self.currentSprite.size.height * 3 / 4))
        bossBody.categoryBitMask = CollisionTypes.Boss
        bossBody.collisionBitMask = CollisionTypes.None
        bossBody.contactTestBitMask = CollisionTypes.Player | CollisionTypes.Buster
        
        self.physicsBody = bossBody
    }
    
    func charge() {
        self.state = .charging
        self.physicsBody?.velocity = CGVectorZero
        
        let targetPos = CGPoint(x: self.position.x - targetPlayer.position.x, y: self.position.y - targetPlayer.position.y).normalized() * -200 + targetPlayer.position
        let charge = SKAction.sequence([SKAction.wait(forDuration: 1.0), SKAction.move(to: targetPos, duration: TimeInterval((targetPos - self.position).length() / chargeSpeed)), SKAction.run({ self.state = .normal })])
        
        run(charge)
    }
    
    func spawnIntoWorld(_ world: SKNode, distFromPlayer: CGFloat) {
        state = .spawning
        
        let randomAngle = CGFloat(arc4random()) / CGFloat(INT32_MAX) * π * 2
        self.position = targetPlayer.position + CGPoint(angle: randomAngle) * distFromPlayer
        
        world.addChild(self)
        
        let targetPos = (self.position - targetPlayer.position).normalized() * shootDist + targetPlayer.position
        let moveTowardsPlayer = SKAction.move(to: targetPos, duration: TimeInterval((targetPos - self.position).length() / chargeSpeed))
        
        self.run(SKAction.sequence([moveTowardsPlayer, SKAction.run({
            self.state = .normal
            self.physicsBody?.velocity = CGVector(angle: randomAngle + π) * self.chargeSpeed / 3
        })]))
    }
    
    func step(_ elapsedTime: TimeInterval) {
        switch state {
        case .normal:
            move(elapsedTime)
            flipTowardsPlayer()
            incrementTimeVariables(elapsedTime)
            doActionsForTimeVariables()
            
            self.physicsBody?.velocity = self.physicsBody!.velocity.normalized() * self.physicsBody!.velocity.length().clamped(0, 500)
        case .charging:
            flipTowardsPlayer()
        case .spawning:
            flipTowardsPlayer()
        case .notSpawned:
            break
        }
    }
    
    fileprivate func move(_ elapsedTime: TimeInterval) {
        let forceMagnitude = 1500.0 / sqrt(distFromPlayer)
        
        self.physicsBody?.applyForce(CGVector(angle: angleFromPlayer - π) * forceMagnitude)
    }
    
    fileprivate func flipTowardsPlayer() {
        if targetPlayer.position.x < self.position.x && xScale > 0 {
            xScale *= -1
        }
        else if targetPlayer.position.x > self.position.x && xScale < 0 {
            xScale *= -1
        }
    }
    
    fileprivate func incrementTimeVariables(_ elapsedTime: TimeInterval) {
        timeSinceCharged += elapsedTime
        record.timeSinceShot += elapsedTime
    }
    
    fileprivate func doActionsForTimeVariables() {
        if timeSinceCharged >= 16 + 2 / 3 {
            charge()
            timeSinceCharged = 0
        }
        
        if record.timeSinceShot >= record.minTimeBetweenShots && distFromPlayer <= shootDist {
            let slimeball = Slimeball(angle: angleFromPlayer + π, fromEntity: self)
            targetPlayer.parent?.addChild(slimeball)
            record.timeSinceShot = 0
        }
    }
}
